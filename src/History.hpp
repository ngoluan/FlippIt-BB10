/*
 * History.hpp
 *
 *  Created on: Dec 24, 2014
 *      Author: Luan
 */

#ifndef HISTORY_HPP_
#define HISTORY_HPP_

#include <bb/cascades/GroupDataModel>
#include "generalUtilities.hpp"
#include <QtCore/QObject>

class History: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bb::cascades::GroupDataModel* model READ model CONSTANT)
public:
    History(QObject *parent = 0);
    virtual ~History();
    Q_INVOKABLE void addData();
public Q_SLOTS:
    void finishedSlot();
private:
    bb::cascades::GroupDataModel* model() const;
    GeneralUtilities *generalUtilities;
    QNetworkReply* reply;
    QNetworkAccessManager* networkManager;
    bb::cascades::GroupDataModel *m_model;
    void convertJSON(QString reply);
};

#endif /* HISTORY_HPP_ */
