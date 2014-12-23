/*
 * settings.hpp
 *
 *  Created on: Dec 22, 2014
 *      Author: Luan
 */

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

class Settings: public QObject {
        Q_OBJECT

public:
    Settings();
    virtual ~Settings();
    Q_INVOKABLE QString getValueFor(const QString &objectName, const QString &defaultValue);
    Q_INVOKABLE void saveValueFor(const QString &objectName, const QString &inputValue);
};

#endif /* SETTINGS_HPP_ */
