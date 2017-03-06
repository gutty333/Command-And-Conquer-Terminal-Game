#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef UNIT_H
#define UNIT_H

class Unit
{
	protected:
		string name;
		string type;
		string description;
		int hitPoint;
		int cost;
		vector <string> requirements;
		vector <string> combatAccess;
		vector <string> upgrades;
		bool specialAirUnit;
		bool engineer;

	public:
		Unit();
		void setHitPoint(int);
		void addUpgrade(string);

		string getName();
		string getType();
		string getDescription();
		int getHitPoint();
		int getCost();
		bool getAirUnit();
		bool getEngineer();
		vector <string> getRequirements();
		vector <string> getCombatAccess();
		void printInfo();
};

#endif 