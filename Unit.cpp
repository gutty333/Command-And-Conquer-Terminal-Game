#include "Unit.h"
#include "Harvester.h"
#include "Mcv.h"

#include "GDI/Rifleman.h"
#include "GDI/MissileSquad.h"
#include "GDI/Engineer.h"
#include "GDI/Grenadier.h"
#include "GDI/SniperTeam.h"
#include "GDI/ZoneTrooper.h"
#include "GDI/Apc.h"
#include "GDI/Pitbull.h"
#include "GDI/Predator.h"
#include "GDI/Rig.h"
#include "GDI/Juggernaut.h"
#include "GDI/MammothTank.h"
#include "GDI/Orca.h"
#include "GDI/Firehawk.h"
#include "GDI/HammerHead.h"

#include "NOD\MilitantSquad.h"
#include "NOD\RocketSquad.h"
#include "NOD\Saboteur.h"
#include "NOD\Fanatic.h"
#include "NOD\ShadowTeam.h"
#include "NOD\BlackHand.h"
#include "NOD\RaiderBuggy.h"
#include "NOD\AttackBike.h"
#include "NOD\ScorpionTank.h"
#include "NOD\FlameTank.h"
#include "NOD\StealthTank.h"
#include "NOD\Avatar.h"
#include "NOD\Venom.h"
#include "NOD\Vertigo.h"

#include "SCRIN\Buzzer.h"
#include "SCRIN\Disintegrator.h"
#include "SCRIN\Assimilator.h"
#include "SCRIN\ShockTrooper.h"
#include "SCRIN\Ravager.h"
#include "SCRIN\GunWalker.h"
#include "SCRIN\Seeker.h"
#include "SCRIN\ScrinHarvester.h"
#include "SCRIN\DevourerTank.h"
#include "SCRIN\Corrupter.h"
#include "SCRIN\Tripod.h"
#include "SCRIN\Stormrider.h"
#include "SCRIN\DroneShip.h"
#include "SCRIN\DevastatorWarship.h"
#include "SCRIN\PlanetaryAssault.h"

// List of unit types
const string unitTypes[] = { "Infantry","Vehicle","Air" };

// List of GDI buildings
const string GDI[] = { "Construction Yard" , "Power Plant", "Refinery", "Barracks", "War Factory", "Command Post", "Airfield" , "Armory", "Tech Center", "Space Command Uplink" };
// List of NOD buildings
const string NOD[] = { "Construction Yard" , "Power Plant", "Refinery", "Hand of Nod", "War Factory", "Operations Center", "Airtower" , "Secret Shrine", "Tech Lab", "Tiberium Chemical Plant" };
// List of SCRIN buildings
const string SCRIN[] = { "Drone Platform" , "Reactor", "Extractor", "Portal", "Warp Sphere", "Nerve Center", "Gravity Stabilizer" , "Stasis Chamber", "Technology Assembler", "Signal Transmitter" };

// GDI Infantry Units
const string GDI_INFANTRY[] = { "Rifleman Squad", "Missile Squad", "Engineer", "Grenadier Squad", "Sniper Team", "Zone Trooper" };
// GDI Vehicle Units
const string GDI_VEHICLE[] = { "CC-6 Pitbull", "Guardian APC", "MBT-6 Predator", "Harvester", "Mobile Construction Vehicle", "Rig", "Juggernaut MK. III", "Mammoth MK. III" };
// GDI Air Units
const string GDI_AIR[] = { "A-15 Orca", "Firehawk", "Hammerhead" };

// NOD Infantry Units
const string NOD_INFANTRY[] = { "Militant Squad", "Rocket Squad", "Saboteur", "Fanatic", "Shadow Team", "Black Hand" };
// NOD Vehicle Units
const string NOD_VEHICLE[] = { "Attack Bike", "Raider Buggy", "Scorpion Tank", "Harvester", "Mobile Construction Vehicle", "Flame Tank", "Stealth Tank", "Avatar" };
// NOD Air Units
const string NOD_AIR[] = { "Venom", "Vertigo" };

// SCRIN Infantry Units
const string SCRIN_INFANTRY[] = { "Buzzer", "Disintegrator", "Assimilator", "Shock Trooper", "Ravager" };
// SCRIN Vehicle Units
const string SCRIN_VEHICLE[] = { "Gun Walker", "Seeker", "Harvester", "Devourer Tank", "Corrupter", "Annihilator Tripod" };
// SCRIN Air Units
const string SCRIN_AIR[] = { "Stormrider", "Drone Ship","Devastator Warship", "Planetary Assault Carrier" };

// Constructor
Unit::Unit()
{
	name = description = type = "";
	hitPoint = cost = 0;
	specialAirUnit = false;
	engineer = false;
}

