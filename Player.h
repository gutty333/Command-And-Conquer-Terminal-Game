#include "Building.h"
#include "Unit.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	private:
		int resources;
		int currentPower;
		int requiredPower;
		string faction;
		bool alive;
		bool lowPower;
		vector <Building*> buildings;
		vector <Unit*> units;
		vector <Building*> offlineBuildings;
		vector <Upgrade> currentUpgrades;

	public:
		Player();

		void setResources(int);
		void setCurrentPower(int);
		void setRequiredPower(int);

		int getResources();
		int getCurrentPower();
		int getRequiredPower();
		string getFaction();
		bool getAlive();
		int getTotalBuildings();
		int getTotalUnits();
		int getTotalSpecificUnit(string);

		void sellBuilding(int&);
		void buildBuilding(int&, vector <string>);
		void buildUnit(int&, vector <string>, vector <string>, vector <string>);
		void destroyUnit(int, int);
		bool needsRepair(int);
		void repairBuilding(int);
		void repairBuilding2(int);

		void managePower(int&);
		void checkPower();
		void checkAlive();
		void harvest();
		void buyUpgrades(int&);

		void printUnits();
		void printUnitList();
		void printBuildings();
		void printBuildingList();
		void printUpgrades();
};

#endif