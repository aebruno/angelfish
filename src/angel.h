#ifndef ANGEL_H
#define ANGEL_H

#include "deviceinfo.h"
#include "devicemodel.h"
#include <QString>
#include "libgato/gato.h"


QT_USE_NAMESPACE
class Angel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(DeviceModel* devices READ devices CONSTANT)

public:
    Angel();
    ~Angel();
    QString error() const;

public slots:
    void deviceSearch();
    void stopSearch();
    DeviceModel* devices();


private slots:
    void addDevice(GatoPeripheral *peripheral, int rssi);

Q_SIGNALS:
    void errorChanged();

private:
    void setError(const QString &error);
    QString m_error;
    DeviceInfo m_currentDevice;
    GatoCentralManager* m_deviceDiscoveryAgent;
    DeviceModel d_model;
};

#endif // ANGEL_H
