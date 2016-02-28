#include "libgato/gato.h"
#include "deviceinfo.h"

DeviceInfo::DeviceInfo(const GatoPeripheral *p):
    QObject()
{
    m_device = p;
}

const GatoPeripheral* DeviceInfo::getDevice() const
{
    return m_device;
}

QString DeviceInfo::getAddress() const
{
    return m_device->address().toString();
}

void DeviceInfo::setDevice(const GatoPeripheral *device)
{
    m_device = device;
    Q_EMIT deviceChanged();
}
