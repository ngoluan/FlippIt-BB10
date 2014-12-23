/*
 * login.hpp
 *
 *  Created on: Dec 22, 2014
 *      Author: Luan
 */

#ifndef LOGIN_HPP_
#define LOGIN_HPP_

#include <QString>
#include <QNetworkReply>
#include "generalUtilities.hpp"
#include "settings.hpp"

class Login: public QObject {
        Q_OBJECT
public:
    Login(QObject *parent=0);
    virtual ~Login();
    void loginUser(QString email, QString password);
public Q_SLOTS:
    void finishedSlot();
Q_SIGNALS:
    void userLoggedIn();
private:
    QNetworkReply* reply;
    GeneralUtilities *generalUtilities;
    Settings *settings;
    QString localEmail;
};

#endif /* LOGIN_HPP_ */
