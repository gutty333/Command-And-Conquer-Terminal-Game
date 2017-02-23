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
// GDI Infantry Units
const string GDI_INFANTRY[] = { "Rifleman Squad", "Missile Squad", "Engineer", "Grenadier Squad", "Sniper Team", "Zone Trooper" };
// GDI Vehicle Units
const string GDI_VEHICLE[] = { "CC-6 Pitbull", "Guardian APC", "MBT-6 Predator", "Harvester", "Mobile Construction Vehicle", "Rig", "Juggernaut MK. III", "Mammoth MK. III" };
// GDI Air Units
const string GDI_AIR[] = { "A-15 Orca", "Firehawk", "Hammerhead" };

// Constructor
Building::Building()
{
	name = "";
	power = hitPoint = cost = hitPointFull = 0;
	online = true;
	supportStructure = false;
	airField = false;
	upgradeStructure = false;
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
bool Building::getUpgradeStructure()
{
	return upgradeStructure;
}
vector <string> Building::getRequirements()
{
	return requirements;
}
Upgrade Building::getUpgrade(int index)
{
	return upgradesProvided[index];
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
// Print Upgrade Method
void Building::printUpgradeList()
{
	for (int x = 0; x < upgradesProvided.size(); x++)
	{
		cout << "\t" << x << ". " << upgradesProvided[x].getName() << endl;
	}
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
	upgradeStructure = true;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[1]);
	requirements.push_back(GDI[2]);

	Upgrade upgradeOne("AP Ammo", "This upgrade bestows a firepower boost to Watchtowers, Hammerheads, Riflemen, and APCS, doubling their damage.", 2000);
	Upgrade upgradeTwo("Sensor Pod", "Sensor Pods can be equipped onto Orcas to allow them to launch stealth-detecting pods.", 500);

	upgradeOne.addUnit(GDI_INFANTRY[0]);
	upgradeOne.addUnit(GDI_VEHICLE[1]);
	upgradeOne.addUnit(GDI_AIR[2]);
	upgradeTwo.addUnit(GDI_AIR[0]);

	upgradesProvided.push_back(upgradeOne);
	upgradesProvided.push_back(upgradeTwo);
}
AirField::AirField()
{
	name = GDI[6];
	power = -8;
	hitPoint = hitPointFull = 4000;
	cost = 1000;
	airField = true;
	totalAirUnits = 0;

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
	upgradeStructure = true;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[1]);
	requirements.push_back(GDI[3]);

	Upgrade upgradeOne("Composite Armor", "Provides GDI Infantry with significantly more protection from hostile fire. It affects Rifleman Squads, Missile Squads, and Grenadiers.", 1500);
	Upgrade upgradeTwo("Power Pack", "Power Packs give Zone Troopers a 50% boost in health and also allow self-healing when the squad is idle.", 1000);
	Upgrade upgradeThree("Scanner Pack", "Equips Zone Troopers with scanner packs, increases their sight radius and allows them to detect stealth in a small radius.", 1000);

	upgradeOne.addUnit(GDI_INFANTRY[0]);
	upgradeOne.addUnit(GDI_INFANTRY[1]);
	upgradeOne.addUnit(GDI_INFANTRY[3]);
	upgradeTwo.addUnit(GDI_INFANTRY[5]);
	upgradeThree.addUnit(GDI_INFANTRY[5]);

	upgradesProvided.push_back(upgradeOne);
	upgradesProvided.push_back(upgradeTwo);
	upgradesProvided.push_back(upgradeThree);
}
TechCenter::TechCenter()
{
	name = GDI[8];
	power = -12;
	hitPoint = hitPointFull = 10000;
	cost = 4000;
	supportStructure = true;
	upgradeStructure = true;

	requirements.push_back(GDI[0]);
	requirements.push_back(GDI[5]);

	Upgrade upgradeOne("Mortar", "Pitbulls can be equipped with light mortars, which increase their effectiveness against infantry units and structures.", 1000);
	Upgrade upgradeTwo("Railgun", "Predator Tanks,Mammoth Tanks, Guardian Cannons, and Battle Bases all benefit from Railguns.", 4000);
	Upgrade upgradeThree("Stratofighter Boosters", "Stratofighter Boosters provide Firehawks with the ability to quickly accelerate into the stratosphere and fly almost instantaneously to any location.", 1000);

	upgradeOne.addUnit(GDI_VEHICLE[0]);
	upgradeTwo.addUnit(GDI_VEHICLE[2]);
	upgradeTwo.addUnit(GDI_VEHICLE[7]);
	upgradeThree.addUnit(GDI_AIR[1]);

	upgradesProvided.push_back(upgradeOne);
	upgradesProvided.push_back(upgradeTwo);
	upgradesProvided.push_back(upgradeThree);
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


// Air field child methods
void AirField::addAirUnit()
{
	totalAirUnits++;
}
void AirField::removeAirUnit()
{
	totalAirUnits--;
	if (totalAirUnits < 0)
	{
		totalAirUnits = 0;
	}
}
int AirField::getTotalAirUnit()
{
	return totalAirUnits;
}
void AirField::printInfo()
{
	cout << "\tName: " << name << endl;
	cout << "\tPower: " << power << endl;
	cout << "\tCost: " << cost << endl;
	cout << "\tHit points: " << hitPoint << "/" << hitPointFull << endl;
	cout << "\tSpace: " << totalAirUnits << "/" << 4 << endl;
	cout << (online ? "\tBuilding is online" : "\tBuilding is offline") << endl;
}