#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QString>
#include <QObject>
#include "libgato/gato.h"

class DeviceInfo: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName READ getName NOTIFY deviceChanged)
    Q_PROPERTY(QString deviceAddress READ getAddress NOTIFY deviceChanged)
public:
    DeviceInfo(const GatoPeripheral *device);
    void setDevice(const GatoPeripheral *device);
    QString getName() const { return m_device->name(); }
    QString getAddress() const;
    const GatoPeripheral* getDevice() const;

signals:
    void deviceChanged();

private:
    const GatoPeripheral *m_device;
};

#endif // DEVICEINFO_H
