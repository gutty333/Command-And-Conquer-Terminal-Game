#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef UPGRADE_H
#define UPGRADE_H

class Upgrade
{
private:
	string name;
	string info;
	int cost;
	vector <string> unitsUpgrading;

public:
	Upgrade(string, string, int);
	string getName();
	string getInfo();
	int getCost();
	void printInfo();
	void addUnit(string);
	string getUnit(int);
	int getTotalUnitsUpgrading();
};

#endif