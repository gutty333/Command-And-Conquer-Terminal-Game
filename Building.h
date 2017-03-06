#include <iostream>
#include <string>
#include <vector>
#include "Upgrade.h"
using namespace std;


#ifndef BUILDING_H
#define BUILDING_H

class Building
{
	protected:
		string name;
		int power;
		int hitPoint;
		int	hitPointFull;
		int cost;
		vector <string> requirements;
		vector <Upgrade> upgradesProvided;
		bool online;
		bool supportStructure;
		bool airField;
		bool refinery;
		bool powerProvider;
		bool upgradeStructure;

	public:
		Building();

		void setHitPoint(int);
		void setOnline(bool);

		string getName();
		int getPower();
		int getHitPoint();
		int getHitPointFull();
		int getCost();
		Upgrade getUpgrade(int);
		bool getOnline();
		bool getSupportStructure();
		bool getUpgradeStructure();
		bool getAirField();
		bool getRefinery();
		bool getPowerProvider();
		vector <string> getRequirements();
		void printUpgradeList();
		virtual void printInfo();
		
		virtual void addAirUnit(string) {};
		virtual void removeAirUnit(int) {};
		virtual string getAirUnitName(int) { return ""; };
		virtual int getTotalAirUnit() { return 0; };
};

#endif