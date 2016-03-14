#ifndef ANGEL_ACTIVITY_SERVICE_H
#define ANGEL_ACTIVITY_SERVICE_H

#include <QtCore/QObject>
#include "libgato/gato.h"
#include "service.h"

class ActivityService : public AngelService
{
    Q_OBJECT
    Q_PROPERTY(int steps READ getSteps NOTIFY stepsChanged)
    Q_PROPERTY(int acceleration READ getAcceleration NOTIFY accelerationChanged)

public:
    explicit ActivityService(QObject *parent = 0);
    static const GatoUUID ServiceActivityMonitoringUuid;
    static const GatoUUID CharStepCountUuid;
    static const GatoUUID CharAccelerationEnergyMagnitudeUuid;

    const GatoUUID uuid();
    int getSteps() const;
    void setSteps(int steps);
    int getAcceleration() const;

    Q_INVOKABLE void readAcceleration();

public slots:
    void handleCharacteristics(const GatoService &service);
    void handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value);

Q_SIGNALS:
    void stepsChanged();
    void accelerationChanged();

private:
    void updateAcceleration(const QByteArray &value);

    int _steps;
    QVector<quint32> _acceleration;
};

#endif // ANGEL_ACTIVITY_SERVICE_H
