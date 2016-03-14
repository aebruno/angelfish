#include "activityservice.h"

const GatoUUID ActivityService::ServiceActivityMonitoringUuid(QString("68b52738-4a04-40e1-8f83-337a29c3284d"));
const GatoUUID ActivityService::CharStepCountUuid(QString("7a543305-6b9e-4878-ad67-29c5a9d99736"));
const GatoUUID ActivityService::CharAccelerationEnergyMagnitudeUuid(QString("9e3bd0d7-bdd8-41fd-af1f-5e99679183ff"));

ActivityService::ActivityService(QObject *parent) :
    AngelService(parent)
{
    _steps = 0;
}


const GatoUUID ActivityService::uuid()
{
    return ServiceActivityMonitoringUuid;
}

void ActivityService::handleCharacteristics(const GatoService &service)
{
    if(service.uuid() == uuid()) {
        qDebug() << "Got characteristics for Activity Monitoring Service: " << service.uuid();
        foreach (const GatoCharacteristic &c, service.characteristics()) {
            if(c.uuid() == CharStepCountUuid) {
                qDebug() << "Subscribing to step notifications";
                _sensor->setNotification(c, true);
                _sensor->readValue(c);
            } else if(c.uuid() == CharAccelerationEnergyMagnitudeUuid) {
                qDebug() << "Reading acceleration engery magnitude";
                _sensor->readValue(c);
            } else {
                qDebug() << "Ignoring characteristic " << c.uuid() << " for activity monitoring service " << service.uuid();
            }
        }
    }
}

void ActivityService::handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value)
{
    if(characteristic.uuid() == CharStepCountUuid) {
        qDebug() << "Updating step count";
        const char *data = value.constData();
        quint32 *steps = (quint32 *) &data[0];
        setSteps((int)*steps);
    } else if(characteristic.uuid() == CharAccelerationEnergyMagnitudeUuid) {
        qDebug() << "Updating acceleration energy magnitude";
        updateAcceleration(value);
    }
}

int ActivityService::getSteps() const 
{
    return _steps;
}

void ActivityService::setSteps(int steps)
{
    _steps = steps;
    Q_EMIT stepsChanged();
}

int ActivityService::getAcceleration() const 
{
    if (_acceleration.isEmpty())
        return 0;
    return _acceleration.last();
}

void ActivityService::updateAcceleration(const QByteArray &value)
{
    const char *data = value.constData();
    quint32 *accelMag = (quint32 *) &data[0];
    _acceleration.append(*accelMag);
    Q_EMIT accelerationChanged();
}

void ActivityService::readAcceleration()
{
    if(_sensor != NULL && _sensor->state() == GatoPeripheral::StateConnected && !_sensor->services().isEmpty()) {
        QList<GatoService> services = _sensor->services();
        foreach (const GatoService &s, services) {
            if(s.uuid() == uuid()) {
                QList<GatoCharacteristic> chars = s.characteristics();
                foreach (const GatoCharacteristic &c, chars) {
                    if(c.uuid() == CharAccelerationEnergyMagnitudeUuid) {
                        _sensor->readValue(c);
                    }
                }
            }
        }
    }
}
