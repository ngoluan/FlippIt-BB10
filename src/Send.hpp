/*
 * Send.hpp
 *
 *  Created on: Dec 25, 2014
 *      Author: Luan
 */

#ifndef SEND_HPP_
#define SEND_HPP_

#include <QtCore/QObject>
#include <bb/cascades/GroupDataModel>
#include <bb/cascades/NavigationPane>
#include <QDebug>
#include <QString>
#include <bb/cascades/TouchEvent>
#include "generalUtilities.hpp"
#include "settings.hpp"

using namespace bb::cascades;

class Send: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bb::cascades::GroupDataModel* model READ model CONSTANT)
public:
    Send(QObject *parent = 0);
    Q_INVOKABLE void addDevices();
    Q_INVOKABLE void getDevices();
    Q_INVOKABLE void test();
    Q_INVOKABLE void sendText(QVariantMap device);
    Q_INVOKABLE void sendFile(QVariantMap device);
    Q_INVOKABLE void filePicker(QString fileName);
    Q_INVOKABLE void setSaveMessage();
    void setNavPane(NavigationPane *navPane);
    virtual ~Send();
    bb::cascades::GroupDataModel* model() const;
public Q_SLOTS:
    void finishedSlot();
    void sendFinish();
    void handleTouch(bb::cascades::TouchEvent* event);
    void SlotSetProgressLevel(qint64 bytesSent, qint64 bytesTotal);
private:
    QString fileName;
    bb::cascades::GroupDataModel *m_model;
    GeneralUtilities *generalUtilities;
    Settings *settings;
    void drawDevices(QVariantList devices);
    NavigationPane *nav;
    QNetworkReply* reply;
    QString saveMessage;
    QNetworkAccessManager nam;
};

#endif /* SEND_HPP_ */
