#ifndef ANGEL_BATTERY_SERVICE_H
#define ANGEL_BATTERY_SERVICE_H

#include <QtCore/QObject>
#include "libgato/gato.h"
#include "service.h"

class BatteryService : public AngelService
{
    Q_OBJECT
    Q_PROPERTY(int level READ getLevel NOTIFY levelChanged)

public:
    explicit BatteryService(QObject *parent = 0);
    static const GatoUUID ServiceBatteryUuid;
    static const GatoUUID CharBatteryLevelUuid;

    const GatoUUID uuid();
    int getLevel() const;
    void setLevel(int level);

public slots:
    void handleCharacteristics(const GatoService &service);
    void handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value);

Q_SIGNALS:
    void levelChanged();

private:
    int _batteryLevel;
};

#endif // ANGEL_BATTERY_SERVICE_H
