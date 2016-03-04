#include "angel.h"

const GatoUUID Angel::ServiceDeviceInformationUuid(quint16(0x180A));
const GatoUUID Angel::CharManufacturerNameUuid(quint16(0x2A29));
const GatoUUID Angel::CharModelNumberUuid(quint16(0x2A24));
const GatoUUID Angel::CharSerialNumberUuid(quint16(0x2A25));
const GatoUUID Angel::ServiceBatteryUuid(quint16(0x180F));
const GatoUUID Angel::CharBatteryLevelUuid(quint16(0x2A19));
const GatoUUID Angel::ServiceHeartRateUuid(quint16(0x180D));
const GatoUUID Angel::CharHeartRateMeasurementUuid(quint16(0x2A37));

Angel::Angel()
{
    m_deviceDiscoveryAgent = new GatoCentralManager(this);
    _sensor = NULL;
    _batteryLevel = 0;

    connect(m_deviceDiscoveryAgent, SIGNAL(discoveredPeripheral(GatoPeripheral *, int)),
            this, SLOT(addDevice(GatoPeripheral *, int)));

    QSettings settings;
    if(settings.value(SETTING_ADDR).toString().length() > 0) {
        qWarning() << "Found device: " << settings.value(SETTING_ADDR).toString();
        setSensor(settings.value(SETTING_ADDR).toString());
    }
}

Angel::~Angel()
{
    d_model.clear();
    m_deviceDiscoveryAgent->stopScan();
    if(hasSensor()) {
        disconnectSensor();
    }

    delete m_deviceDiscoveryAgent;
    delete _sensor;
}

void Angel::setSensor(QString address)
{
    _sensor = new GatoPeripheral(GatoAddress(address));
    connect(_sensor, SIGNAL(connected()), this, SLOT(handleDeviceConnected()));
    connect(_sensor, SIGNAL(disconnected()), this, SLOT(handleDeviceDisconnected()));
	connect(_sensor, SIGNAL(servicesDiscovered()), this, SLOT(handleDeviceServices()));
	connect(_sensor, SIGNAL(characteristicsDiscovered(GatoService)),
            this, SLOT(handleDeviceCharacteristics(GatoService)));
	connect(_sensor, SIGNAL(valueUpdated(GatoCharacteristic,QByteArray)),
			this, SLOT(handleDeviceUpdate(GatoCharacteristic,QByteArray)));
}

void Angel::deviceSearch()
{
    qWarning() << "Starting device search";
    qWarning() << "Count " << d_model.count();
    d_model.clear();
    m_deviceDiscoveryAgent->scanForPeripherals();

    // Stop searching after 10 seconds
    //QTimer::singleShot(10000, this, SLOT(stopSearch()));
}

void Angel::stopSearch()
{
    qWarning() << "Stopping device search";
    qWarning() << "Count " << d_model.count();
    m_deviceDiscoveryAgent->stopScan();
}

void Angel::addDevice(GatoPeripheral *peripheral, int rssi)
{
    if(peripheral->name().contains("Angel", Qt::CaseInsensitive)) {
        qWarning() << "Discovered LE Device name: " << peripheral->name() << " Address: "
                   << peripheral->address().toString();
        d_model.addDevice(peripheral);
        qWarning() << "Count " << d_model.count();
    }
}

void Angel::setupNewDevice(int index)
{
    qWarning() << "Setting up new device";
    GatoPeripheral* d = d_model.getDevice(index);
    if(d == NULL) {
        qWarning() << "Failed to setup device. Invalid index " << index;
        return;
    }
    
    QSettings settings;
    settings.setValue(SETTING_NAME, d->name());
    settings.setValue(SETTING_ADDR, d->address().toString());
    settings.setValue(SETTING_MF, "");
    settings.setValue(SETTING_MODEL, "");
    settings.setValue(SETTING_SERIAL, "");
    settings.sync();

    setSensor(d->address().toString());

    d_model.clear();
    _batteryLevel = 0;
    Q_EMIT addressChanged();
    Q_EMIT nameChanged();
    Q_EMIT manufacturerChanged();
    Q_EMIT modelNumberChanged();
    Q_EMIT serialNumberChanged();
    Q_EMIT batteryChanged();
    Q_EMIT sensorChanged();
}

QString Angel::error() const
{
    return m_error;
}

DeviceModel* Angel::devices()
{
    return &d_model;
}

bool Angel::hasSensor()
{
    return _sensor != NULL;
}

bool Angel::isConnected()
{
    if(hasSensor()) {
        return _sensor->state() == GatoPeripheral::StateConnected;
    }

    return false;
}

