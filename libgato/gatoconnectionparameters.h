#ifndef GATOCONNECTIONPARAMETERS_H
#define GATOCONNECTIONPARAMETERS_H

#include <QtCore/QObject>
#include <QtCore/QSharedDataPointer>

#include "libgato_global.h"

class GatoConnectionParametersPrivate;

/** These parameters determine the effective throughput of a Low Energy link,
 *  enabling custom balancing between power usage, bandwidth, and latency. */

class LIBGATO_EXPORT GatoConnectionParameters
{
	Q_GADGET

public:
	GatoConnectionParameters();
	GatoConnectionParameters(const GatoConnectionParameters &o);
	~GatoConnectionParameters();

	// Units for all of this: milliseconds
	// TODO Need to document

	// Connection interval: generally, lower connection interval increases throughput.
	// Units: microseconds (µs!)

	int connectionIntervalMin() const;
	void setConnectionIntervalMin(int interval);

	int connectionIntervalMax() const;
	void setConnectionIntervalMax(int interval);

	void setConnectionInterval(int min, int max);

	// TODO Document
	// Units: miliseconds (ms!)
	int slaveLatency() const;
	void setSlaveLatency(int latency);

	// Units: miliseconds
	int supervisionTimeout() const;
	void setSupervisionTimeout(int timeout);

	GatoConnectionParameters &operator=(const GatoConnectionParameters &o);

private:
	QSharedDataPointer<GatoConnectionParametersPrivate> d;
};

#endif // GATOCONNECTIONPARAMETERS_H
