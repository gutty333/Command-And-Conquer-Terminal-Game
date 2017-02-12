#include <iostream>
#include <string>
#include <vector>
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
		bool online;
		bool supportStructure;

	public:
		Building();

		void setHitPoint(int);
		void setOnline(bool);

		string getName();
		int getPower();
		int getHitPoint();
		int getHitPointFull();
		int getCost();
		bool getOnline();
		bool getSupportStructure();
		vector <string> getRequirements();
		void printInfo();
};

#endif