// Setter Method
void Unit::setHitPoint(int x)
{
	hitPoint = x;
}
void Unit::addUpgrade(string upgradeName)
{
	upgrades.push_back(upgradeName);
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
vector <string> Unit::getRequirements()
{
	return requirements;
}
vector <string> Unit::getCombatAccess()
{
	return combatAccess;
}
bool Unit::getAirUnit()
{
	return specialAirUnit;
}
bool Unit::getEngineer()
{
	return engineer;
}

// Info Method
void Unit::printInfo()
{
	cout << "\tName: " << name << endl;
	cout << "\tType: " << type << endl;
	cout << "\tDescription: " << description << endl;;
	cout << "\tCost: " << cost << endl;
	cout << "\tHit points: " << hitPoint << endl;
	if (combatAccess.size() > 0)
	{
		cout << "\tThis unit can attack: " << endl;
		for (int x = 0; x < combatAccess.size(); x++)
		{
			cout << "\t  " << combatAccess[x] << " Units" << endl;
		}
	}
	else
	{
		cout << "\tThis unit is unable to attack" << endl;
	}
	if (upgrades.size() > 0)
	{
		cout << "\tUpgrades: " << endl;
		for (int x = 0; x < upgrades.size(); x++)
		{
			cout << "\t  " << upgrades[x] << endl;
		}
	}
	else
	{
		cout << "\tUpgrades: None" << endl;
	}
}



// GDI Child Constructors
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
	engineer = true;
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
	name = GDI_VEHICLE[1];
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
	name = GDI_VEHICLE[0];
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
	requirements.push_back(GDI[4]);
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
	specialAirUnit = true;
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
	specialAirUnit = true;
	requirements.push_back(GDI[6]);
	requirements.push_back(GDI[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
HammerHead::HammerHead()
{
	name = GDI_AIR[2];
	type = unitTypes[2];
	description = "Transport gunship";
	cost = 1500;
	hitPoint = 2500;
	requirements.push_back(GDI[6]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}


// NOD Child Constructors
MilitantSquad::MilitantSquad()
{
	name = NOD_INFANTRY[0];
	type = unitTypes[0];
	description = "Basic infantry";
	cost = 200;
	hitPoint = 400;
	requirements.push_back(NOD[3]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
RocketSquad::RocketSquad()
{
	name = NOD_INFANTRY[1];
	type = unitTypes[0];
	description = "Anti-armor and anti-air infantry";
	cost = 400;
	hitPoint = 600;
	requirements.push_back(NOD[3]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
Saboteur::Saboteur()
{
	name = NOD_INFANTRY[2];
	type = unitTypes[0];
	description = "Support infantry";
	cost = 500;
	hitPoint = 75;
	engineer = true;
	requirements.push_back(NOD[3]);
}
Fanatic::Fanatic()
{
	name = NOD_INFANTRY[3];
	type = unitTypes[0];
	description = "Suicide attackers";
	cost = 700;
	hitPoint = 750;
	requirements.push_back(NOD[3]);
	requirements.push_back(NOD[5]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
ShadowTeam::ShadowTeam()
{
	name = NOD_INFANTRY[4];
	type = unitTypes[0];
	description = "Special forces";
	cost = 800;
	hitPoint = 600;
	requirements.push_back(NOD[3]);
	requirements.push_back(NOD[7]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
BlackHand::BlackHand()
{
	name = NOD_INFANTRY[5];
	type = unitTypes[0];
	description = "Elite Infantry";
	cost = 900;
	hitPoint = 3000;
	requirements.push_back(NOD[3]);
	requirements.push_back(NOD[5]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
RaiderBuggy::RaiderBuggy()
{
	name = NOD_VEHICLE[1];
	type = unitTypes[1];
	description = "Anti-infantry/anti-air scout";
	cost = 500;
	hitPoint = 1600;
	requirements.push_back(NOD[4]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
AttackBike::AttackBike()
{
	name = NOD_VEHICLE[0];
	type = unitTypes[1];
	description = "Armed reconnaissance Scout";
	cost = 600;
	hitPoint = 800;
	requirements.push_back(NOD[4]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
ScorpionTank::ScorpionTank()
{
	name = NOD_VEHICLE[2];
	type = unitTypes[1];
	description = "Medium assault vehicle";
	cost = 900;
	hitPoint = 2400;
	requirements.push_back(NOD[4]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
FlameTank::FlameTank()
{
	name = NOD_VEHICLE[5];
	type = unitTypes[1];
	description = "Anti-infantry/anti-structure tank";
	cost = 1200;
	hitPoint = 3700;
	requirements.push_back(NOD[4]);
	requirements.push_back(NOD[5]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
StealthTank::StealthTank()
{
	name = NOD_VEHICLE[6];
	type = unitTypes[1];
	description = "Recon/Support tank";
	cost = 1800;
	hitPoint = 1875;
	requirements.push_back(NOD[4]);
	requirements.push_back(NOD[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
Avatar::Avatar()
{
	name = NOD_VEHICLE[7];
	type = unitTypes[1];
	description = "Heavy Assault walker";
	cost = 2200;
	hitPoint = 11000;
	requirements.push_back(NOD[4]);
	requirements.push_back(NOD[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
Venom::Venom()
{
	name = NOD_AIR[0];
	type = unitTypes[2];
	description = "Multipurpose aircraft";
	cost = 900;
	hitPoint = 1800;
	requirements.push_back(NOD[6]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
Vertigo::Vertigo()
{
	name = NOD_AIR[1];
	type = unitTypes[2];
	description = "Stealth bomber";
	cost = 1800;
	hitPoint = 3000;
	specialAirUnit = true;
	requirements.push_back(NOD[6]);
	requirements.push_back(NOD[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}


// SCRIN Child Constructors
Buzzer::Buzzer()
{
	name = SCRIN_INFANTRY[0];
	type = unitTypes[0];
	description = "Antipersonnel";
	cost = 200;
	hitPoint = 112;
	requirements.push_back(SCRIN[3]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
Disintegrator::Disintegrator()
{
	name = SCRIN_INFANTRY[1];
	type = unitTypes[0];
	description = "Anti-vehicle/structure";
	cost = 300;
	hitPoint = 350;
	requirements.push_back(SCRIN[3]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
Assimilator::Assimilator()
{
	name = SCRIN_INFANTRY[2];
	type = unitTypes[0];
	description = "Support infantry";
	cost = 500;
	hitPoint = 75;
	engineer = true;
	requirements.push_back(SCRIN[3]);
}
ShockTrooper::ShockTrooper()
{
	name = SCRIN_INFANTRY[3];
	type = unitTypes[0];
	description = "Heavy infantry";
	cost = 800;
	hitPoint = 900;
	requirements.push_back(SCRIN[3]);
	requirements.push_back(SCRIN[5]);
	requirements.push_back(SCRIN[7]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
Ravager::Ravager()
{
	name = SCRIN_INFANTRY[4];
	type = unitTypes[0];
	description = "Elite Infantry";
	cost = 1200;
	hitPoint = 900;
	requirements.push_back(SCRIN[3]);
	requirements.push_back(SCRIN[5]);
	requirements.push_back(SCRIN[7]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
Seeker::Seeker()
{
	name = SCRIN_VEHICLE[1];
	type = unitTypes[1];
	description = "Light tank";
	cost = 800;
	hitPoint = 2100;
	requirements.push_back(SCRIN[4]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
GunWalker::GunWalker()
{
	name = SCRIN_VEHICLE[0];
	type = unitTypes[1];
	description = "Anti-infantry/anti-aircraft light walker";
	cost = 700;
	hitPoint = 2500;
	requirements.push_back(SCRIN[4]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
ScrinHarvester::ScrinHarvester()
{
	name = SCRIN_VEHICLE[2];
	type = unitTypes[1];
	description = "Resource gatherer";
	cost = 1500;
	hitPoint = 5000;
	requirements.push_back(SCRIN[4]);
}
DevourerTank::DevourerTank()
{
	name = SCRIN_VEHICLE[3];
	type = unitTypes[1];
	description = "Medium Tank";
	cost = 1600;
	hitPoint = 3200;
	requirements.push_back(SCRIN[4]);
	requirements.push_back(SCRIN[5]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
Corrupter::Corrupter()
{
	name = SCRIN_VEHICLE[4];
	type = unitTypes[1];
	description = "Support walker";
	cost = 1000;
	hitPoint = 3000;
	requirements.push_back(SCRIN[4]);
	requirements.push_back(SCRIN[5]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
Tripod::Tripod()
{
	name = SCRIN_VEHICLE[5];
	type = unitTypes[1];
	description = "Heavy assault walker";
	cost = 3000;
	hitPoint = 7500;
	requirements.push_back(SCRIN[4]);
	requirements.push_back(SCRIN[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
StormRider::StormRider()
{
	name = SCRIN_AIR[0];
	type = unitTypes[2];
	description = "Multirole aircraft";
	cost = 1500;
	hitPoint = 2800;
	specialAirUnit = true;
	requirements.push_back(SCRIN[6]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}
DroneShip::DroneShip()
{
	name = SCRIN_AIR[1];
	type = unitTypes[2];
	description = "Utility vehicle";
	cost = 3000;
	hitPoint = 5000;
	requirements.push_back(SCRIN[6]);
}
DevastatorWarship::DevastatorWarship()
{
	name = SCRIN_AIR[2];
	type = unitTypes[2];
	description = "Artillery battleship";
	cost = 2400;
	hitPoint = 6250;
	requirements.push_back(SCRIN[6]);
	requirements.push_back(SCRIN[8]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
}
PlanetaryAssault::PlanetaryAssault()
{
	name = SCRIN_AIR[3];
	type = unitTypes[2];
	description = "Heavy capital ship/aircraft carrier";
	cost = 3000;
	hitPoint = 10000;
	requirements.push_back(SCRIN[6]);
	requirements.push_back(SCRIN[8]);
	requirements.push_back(SCRIN[9]);
	combatAccess.push_back(unitTypes[0]);
	combatAccess.push_back(unitTypes[1]);
	combatAccess.push_back(unitTypes[2]);
}