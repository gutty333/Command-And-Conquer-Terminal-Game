#include "Building.h"
#include "ConstructionYard.h"
#include "PowerPlant.h"
#include "Refinery.h"
#include "Barracks.h"
#include "WarFactory.h"
#include "CommandPost.h"
#include "Airfield.h"
#include "Armory.h"
#include "TechCenter.h"
#include "CommandLink.h"

// List of GDI buildings
const string GDI[] = { "Construction Yard" , "Power Plant", "Refinery", "Barracks", "War Factory", "Command Post", "Airfield" , "Armory", "Tech Center", "Space Command Uplink" };

// Constructor
Building::Building()
{
	name = "";
	power = hitPoint = cost = hitPointFull = 0;
	online = true;
	supportStructure = false;
}

// Setter Method
void Building::setHitPoint(int newHealth)
{
	hitPoint = newHealth;
}
void Building::setOnline(bool powerStatus)
{
	online = powerStatus;
}

// Getter Methods
string Building::getName()
{
	return name;
}
int Building::getPower()
{
	return power;
}
int Building::getHitPoint()
{
	return hitPoint;
}
int Building::getHitPointFull()
{
	return hitPointFull;
}
int Building::getCost()
{
	return cost;
}
bool Building::getOnline()
{
	return online;
}
bool Building::getSupportStructure()
{
	return supportStructure;
}
vector <string> Building::getRequirements()
{
	return requirements;
}

// Info Method
void Building::printInfo()
{
	cout << "\tName: " << name << endl;
	cout << "\tPower: " << power << endl;
	cout << "\tCost: " << cost << endl;
	cout << "\tHit points: " << hitPoint << "/" << hitPointFull << endl;
	cout << (online ? "\tBuilding is online" : "\tBuilding is offline") << endl;
}

// Child Constructors
ConstructionYard::ConstructionYard()
{
	name = GDI[0];
	power = 10;
	hitPoint = hitPointFull = 20000;
	cost = 3500;
}
PowerPlant::PowerPlant()
{
	name = GDI[1];
	power = 20;
	hitPoint = 1500;
	hitPointFull = 4000;
	cost = 700;

	requirements.push_back(GDI[0]);
}
Refinery::Refinery()
{
	name = GDI[2];
	power = -15;
	hitPoint = hitPointFull = 10000;
	cost = 3000;

	requirements.push_back(GDI[0]);
}
Barracks::Barracks()
{
	name = GDI[3];
	power = -5;
	hitPoint = hitPointFull = 3000;
	cost = 500;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[1]);
}
WarFactory::WarFactory()
{
	name = GDI[4];
	power = -7;
	hitPoint = hitPointFull = 10000;
	cost = 2000;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[1]);
	requirements.push_back(GDI[2]);
}
CommandPost::CommandPost()
{
	name = GDI[5];
	power = -9;
	hitPoint = hitPointFull = 5000;
	cost = 1500;
	supportStructure = true;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[1]);
	requirements.push_back(GDI[2]);
}
AirField::AirField()
{
	name = GDI[6];
	power = -8;
	hitPoint = hitPointFull = 4000;
	cost = 1000;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[5]);
}
Armory::Armory()
{
	name = GDI[7];
	power = -7;
	hitPoint = hitPointFull = 3000;
	cost = 1000;
	supportStructure = true;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[1]);
	requirements.push_back(GDI[3]);
}
TechCenter::TechCenter()
{
	name = GDI[8];
	power = -12;
	hitPoint = hitPointFull = 10000;
	cost = 4000;
	supportStructure = true;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[5]);
}
CommandLink::CommandLink()
{
	name = GDI[9];
	power = -15;
	hitPoint = hitPointFull = 3000;
	cost = 3000;
	supportStructure = true;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[8]);
}