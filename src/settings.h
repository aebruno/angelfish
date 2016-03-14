/**
 * Copyright (c) 2012 Nokia Corporation.
 * All rights reserved.
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#define SETTING_NAME "device/name"
#define SETTING_ADDR "device/address"
#define SETTING_MF "device/manufacturer"
#define SETTING_MODEL "device/model"
#define SETTING_SERIAL "device/serial"
#define SETTING_HWREV "device/hwrev"
#define SETTING_FIRMREV "device/firmrev"
#define SETTING_SOFTREV "device/softrev"

class Settings : public QObject
{
    Q_OBJECT

public:
    explicit Settings(QObject *parent = 0);
    explicit Settings(const Settings &settings);

public slots:
    void setSetting(const QString &setting, const QVariant &value);
    QVariant setting(const QString &setting, const QVariant &defaultValue);
    QVariant setting(const QString &setting);
    bool removeSetting(const QString &setting);
    void clear();

signals:
    void settingChanged(const QString &setting, const QVariant &value);
};

#endif // SETTINGS_H
