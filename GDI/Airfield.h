#include "../Building.h"

#ifndef AIRFIELD_H
#define AIRFIELD_H

class AirField :public Building
{
private:
	int totalAirUnits;
	vector <string> airUnits;

public:
	AirField();
	virtual void printInfo();
	virtual void addAirUnit(string);
	virtual string getAirUnitName(int);
	virtual void removeAirUnit(int);
	virtual int getTotalAirUnit();
};

#endif 