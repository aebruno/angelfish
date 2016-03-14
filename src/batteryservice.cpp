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
