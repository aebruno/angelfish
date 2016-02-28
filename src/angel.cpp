#include "angel.h"

Angel::Angel():
    m_currentDevice(new GatoPeripheral(GatoAddress()))
{
    m_deviceDiscoveryAgent = new GatoCentralManager(this);

    connect(m_deviceDiscoveryAgent, SIGNAL(discoveredPeripheral(GatoPeripheral *, int)),
            SLOT(addDevice(GatoPeripheral *, int)));
}

Angel::~Angel()
{
    d_model.clear();
    m_deviceDiscoveryAgent->stopScan();
}

void Angel::deviceSearch()
{
    qWarning() << "Starting device search";
    qWarning() << "Count " << d_model.count();
    d_model.clear();
    m_deviceDiscoveryAgent->scanForPeripherals();
}

void Angel::stopSearch()
{
    qWarning() << "Stopping device search";
    qWarning() << "Count " << d_model.count();
    m_deviceDiscoveryAgent->stopScan();
    d_model.clear();
}

void Angel::addDevice(GatoPeripheral *peripheral, int rssi)
{
    qWarning() << "Discovered LE Device name: " << peripheral->name() << " Address: "
               << peripheral->address().toString();
    DeviceInfo *dev = new DeviceInfo(peripheral);
    d_model.addDevice(dev);
    qWarning() << "Count " << d_model.count();
}

QString Angel::error() const
{
    return m_error;
}

DeviceModel* Angel::devices()
{
    return &d_model;
}

void Angel::setError(const QString &error)
{
    if (m_error != error) {
        m_error = error;
        Q_EMIT errorChanged();
    }
}