void Angel::setError(const QString &error)
{
    if (m_error != error) {
        m_error = error;
        Q_EMIT errorChanged();
    }
}

QString Angel::name() const
{
    QSettings settings;
    if(_sensor != NULL && _sensor->name().length() > 0) {
        return _sensor->name();
    } else if(settings.value(SETTING_NAME).toString().length() > 0) {
        return settings.value(SETTING_NAME).toString();
    }

    return QString();
}

QString Angel::address() const
{
    QSettings settings;
    if(_sensor != NULL) {
        return _sensor->address().toString();
    } else if(settings.value(SETTING_ADDR).toString().length() > 0) {
        return settings.value(SETTING_ADDR).toString();
    }

    return QString();
}

QString Angel::manufacturer() const
{
    QSettings settings;
    if(settings.value(SETTING_MF).toString().length() > 0) {
        return settings.value(SETTING_MF).toString();
    }

    return QString();
}

QString Angel::modelNumber() const
{
    QSettings settings;
    if(settings.value(SETTING_MODEL).toString().length() > 0) {
        return settings.value(SETTING_MODEL).toString();
    }

    return QString();
}

QString Angel::serialNumber() const
{
    QSettings settings;
    if(settings.value(SETTING_SERIAL).toString().length() > 0) {
        return settings.value(SETTING_SERIAL).toString();
    }

    return QString();
}

int Angel::battery() const 
{
    return _batteryLevel;
}

void Angel::connectSensor()
{
    if(hasSensor()) {
        qDebug() << "Trying to connect to sensor: " << _sensor->address();
        _sensor->connectPeripheral();
    }

}

void Angel::disconnectSensor()
{
    if(hasSensor()) {
        qDebug() << "Disconnecting from sensor: " << _sensor->address();
        _sensor->disconnectPeripheral();
        _batteryLevel = 0;
        Q_EMIT batteryChanged();
    }
}

void Angel::handleDeviceConnected()
{
	qDebug() << "Sensor connected";
	if (_sensor->services().isEmpty()) {
		qDebug() << "Trying to discover services";
		_sensor->discoverServices();
	} else {
		// Directly use the services in cache
		handleDeviceServices();
	}
    Q_EMIT connectionChanged();
}

void Angel::handleDeviceDisconnected()
{
	qDebug() << "Sensor disconnected";
    Q_EMIT connectionChanged();
}

void Angel::handleDeviceServices()
{
	QList<GatoService> services = _sensor->services();
	qDebug() << "Total services found: " << services.size();
	foreach (const GatoService &s, services) {
        if(s.uuid() == ServiceBatteryUuid || s.uuid() == ServiceDeviceInformationUuid) {
            qDebug() << "Processing service: " << s.uuid();
            _sensor->discoverCharacteristics(s);
        }
	}
}

void Angel::handleDeviceCharacteristics(const GatoService &service)
{
	qDebug() << "Got characteristics for service: " << service.uuid();
	foreach (const GatoCharacteristic &c, service.characteristics()) {
        if(c.uuid() == CharBatteryLevelUuid) {
            qDebug() << "Subscribing to battery level notifications";
			_sensor->setNotification(c, true);
        } else if(c.uuid() == CharManufacturerNameUuid) {
            qDebug() << "Reading manufacturer name";
			_sensor->readValue(c);
        } else if(c.uuid() == CharModelNumberUuid) {
            qDebug() << "Reading model number";
			_sensor->readValue(c);
        } else if(c.uuid() == CharSerialNumberUuid) {
            qDebug() << "Reading model serial";
			_sensor->readValue(c);
        } else {
            qDebug() << "Ignoring characteristic " << c.uuid() << " for service " << service.uuid();
        }
	}
}

void Angel::handleDeviceUpdate(const GatoCharacteristic &characteristic, const QByteArray &value)
{
    QSettings settings;
    if(characteristic.uuid() == CharBatteryLevelUuid) {
        _batteryLevel = (int)value.at(0);
        Q_EMIT batteryChanged();
    } else if(characteristic.uuid() == CharManufacturerNameUuid) {
        settings.setValue(SETTING_MF, QString::fromUtf8(value.data()));
    } else if(characteristic.uuid() == CharModelNumberUuid) {
        settings.setValue(SETTING_MODEL, QString::fromUtf8(value.data()));
    } else if(characteristic.uuid() == CharSerialNumberUuid) {
        settings.setValue(SETTING_SERIAL, QString::fromUtf8(value.data()));
    } else {
        qWarning() << "Invalid characteristic " << characteristic.uuid();
    }
}
