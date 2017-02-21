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
		int total;
		vector <string> requirements;
		vector <string> combatAccess;
		bool specialAirUnit;

	public:
		Unit();

		void setHitPoint(int);
		void setTotal(int);

		string getName();
		string getType();
		string getDescription();
		int getHitPoint();
		int getCost();
		int getTotal();
		bool getAirUnit();
		vector <string> getRequirements();
		vector <string> getCombatAccess();
		void printInfo();
};

#endif 