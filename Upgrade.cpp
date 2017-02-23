#include "Upgrade.h"

// Constructor
Upgrade::Upgrade(string name, string info, int price)
{
	this->name = name;
	this->info = info;
	cost = price;
}

// Getter Method
string Upgrade::getName()
{
	return name;
}
string Upgrade::getInfo()
{
	return info;
}
int Upgrade::getCost()
{
	return cost;
}

// Print Method
void Upgrade::printInfo()
{
	cout << "\tName: " << name << endl;
	cout << "\tDescription: " << info << endl;
	cout << "\tCost: " << cost << endl;
}

// Add Units Upgrading Method
// This is the list of units receiving the upgrade
void Upgrade::addUnit(string unitName)
{
	unitsUpgrading.push_back(unitName);
}

// Get Unit Method
string Upgrade::getUnit(int index)
{
	return unitsUpgrading[index];
}

// Get Unit Total Method
int Upgrade::getTotaUnitsUpgrading()
{
	return unitsUpgrading.size();
}