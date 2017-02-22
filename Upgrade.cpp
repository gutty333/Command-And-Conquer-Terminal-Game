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