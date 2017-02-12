#include "Unit.h"
#include "Rifleman.h"
#include "MissileSquad.h"
#include "Engineer.h"
#include "Grenadier.h"
#include "SniperTeam.h"
#include "ZoneTrooper.h"

#include "Apc.h"
#include "Pitbull.h"
#include "Predator.h"
#include "Harvester.h"
#include "Mcv.h"
#include "Rig.h"
#include "Juggernaut.h"
#include "MammothTank.h"

#include "Orca.h"
#include "Firehawk.h"

// List of unit types
const string unitTypes[] = { "Infantry","Vehicle","Air" };

// List of GDI buildings
const string GDI[] = { "Construction Yard" , "Power Plant", "Refinery", "Barracks", "War Factory", "Command Post", "Airfield" , "Armory", "Tech Center", "Space Command Uplink" };
// GDI Infantry Units
const string GDI_INFANTRY[] = { "Rifleman Squad", "Missile Squad", "Engineer", "Grenadier Squad", "Sniper Team", "Zone Trooper" };
// GDI Vehicle Units
const string GDI_VEHICLE[] = { "CC-6 Pitbull", "Guardian APC","MBT-6 Predator", "Harvester", "Mobile Construction Vehicle", "Rig", "Juggernaut MK. III", "Mammoth MK. III" };
// GDI Air Units
const string GDI_AIR[] = { "A-15 Orca", "Firehawk" };

// Constructor
Unit::Unit()
{
	name = description = type = "";
	hitPoint = cost = total = 0;
}

// Setter Method
void Unit::setHitPoint(int x)
{
	hitPoint = x;
}
void Unit::setTotal(int x)
{
	total = x;
}

// Getter Methods
string Unit::getName()
{
	return name;
}
string Unit::getType()
{
	return type;
}
string Unit::getDescription()
{
	return description;
}
int Unit::getHitPoint()
{
	return hitPoint;
}
int Unit::getCost()
{
	return cost;
}
int Unit::getTotal()
{
	return total;
}
vector <string> Unit::getRequirements()
{
	return requirements;
}
vector <string> Unit::getCombatAccess()
{
	return combatAccess;
}

// Info Method
void Unit::printInfo()
{
	cout << "\tName: " << name << endl;
	cout << "\tYou have a total of " << total << " " << name << endl;
	cout << "\tType: " << type << endl;
	cout << "\tDescription: " << description << endl;;
	cout << "\tCost: " << cost << endl;
	cout << "\tHit points: " << hitPoint << endl;
	if (combatAccess.size() > 0)
	{
		cout << "\tThis unit can attack: " << endl;
		for (int x = 0; x < combatAccess.size(); x++)
		{
			cout << "\t" << combatAccess[x] << " Units" << endl;
		}
	}
	else
	{
		cout << "\tThis unit is unable to attack" << endl;
	}
}




// Child Constructors
Rifleman::Rifleman()
{
	name = GDI_INFANTRY[0];
	type = unitTypes[0];
	description = "Basic infantry";
	cost = 300;
	hitPoint = 450;
	requirements.push_back(GDI[3]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
MissileSquad::MissileSquad()
{
	name = GDI_INFANTRY[1];
	type = unitTypes[0];
	description = "Anti-armor and anti-air infantry";
	cost = 400;
	hitPoint = 600;
	requirements.push_back(GDI[3]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
Engineer::Engineer()
{
	name = GDI_INFANTRY[2];
	type = unitTypes[0];
	description = "Support infantry";
	cost = 500;
	hitPoint = 75;
	requirements.push_back(GDI[3]);
}
Grenadier::Grenadier()
{
	name = GDI_INFANTRY[3];
	type = unitTypes[0];
	description = "Anti-infantry infantry";
	cost = 800;
	hitPoint = 1248;
	requirements.push_back(GDI[3]);
	requirements.push_back(GDI[5]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
SniperTeam::SniperTeam()
{
	name = GDI_INFANTRY[4];
	type = unitTypes[0];
	description = "Recon infiltration anti-infantry";
	cost = 1000;
	hitPoint = 300;
	requirements.push_back(GDI[3]);
	requirements.push_back(GDI[5]);
	requirements.push_back(GDI[7]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
ZoneTrooper::ZoneTrooper()
{
	name = GDI_INFANTRY[5];
	type = unitTypes[0];
	description = "Heavy infantry";
	cost = 1300;
	hitPoint = 960;
	requirements.push_back(GDI[3]);
	requirements.push_back(GDI[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}

Apc::Apc()
{
	name = GDI_VEHICLE[0];
	type = unitTypes[1];
	description = "Troop carrier";
	cost = 700;
	hitPoint = 2800;
	requirements.push_back(GDI[4]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
Pitbull::Pitbull()
{
	name = GDI_VEHICLE[1];
	type = unitTypes[1];
	description = "Armed recon";
	cost = 700;
	hitPoint = 1450;
	requirements.push_back(GDI[4]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
Predator::Predator()
{
	name = GDI_VEHICLE[2];
	type = unitTypes[1];
	description = "Main battle tank";
	cost = 1100;
	hitPoint = 3400;
	requirements.push_back(GDI[4]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
Harvester::Harvester()
{
	name = GDI_VEHICLE[3];
	type = unitTypes[1];
	description = "Resource gatherer";
	cost = 1500;
	hitPoint = 5000;
}
Mcv::Mcv()
{
	name = GDI_VEHICLE[4];
	type = unitTypes[1];
	description = "Utility vehicle";
	cost = 3500;
	hitPoint = 5000;
	requirements.push_back(GDI[4]);
}
Rig::Rig()
{
	name = GDI_VEHICLE[5];
	type = unitTypes[1];
	description = "Support vehicle";
	cost = 2000;
	hitPoint = 2000;
	requirements.push_back(GDI[4]);
	requirements.push_back(GDI[5]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
Juggernaut::Juggernaut()
{
	name = GDI_VEHICLE[6];
	type = unitTypes[1];
	description = "Mobile artillery support";
	cost = 2200;
	hitPoint = 5000;
	requirements.push_back(GDI[4]);
	requirements.push_back(GDI[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
MammothTank::MammothTank()
{
	name = GDI_VEHICLE[7];
	type = unitTypes[1];
	description = "Assault";
	cost = 2500;
	hitPoint = 11500;
	requirements.push_back(GDI[4]);
	requirements.push_back(GDI[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}


Orca::Orca()
{
	name = GDI_AIR[0];
	type = unitTypes[2];
	description = "Gunship";
	cost = 1100;
	hitPoint = 1800;
	requirements.push_back(GDI[6]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
Firehawk::Firehawk()
{
	name = GDI_AIR[1];
	type = unitTypes[2];
	description = "Fighter bomber";
	cost = 1500;
	hitPoint = 2625;
	requirements.push_back(GDI[6]);
	requirements.push_back(GDI[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}