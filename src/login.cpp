/*
 * login.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: Luan
 */

#include <src/login.hpp>
#include <QString>
#include <QVariantMap>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "settings.hpp"

Login::Login(QObject *parent)
{
    // TODO Auto-generated constructor stub
}

Login::~Login()
{
    // TODO Auto-generated destructor stub
}
void Login::loginUser(QString email, QString password){
    qDebug() << "Logging in: " + email + " " + password;
    localEmail = email;
    generalUtilities = new GeneralUtilities();
    settings = new Settings();

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);

    QByteArray data;
    QUrl params;
    params.addQueryItem("email", email);
    params.addQueryItem("password", password);
    params.addQueryItem("targetID", settings->getValueFor("pim",""));
    params.addQueryItem("type", "blackberry");
    data.append(params.toString());
    data.remove(0,1);

    QString requestUrl = generalUtilities->serverPath + "server/login_v2.php";

    QNetworkRequest networkRequest= QNetworkRequest();
    networkRequest.setUrl(requestUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    reply = networkManager->post(networkRequest,data);
    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(finishedSlot()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}
void Login::finishedSlot()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();  // bytes
        QString string(bytes); // string
        qDebug() << "Server response: " + string;
        QVariantMap response = generalUtilities->json2Map(string);
        QString error = response.value("error").toString();
        QString message = response.value("message").toString();
        if(!error.isEmpty()){
            qDebug() << error;
            generalUtilities->createToast(error);
        }
        else{
            settings->saveValueFor("email",localEmail);
            generalUtilities->createToast(message);
            emit userLoggedIn();
        }

    }
    else
    {
        // handle errors here
    }
}
