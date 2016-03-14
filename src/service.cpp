#include "service.h"

AngelService::AngelService(QObject *parent)
{
    _sensor = NULL;
}

void AngelService::setSensor(GatoPeripheral *sensor) {
    _sensor = sensor;
    connect(_sensor, SIGNAL(characteristicsDiscovered(GatoService)),
            this, SLOT(handleCharacteristics(GatoService)));
    connect(_sensor, SIGNAL(valueUpdated(GatoCharacteristic,QByteArray)),
            this, SLOT(handleValueUpdated(GatoCharacteristic,QByteArray)));
}
