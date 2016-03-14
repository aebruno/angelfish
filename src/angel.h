#ifndef ANGEL_H
#define ANGEL_H

#include <QtCore/QObject>
#include <QSettings>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QByteArray>
#include "libgato/gato.h"
#include "service.h"
#include "settings.h"
#include "devicemodel.h"

class Angel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sensorState READ sensorState NOTIFY sensorStateChanged)
    Q_PROPERTY(bool hasSensor READ hasSensor NOTIFY sensorChanged)
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectionChanged)

public:

    Angel();
    ~Angel();
    QString sensorState() const;
    QString address() const;
    bool hasSensor() const;
    bool isConnected();
    void registerService(AngelService *service);

    Q_INVOKABLE void connectSensor();
    Q_INVOKABLE void disconnectSensor();
    Q_INVOKABLE void deviceSearch();
    Q_INVOKABLE void stopSearch();
    Q_INVOKABLE void setupNewDevice(int index);
    Q_INVOKABLE DeviceModel* devices();

private slots:
    void addDevice(GatoPeripheral *peripheral, int rssi);
    void handleDeviceConnected();
    void handleDeviceDisconnected();
	void handleDeviceServices();

Q_SIGNALS:
    void sensorChanged();
    void connectionChanged();
    void sensorStateChanged();

private:
    void setSensor(QString address);

    QMap<GatoUUID, AngelService *> _services;

    GatoPeripheral* _sensor;
    GatoCentralManager* _bleManager;
    DeviceModel _dmodel;
};

#endif // ANGEL_H
