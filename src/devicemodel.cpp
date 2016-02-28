#include "devicemodel.h"
#include <QDebug>


DeviceModel::DeviceModel(QObject *parent) :
    QAbstractListModel(parent)
{
    _roles[NameRole] = "name";
    _roles[AddressRole] = "address";
}

DeviceModel::~DeviceModel()
{
    m_devices.clear();
}

int DeviceModel::count() const
{
    return rowCount();
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_devices.count();
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_devices.count())
        return QVariant();

    DeviceInfo *d = m_devices.at(index.row());

    switch (role) {
    case NameRole:
        return QVariant::fromValue(d->getName());
        break;
    case AddressRole:
        return QVariant::fromValue(d->getAddress());
        break;
    default:
        return QVariant();
        break;
    }
}

void DeviceModel::clear()
{
    qDeleteAll(m_devices);
    m_devices.clear();
}

void DeviceModel::addDevice(DeviceInfo *device)
{
    beginInsertRows(QModelIndex(),m_devices.count(),m_devices.count());
    m_devices.append(device);
    endInsertRows();
    Q_EMIT countChanged();
}
