#include "Upgrade.h"

// Constructor
Upgrade::Upgrade(string name, string info, int price)
{
	this->name = name;
	this->info = info;
	cost = price;
	active = false;
}

// Setter Method
void Upgrade::setActive(bool state)
{
	active = state;
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
bool Upgrade::getActive()
{
	return active;
}

// Print Method
void Upgrade::printInfo()
{
	cout << "\tName: " << name << endl;
	cout << "\tDescription: " << info << endl;
	cout << "\tCost: " << cost << endl;
	cout << "\tActive: " << active << endl;
}