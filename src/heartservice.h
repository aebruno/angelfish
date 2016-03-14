#ifndef ANGEL_HEART_SERVICE_H
#define ANGEL_HEART_SERVICE_H

#include <QtCore/QObject>
#include "libgato/gato.h"
#include "service.h"

class HeartService : public AngelService
{
    Q_OBJECT
    Q_PROPERTY(int rate READ getRate NOTIFY heartRateChanged)

public:
    explicit HeartService(QObject *parent = 0);
    static const GatoUUID ServiceHeartRateUuid;
    static const GatoUUID CharHeartRateMeasurementUuid;

    const GatoUUID uuid();
    int getRate() const;

public slots:
    void handleCharacteristics(const GatoService &service);
    void handleValueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value);

Q_SIGNALS:
    void heartRateChanged();

private:
    void updateBeats(const QByteArray &value);

    QVector<quint16> _beats;
};

#endif // ANGEL_HEART_SERVICE_H
