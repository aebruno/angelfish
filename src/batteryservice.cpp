/*
 * Copyright (C) 2016 Andrew E. Bruno <aeb@qnot.org>
 *
 * This file is part of AngelFish.
 * 
 * AngelFish is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AngelFish is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AngelFish.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include "batteryservice.h"

const GatoUUID BatteryService::ServiceBatteryUuid(quint16(0x180F));
const GatoUUID BatteryService::CharBatteryLevelUuid(quint16(0x2A19));

BatteryService::BatteryService(QObject *parent) :
    AngelService(parent)
{
    _batteryLevel = 0;
}


const GatoUUID BatteryService::uuid()
{
    return ServiceBatteryUuid;
}

void BatteryService::handleCharacteristics(const GatoService &service)
{
    if(service.uuid() == uuid()) {
        qDebug() << "Got characteristics for Battery Service: " << service.uuid();
        foreach (const GatoCharacteristic &c, service.characteristics()) {
            if(c.uuid() == CharBatteryLevelUuid) {
                qDebug() << "Subscribing to battery level notifications";
                _sensor->setNotification(c, true);
            } else {
                qDebug() << "Ignoring characteristic " << c.uuid() << " for battery service " << service.uuid();
            }
        }
    }
}

void BatteryService::handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value)
{
    if(characteristic.uuid() == CharBatteryLevelUuid) {
        qDebug() << "Updating battery level";
        setLevel((int)value.at(0));
    }
}

int BatteryService::getLevel() const 
{
    return _batteryLevel;
}

void BatteryService::setLevel(int level)
{
    _batteryLevel = level;
    Q_EMIT levelChanged();
}
