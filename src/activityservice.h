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
    static const GatoUUID CharActivityMonitoringControlPointUuid;

    const GatoUUID uuid();
    int getSteps() const;
    void setSteps(int steps);
    int getAcceleration() const;

    Q_INVOKABLE void readSteps();
    Q_INVOKABLE void resetSteps();
    Q_INVOKABLE void readAcceleration();
    Q_INVOKABLE void resetAcceleration();

public slots:
    void handleCharacteristics(const GatoService &service);
    void handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value);

Q_SIGNALS:
    void stepsChanged();
    void accelerationChanged();

private:
    void updateAcceleration(const QByteArray &value);
    void writeActivityControl(const QByteArray &opcode);

    int _steps;
    QVector<quint32> _acceleration;
};

#endif // ANGEL_ACTIVITY_SERVICE_H
