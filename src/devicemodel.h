#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>
#include "libgato/gato.h"

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

    void addDevice(GatoPeripheral *device);
    GatoPeripheral* getDevice(int index);
    void clear();
    int count() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const { return _roles; }

Q_SIGNALS:
    void countChanged();

private:
    QHash<int, QByteArray> _roles;
    QList<GatoPeripheral *> m_devices;

};
#endif // DEVICEMODEL_H
