#ifndef GATOPERIPHERAL_H
#define GATOPERIPHERAL_H

#include <QtCore/QObject>
#include "libgato_global.h"
#include "gatouuid.h"
#include "gatoaddress.h"
#include "gatoconnectionparameters.h"

class GatoService;
class GatoCharacteristic;
class GatoDescriptor;
class GatoPeripheralPrivate;

class LIBGATO_EXPORT GatoPeripheral : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(GatoPeripheral)
	Q_ENUMS(State)
	Q_ENUMS(WriteType)
	Q_FLAGS(PeripheralConnectOptions)
	Q_PROPERTY(GatoAddress address READ address)
	Q_PROPERTY(QString name READ name NOTIFY nameChanged)

public:
	GatoPeripheral(const GatoAddress& addr, QObject *parent = 0);
	~GatoPeripheral();

	enum PeripheralConnectOption {
		PeripheralConnectOptionRequireEncryption = 1 << 0
	};
	Q_DECLARE_FLAGS(PeripheralConnectOptions, PeripheralConnectOption)

	enum State {
		StateDisconnected,
		StateConnecting,
		StateConnected
	};

	enum WriteType {
		WriteWithResponse = 0,
		WriteWithoutResponse
	};

	State state() const;
	GatoAddress address() const;
	QString name() const;
	QList<GatoService> services() const;

	GatoConnectionParameters connectionParameters() const;
	bool setConnectionParameters(const GatoConnectionParameters &params);

	void parseEIR(quint8 data[], int len);
	bool advertisesService(const GatoUUID &uuid) const;

public slots:
	void connectPeripheral(PeripheralConnectOptions options = 0);
	void disconnectPeripheral();

	void discoverServices();
	void discoverServices(const QList<GatoUUID>& serviceUUIDs);
	void discoverCharacteristics(const GatoService &service);
	void discoverCharacteristics(const GatoService &service, const QList<GatoUUID>& characteristicUUIDs);
	void discoverDescriptors(const GatoCharacteristic &characteristic);

	void readValue(const GatoCharacteristic &characteristic);
	void readValue(const GatoDescriptor &descriptor);
	void writeValue(const GatoCharacteristic &characteristic, const QByteArray &data, WriteType type = WriteWithResponse);
	void writeValue(const GatoDescriptor &descriptor, const QByteArray &data);
	void setNotification(const GatoCharacteristic &characteristic, bool enabled);

signals:
	void connected();
	void disconnected();

	void nameChanged();
	void servicesDiscovered();
	void characteristicsDiscovered(const GatoService &service);
	void descriptorsDiscovered(const GatoCharacteristic &characteristic);

	void valueUpdated(const GatoCharacteristic &characteristic, const QByteArray &value);
	void descriptorValueUpdated(const GatoDescriptor &descriptor, const QByteArray &value);

private:
	GatoPeripheralPrivate *const d_ptr;
};

#endif // GATOPERIPHERAL_H
