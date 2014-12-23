/*
 * settings.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: Luan
 */

#include <src/settings.hpp>
#include <QSettings>

Settings::Settings()
{
    // TODO Auto-generated constructor stub

}

Settings::~Settings()
{
    // TODO Auto-generated destructor stub
}


QString Settings::getValueFor(const QString &objectName, const QString &defaultValue) {
        QSettings settings("Luan", "FlippIt");

        // If no value has been saved, return the default value.
        if (settings.value(objectName).isNull()) {
                return defaultValue;
        }

        // Otherwise, return the value stored in the settings object.
        return settings.value(objectName).toString();
}

void Settings::saveValueFor(const QString &objectName, const QString &inputValue) {
        // A new value is saved to the application settings object.
        QSettings settings("Luan", "FlippIt");
        settings.setValue(objectName, QVariant(inputValue));
}

