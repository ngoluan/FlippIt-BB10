/*
 * generalUtilities.h
 *
 *  Created on: Dec 22, 2014
 *      Author: Luan
 */

#ifndef GENERALUTILITIES_H_
#define GENERALUTILITIES_H_

#include <QString>
#include <QVariantList>
#include <QVariantMap>

class GeneralUtilities: public QObject {
        Q_OBJECT

public:
    GeneralUtilities(QObject *parent=0);
    virtual ~GeneralUtilities();
    Q_INVOKABLE QString serverPath;
    Q_INVOKABLE QVariantList json2List(QString reply);
    Q_INVOKABLE QVariantMap json2Map(QString reply);
    Q_INVOKABLE void createToast(QString msg);
};

#endif /* GENERALUTILITIES_H_ */
