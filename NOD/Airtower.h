#include "../Building.h"

#ifndef AIRTOWER_H
#define AIRTOWER_H

class AirTower :public Building
{
private:
	int totalAirUnits;
	vector <string> airUnits;

public:
	AirTower();
	virtual void printInfo();
	virtual void addAirUnit(string);
	virtual string getAirUnitName(int);
	virtual void removeAirUnit(int);
	virtual int getTotalAirUnit();
};

#endif 