#include "Building.h"

#ifndef AIRFIELD_H
#define AIRFIELD_H

class AirField :public Building
{
private:
	int totalAirUnits;

public:
	AirField();
	virtual void printInfo();
	virtual bool airFieldSpace();
	virtual void addAirUnit();
};

#endif 