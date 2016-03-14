#include "heartservice.h"

const GatoUUID HeartService::ServiceHeartRateUuid(quint16(0x180D));
const GatoUUID HeartService::CharHeartRateMeasurementUuid(quint16(0x2A37));

HeartService::HeartService(QObject *parent) :
    AngelService(parent)
{
}


const GatoUUID HeartService::uuid()
{
    return ServiceHeartRateUuid;
}

void HeartService::handleCharacteristics(const GatoService &service)
{
    if(service.uuid() == uuid()) {
        qDebug() << "Got characteristics for Heart Service: " << service.uuid();
        foreach (const GatoCharacteristic &c, service.characteristics()) {
            if(c.uuid() == CharHeartRateMeasurementUuid) {
                qDebug() << "Subscribing to heart rate notifications";
                _sensor->setNotification(c, true);
            } else {
                qDebug() << "Ignoring characteristic " << c.uuid() << " for heart rate service " << service.uuid();
            }
        }
    }
}

void HeartService::handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value)
{
    if(characteristic.uuid() == CharHeartRateMeasurementUuid) {
        qDebug() << "Updating heart rate measurement";
        updateBeats(value);
    }
}

int HeartService::getRate() const 
{
    if (_beats.isEmpty())
        return 0;
    return _beats.last();
}

void HeartService::updateBeats(const QByteArray &value) {
    const char *data = value.constData();
    quint8 flags = data[0];

    //Heart Rate
    if (flags & 0x1) { // HR 16 bit? otherwise 8 bit
        quint16 *heartRate = (quint16 *) &data[1];
        qDebug() << "16 bit HR value:" << *heartRate;
        _beats.append(*heartRate);
    } else {
        quint8 *heartRate = (quint8 *) &data[1];
        qDebug() << "8 bit HR value:" << *heartRate;
        _beats.append(*heartRate);
    }

    //Energy Expended
    if (flags & 0x8) {
        int index = (flags & 0x1) ? 3 : 2;
        quint16 *energy = (quint16 *) &data[index];
        qDebug() << "Used Energy:" << *energy;
    }

    Q_EMIT heartRateChanged();
}
