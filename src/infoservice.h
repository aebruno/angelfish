#ifndef ANGEL_INFO_SERVICE_H
#define ANGEL_INFO_SERVICE_H

#include <QtCore/QObject>
#include <QSettings>
#include "libgato/gato.h"
#include "service.h"
#include "settings.h"

class InfoService : public AngelService
{
    Q_OBJECT

public:
    explicit InfoService(QObject *parent = 0);
    static const GatoUUID ServiceDeviceInformationUuid;
    static const GatoUUID CharManufacturerNameUuid;
    static const GatoUUID CharModelNumberUuid;
    static const GatoUUID CharSerialNumberUuid;
    static const GatoUUID CharHardwareRevisionUuid;
    static const GatoUUID CharFirmwareRevisionUuid;
    static const GatoUUID CharSoftwareRevisionUuid;

    const GatoUUID uuid();

public slots:
    void handleCharacteristics(const GatoService &service);
    void handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value);
};

#endif // ANGEL_INFO_SERVICE_H
