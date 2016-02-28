#include "gatoconnectionparameters.h"
#include <QSharedData>

struct GatoConnectionParametersPrivate : public QSharedData
{
	int connIntervalMin;
	int connIntervalMax;
	int slaveLatency;
	int supervisionTimeout;
};

GatoConnectionParameters::GatoConnectionParameters()
	: d(new GatoConnectionParametersPrivate)
{
}

GatoConnectionParameters::GatoConnectionParameters(const GatoConnectionParameters &o)
	: d(o.d)
{
}

GatoConnectionParameters::~GatoConnectionParameters()
{
}

int GatoConnectionParameters::connectionIntervalMin() const
{
	return d->connIntervalMin;
}

void GatoConnectionParameters::setConnectionIntervalMin(int interval)
{
	d->connIntervalMin = interval;
}

int GatoConnectionParameters::connectionIntervalMax() const
{
	return d->connIntervalMax;
}

void GatoConnectionParameters::setConnectionIntervalMax(int interval)
{
	d->connIntervalMax = interval;
}

void GatoConnectionParameters::setConnectionInterval(int min, int max)
{
	d->connIntervalMin = min;
	d->connIntervalMax = max;
}

int GatoConnectionParameters::slaveLatency() const
{
	return d->slaveLatency;
}

void GatoConnectionParameters::setSlaveLatency(int latency)
{
	d->slaveLatency = latency;
}

int GatoConnectionParameters::supervisionTimeout() const
{
	return d->supervisionTimeout;
}

void GatoConnectionParameters::setSupervisionTimeout(int timeout)
{
	d->supervisionTimeout = timeout;
}

GatoConnectionParameters &GatoConnectionParameters::operator=(const GatoConnectionParameters &o)
{
	if (this != &o)
		d.operator=(o.d);
	return *this;
}
