/*
 * Copyright (C) 2016 Andrew E. Bruno <aeb@qnot.org>
 *
 * This file is part of AngelFish.
 * 
 * AngelFish is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AngelFish is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AngelFish.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include "angel.h"

Angel::Angel()
{
    _bleManager = new GatoCentralManager(this);

    _sensor = NULL;

    connect(_bleManager, SIGNAL(discoveredPeripheral(GatoPeripheral *, int)),
            this, SLOT(addDevice(GatoPeripheral *, int)));

    QSettings settings;
    if(settings.value(SETTING_ADDR).toString().length() > 0) {
        qWarning() << "Found device: " << settings.value(SETTING_ADDR).toString();
        setSensor(settings.value(SETTING_ADDR).toString());
    }
}

Angel::~Angel()
{
    _dmodel.clear();
    _bleManager->stopScan();
    if(hasSensor()) {
        disconnectSensor();
    }

    delete _bleManager;
    delete _sensor;
}

void Angel::setSensor(QString address)
{
    _sensor = new GatoPeripheral(GatoAddress(address));
    connect(_sensor, SIGNAL(connected()), this, SLOT(handleDeviceConnected()));
    connect(_sensor, SIGNAL(disconnected()), this, SLOT(handleDeviceDisconnected()));
	connect(_sensor, SIGNAL(servicesDiscovered()), this, SLOT(handleDeviceServices()));

    foreach(GatoUUID key, _services.keys()) {
        _services.value(key)->setSensor(_sensor);
    }
}

void Angel::deviceSearch()
{
    qWarning() << "Starting device search";
    qWarning() << "Count " << _dmodel.count();
    _dmodel.clear();
    _bleManager->scanForPeripherals();
}

void Angel::stopSearch()
{
    qWarning() << "Stopping device search";
    qWarning() << "Count " << _dmodel.count();
    _bleManager->stopScan();
}

void Angel::addDevice(GatoPeripheral *peripheral, int rssi)
{
    if(peripheral->name().contains("Angel", Qt::CaseInsensitive)) {
        qWarning() << "Discovered LE Device name: " << peripheral->name() << " Address: "
                   << peripheral->address().toString();
        _dmodel.addDevice(peripheral);
        qWarning() << "Count " << _dmodel.count();
    }
}

void Angel::setupNewDevice(int index)
{
    qWarning() << "Setting up new device";
    GatoPeripheral* d = _dmodel.getDevice(index);
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
    settings.setValue(SETTING_HWREV, "");
    settings.setValue(SETTING_FIRMREV, "");
    settings.setValue(SETTING_SOFTREV, "");
    settings.sync();

    setSensor(d->address().toString());

    _dmodel.clear();
    Q_EMIT sensorChanged();
}

DeviceModel* Angel::devices()
{
    return &_dmodel;
}

bool Angel::hasSensor() const
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

QString Angel::sensorState() const
{
    if(hasSensor()) {
        if(_sensor->state() == GatoPeripheral::StateConnected) {
            return QString("Connected");
        } else if(_sensor->state() == GatoPeripheral::StateConnecting) {
            return QString("Connecting");
        } else if(_sensor->state() == GatoPeripheral::StateDisconnected) {
            return QString("Disconnected");
        }
    }

    return QString("Disconnected");
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

void Angel::connectSensor()
{
    if(hasSensor()) {
        qDebug() << "Trying to connect to sensor: " << _sensor->address();
        Q_EMIT connectionChanged();
        Q_EMIT sensorStateChanged();
        _sensor->connectPeripheral();
    }

}

void Angel::disconnectSensor()
{
    if(hasSensor()) {
        qDebug() << "Disconnecting from sensor: " << _sensor->address();
        _sensor->disconnectPeripheral();
    }
}

void Angel::registerService(AngelService *service)
{
    _services.insert(service->uuid(), service);
    if(_sensor != NULL) {
        service->setSensor(_sensor);
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
    Q_EMIT sensorStateChanged();
}

void Angel::handleDeviceDisconnected()
{
	qDebug() << "Sensor disconnected";
    Q_EMIT connectionChanged();
    Q_EMIT sensorStateChanged();
}

void Angel::handleDeviceServices()
{
	QList<GatoService> services = _sensor->services();
	qDebug() << "Total services found: " << services.size();
	foreach (const GatoService &s, services) {
        if(_services.contains(s.uuid())) {
            qDebug() << "Processing service: " << s.uuid();
            _sensor->discoverCharacteristics(s);
        }
	}
}
