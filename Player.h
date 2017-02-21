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
		bool getAlive();
		int getTotalBuildings();
		int getTotalUnits();

		void sellBuilding(int);
		void buildBuilding(Building*);
		void buildUnit(Unit*);
		void destroyUnit(int, int);
		bool needsRepair(int);
		void repairBuilding(int);
		void repairBuilding2(int);

		void managePower(int);
		void checkPower();
		void checkAlive();
		void harvest();
		void buyUpgrades();

		void printUnits();
		void printUnitList();
		void printBuildings();
		void printBuildingList();
};

#endif