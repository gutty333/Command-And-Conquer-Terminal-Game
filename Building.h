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
		vector <string> getRequirements();
		void printUpgradeList();
		virtual void printInfo();
		
		virtual void addAirUnit() {};
		virtual void removeAirUnit() {};
		virtual int getTotalAirUnit() { return 0; };
};

#endif