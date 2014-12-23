/*
 * generalUtilities.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: Luan
 */

#include <src/generalUtilities.hpp>
#include <QVariantList>
#include <QVariant>
#include <QString>
#include <bb/data/JsonDataAccess>
#include <bb/system/SystemToast>

using namespace bb::data;
using namespace bb::system;

GeneralUtilities::GeneralUtilities(QObject *parent)
{
    serverPath = "http://www.flippit.ca/";
}

GeneralUtilities::~GeneralUtilities()
{
    // TODO Auto-generated destructor stub
}

QVariantList GeneralUtilities::json2List(QString reply){
    std::string message = reply.toUtf8().constData();
    JsonDataAccess jda;
    QVariant response = jda.loadFromBuffer(reply);
    QVariantList list = response.toList();
    return list;
}

QVariantMap GeneralUtilities::json2Map(QString reply){
    std::string message = reply.toUtf8().constData();
    JsonDataAccess jda;
    QVariant response = jda.loadFromBuffer(reply);
    QVariantMap map = response.toMap();
    return map;
}
void GeneralUtilities::createToast(QString msg){
    SystemToast *toast = new SystemToast(this);

    toast->setBody(msg);
    toast->setPosition(SystemUiPosition::MiddleCenter);
    toast->show();
}
