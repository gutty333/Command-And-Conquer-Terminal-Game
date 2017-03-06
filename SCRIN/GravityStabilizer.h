#include "../Building.h"

#ifndef GRAVITYSTABILIZER_H
#define GRAVITYSTABILIZER_H

class GravityStabilizer :public Building
{
private:
	int totalAirUnits;
	vector <string> airUnits;

public:
	GravityStabilizer();
	virtual void printInfo();
	virtual void addAirUnit(string);
	virtual string getAirUnitName(int);
	virtual void removeAirUnit(int);
	virtual int getTotalAirUnit();
};

#endif 