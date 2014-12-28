/*
 * History.cpp
 *
 *  Created on: Dec 24, 2014
 *      Author: Luan
 */

#include <src/History.hpp>
#include "generalUtilities.hpp"
#include <QNetworkReply>
#include <bb/data/JsonDataAccess>
#include "settings.hpp"
#include <QDebug>

using namespace bb::cascades;
using namespace bb::data;

History::History(QObject *parent)
:QObject(parent)
, m_model(new GroupDataModel(this))
{
    m_model->setGrouping(ItemGrouping::None);

}
void History::addData()
{
    m_model->clear();

    generalUtilities = new GeneralUtilities();

    Settings * settings = new Settings();
    QString email = settings->getValueFor("email","");
    if(email.isEmpty()){
        return;
    }
      // Call the webservice
      networkManager = new QNetworkAccessManager(this);
      qDebug()<<"Getting history data";
      QByteArray data;
      QUrl params;

      params.addQueryItem("email", email);
      data.append(params.toString());
      data.remove(0,1);

      QString requestUrl = generalUtilities->serverPath + "server/getHistory_v1.php";

      QNetworkRequest networkRequest= QNetworkRequest();
      networkRequest.setUrl(requestUrl);
      networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

      //QNetworkReply* reply = networkManager.post(networkRequest,data);
      reply = networkManager->post(networkRequest,data);
      bool ok = connect(reply, SIGNAL(finished()), this, SLOT(finishedSlot()));
          Q_ASSERT(ok);
          Q_UNUSED(ok);
}
GroupDataModel* History::model() const
{
    return m_model;
}

void History::finishedSlot()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here

        // Example 2: Reading bytes form the reply
        QByteArray bytes = reply->readAll();  // bytes
        QString string(bytes); // string
        qDebug()<<"Received history data " + string;
        convertJSON(string);

    }
    // Some http error received
    else
    {
        // handle errors here
    }

    //delete reply;
}
void History::convertJSON(QString reply){
    qDebug() << reply;
    std::string message = reply.toUtf8().constData();
    // Create a data model with sorting keys for firstname and lastname

    // Load the JSON data
    JsonDataAccess jda;
    QVariant list = jda.loadFromBuffer(reply);
    QVariantMap map;

    foreach ( QVariant item , list.toList())
    {

        map["id"] = item.value<QVariantMap>().value("id").toString();
        map["dateTime"] = item.value<QVariantMap>().value("dateTime").toString();
        map["message"] = item.value<QVariantMap>().value("message").toString();
        map["targetID"] = item.value<QVariantMap>().value("targetID").toString();
        map["fileName"] = item.value<QVariantMap>().value("fileName").toString();
        map["dbID"] = item.value<QVariantMap>().value("id").toString();

        m_model->insert(map);
    }

}
History::~History()
{
    // TODO Auto-generated destructor stub
}

