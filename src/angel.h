#ifndef ANGEL_H
#define ANGEL_H

#include "devicemodel.h"
#include <QtCore/QObject>
#include <QSettings>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QByteArray>
#include "libgato/gato.h"

#define SETTING_NAME "device/name"
#define SETTING_ADDR "device/address"
#define SETTING_MF "device/manufacturer"
#define SETTING_MODEL "device/model"
#define SETTING_SERIAL "device/serial"

class Angel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(QString sensorState READ sensorState NOTIFY sensorStateChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString address READ address NOTIFY addressChanged)
    Q_PROPERTY(QString manufacturer READ manufacturer NOTIFY manufacturerChanged)
    Q_PROPERTY(QString modelNumber READ modelNumber NOTIFY modelNumberChanged)
    Q_PROPERTY(QString serialNumber READ serialNumber NOTIFY serialNumberChanged)
    Q_PROPERTY(int battery READ battery NOTIFY batteryChanged)
    Q_PROPERTY(int steps READ steps NOTIFY stepsChanged)
    Q_PROPERTY(int heartRate READ heartRate NOTIFY heartRateChanged)

    Q_PROPERTY(bool hasSensor READ hasSensor NOTIFY sensorChanged)
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectionChanged)
    //Q_PROPERTY(DeviceModel* devices READ getDevices CONSTANT)
    //Q_PROPERTY(GatoPeripheral* sensor READ getSensor CONSTANT)

public:

    static const GatoUUID ServiceDeviceInformationUuid;
    static const GatoUUID CharManufacturerNameUuid;
    static const GatoUUID CharModelNumberUuid;
    static const GatoUUID CharSerialNumberUuid;
    static const GatoUUID ServiceBatteryUuid;
    static const GatoUUID CharBatteryLevelUuid;
    static const GatoUUID ServiceHeartRateUuid;
    static const GatoUUID CharHeartRateMeasurementUuid;
    static const GatoUUID ServiceActivityMonitoringUuid;
    static const GatoUUID CharStepCountUuid;
    static const GatoUUID ServiceAlarmClockUuid;
    static const GatoUUID CharCurrentDateTimeUuid;
    static const GatoUUID ServiceWaveformSignalUuid;
    static const GatoUUID CharOpticalWaveformUuid;
    static const GatoUUID ServiceHealthJournalUuid;
    static const GatoUUID CharHealthJournalEntryUuid;
    static const GatoUUID CharHealthJournalControlUuid;

    Angel();
    ~Angel();
    QString error() const;
    QString sensorState() const;
    QString name() const;
    QString address() const;
    QString manufacturer() const;
    QString modelNumber() const;
    QString serialNumber() const;
    int battery() const;
    int steps() const;
    int heartRate() const;
    bool hasSensor() const;
    bool isConnected();

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
	void handleDeviceCharacteristics(const GatoService &service);
	void handleDeviceUpdate(const GatoCharacteristic &characteristic, const QByteArray &value);

Q_SIGNALS:
    void errorChanged();
    void nameChanged();
    void addressChanged();
    void manufacturerChanged();
    void sensorChanged();
    void modelNumberChanged();
    void serialNumberChanged();
    void batteryChanged();
    void stepsChanged();
    void heartRateChanged();
    void connectionChanged();
    void sensorStateChanged();

private:
    void setError(const QString &error);
    void setSensor(QString address);
    void updateBeats(const QByteArray &value);

    QSettings _settings;
    int _batteryLevel;
    int _steps;
    QVector<quint16> _beats;
    QString m_error;
    GatoPeripheral* _sensor;
    GatoCentralManager* m_deviceDiscoveryAgent;
    DeviceModel d_model;
};

#endif // ANGEL_H
