#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>
#include "deviceinfo.h"

QT_USE_NAMESPACE
class DeviceModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum DeviceRoles {
        NameRole = Qt::UserRole + 1,
        AddressRole
    };

    explicit DeviceModel(QObject *parent = 0);
    virtual ~DeviceModel();

    void addDevice(DeviceInfo *device);
    void clear();
    int count() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const { return _roles; }

Q_SIGNALS:
    void countChanged();

private:
    QHash<int, QByteArray> _roles;
    QList<DeviceInfo *> m_devices;

};
#endif // DEVICEMODEL_H
