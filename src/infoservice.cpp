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

#include "infoservice.h"

const GatoUUID InfoService::ServiceDeviceInformationUuid(quint16(0x180A));
const GatoUUID InfoService::CharManufacturerNameUuid(quint16(0x2A29));
const GatoUUID InfoService::CharModelNumberUuid(quint16(0x2A24));
const GatoUUID InfoService::CharSerialNumberUuid(quint16(0x2A25));
const GatoUUID InfoService::CharHardwareRevisionUuid(quint16(0x2A27));
const GatoUUID InfoService::CharFirmwareRevisionUuid(quint16(0x2A26));
const GatoUUID InfoService::CharSoftwareRevisionUuid(quint16(0x2A28));

InfoService::InfoService(QObject *parent) :
    AngelService(parent)
{
}

const GatoUUID InfoService::uuid()
{
    return ServiceDeviceInformationUuid;
}

void InfoService::handleCharacteristics(const GatoService &service)
{
    if(service.uuid() == uuid()) {
        qDebug() << "Got characteristics for Device Information Service: " << service.uuid();
        foreach (const GatoCharacteristic &c, service.characteristics()) {
            _sensor->readValue(c);
        }
    }
}

void InfoService::handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value)
{
    QSettings settings;
    QString qstr = QString::fromUtf8(value.data());

    if(characteristic.uuid() == CharManufacturerNameUuid) {
        settings.setValue(SETTING_MF, qstr);
    } else if(characteristic.uuid() == CharModelNumberUuid) {
        settings.setValue(SETTING_MODEL, qstr);
    } else if(characteristic.uuid() == CharSerialNumberUuid) {
        settings.setValue(SETTING_SERIAL, qstr);
    } else if(characteristic.uuid() == CharHardwareRevisionUuid) {
        settings.setValue(SETTING_HWREV, qstr);
    } else if(characteristic.uuid() == CharFirmwareRevisionUuid) {
        settings.setValue(SETTING_FIRMREV, qstr);
    } else if(characteristic.uuid() == CharSoftwareRevisionUuid) {
        settings.setValue(SETTING_SOFTREV, qstr);
    }
}
