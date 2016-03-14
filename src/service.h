#ifndef ANGEL_SERVICE_H
#define ANGEL_SERVICE_H

#include <QtCore/QObject>
#include "libgato/gato.h"

class AngelService : public QObject
{
    Q_OBJECT

public:
    explicit AngelService(QObject *parent = 0);

public:
    virtual const GatoUUID uuid() = 0;
    void setSensor(GatoPeripheral *sensor);
    virtual void handleCharacteristics(const GatoService &service) = 0;
    virtual void handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value) = 0;

protected:
    GatoPeripheral* _sensor;
};

#endif // ANGEL_SERVICE_H
