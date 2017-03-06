#include "Building.h"
#include "ConstructionYard.h"
#include "PowerPlant.h"
#include "Refinery.h"
#include "WarFactory.h"

#include "GDI/Barracks.h"
#include "GDI/CommandPost.h"
#include "GDI/Airfield.h"
#include "GDI/Armory.h"
#include "GDI/TechCenter.h"
#include "GDI/CommandLink.h"

#include "NOD/HandOfNod.h"
#include "NOD/OperationsCenter.h"
#include "NOD/Airtower.h"
#include "NOD/SecretShrine.h"
#include "NOD/TechLab.h"
#include "NOD/ChemicalPlant.h"

#include "SCRIN\DronePlatform.h"
#include "SCRIN\Reactor.h"
#include "SCRIN\Extractor.h"
#include "SCRIN\Portal.h"
#include "SCRIN\WarpSphere.h"
#include "SCRIN\NerveCenter.h"
#include "SCRIN\GravityStabilizer.h"
#include "SCRIN\StasisChamber.h"
#include "SCRIN\TechnologyAssembler.h"
#include "SCRIN\SignalTransmitter.h"

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
Building::Building()
{
	name = "";
	power = hitPoint = cost = hitPointFull = 0;
	online = true;
	supportStructure = false;
	airField = false;
	refinery = false;
	powerProvider = false;
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
bool Building::getAirField()
{
	return airField;
}
bool Building::getRefinery()
{
	return refinery;
}
bool Building::getPowerProvider()
{
	return powerProvider;
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

// GDI Child Constructors
ConstructionYard::ConstructionYard()
{
	name = GDI[0];
	power = 10;
	hitPoint = hitPointFull = 20000;
	cost = 3500;
	powerProvider = true;
}
PowerPlant::PowerPlant()
{
	name = GDI[1];
	power = 20;
	hitPoint = 1500;
	hitPointFull = 4000;
	cost = 700;
	powerProvider = true;

	requirements.push_back(GDI[0]);
}
Refinery::Refinery()
{
	name = GDI[2];
	power = -15;
	hitPoint = hitPointFull = 10000;
	cost = 3000;
	refinery = true;

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



// NOD Child Constructors
HandOfNod::HandOfNod()
{
	name = NOD[3];
	power = -5;
	hitPoint = hitPointFull = 3000;
	cost = 500;

	requirements.push_back(NOD[0]);
	requirements.push_back(NOD[1]);
}
OperationsCenter::OperationsCenter()
{
	name = NOD[5];
	power = -9;
	hitPoint = hitPointFull = 5000;
	cost = 1500;
	supportStructure = true;
	upgradeStructure = true;

	requirements.push_back(NOD[0]);
	requirements.push_back(NOD[1]);
	requirements.push_back(NOD[2]);

	Upgrade upgradeOne("Dozer Blades", "Dozer Blades can be added to Scorpion Tanks to bolster their armor and make them immune to mines.", 2000);

	upgradeOne.addUnit(NOD_VEHICLE[2]);

	upgradesProvided.push_back(upgradeOne);
}
AirTower::AirTower()
{
	name = NOD[6];
	power = -8;
	hitPoint = hitPointFull = 4000;
	cost = 1000;
	airField = true;
	totalAirUnits = 0;

	requirements.push_back(NOD[0]);
	requirements.push_back(NOD[5]);
}
SecretShrine::SecretShrine()
{
	name = NOD[7];
	power = -7;
	hitPoint = hitPointFull = 3000;
	cost = 1000;
	supportStructure = true;
	upgradeStructure = true;

	requirements.push_back(NOD[0]);
	requirements.push_back(NOD[1]);
	requirements.push_back(NOD[3]);

	Upgrade upgradeOne("Tiberium Infusion", "Tiberium Infusion provides Militant Squads, Militant Rocket Squads, and Fanatics with additional 10% health and 25% speed, as well as armor increases for some militants and immunity to Tiberium.", 1000);
	Upgrade upgradeTwo("Confessors", "	Providing guidance to the masses, Nod Confessors can be assigned to militant squads to provide leadership and additional firepower. They can also hurl hallucinogenic grenades that cause targeted squads to fire on each other.", 1000);

	upgradeOne.addUnit(NOD_INFANTRY[0]);
	upgradeOne.addUnit(NOD_INFANTRY[1]);
	upgradeOne.addUnit(NOD_INFANTRY[3]);
	upgradeTwo.addUnit(NOD_INFANTRY[0]);
	upgradeTwo.addUnit(NOD_INFANTRY[1]);

	upgradesProvided.push_back(upgradeOne);
	upgradesProvided.push_back(upgradeTwo);
}
TechLab::TechLab()
{
	name = NOD[8];
	power = -12;
	hitPoint = hitPointFull = 10000;
	cost = 4000;
	supportStructure = true;
	upgradeStructure = true;

	requirements.push_back(NOD[0]);
	requirements.push_back(NOD[5]);

	Upgrade upgradeOne("Laser Capacitors", "Scorpion Tanks and Venoms receive a substantial firepower bonus when loaded with Spitfire lasers.", 2500);
	Upgrade upgradeTwo("EMP Coil", "EMP Coils can be fitted onto Raider Buggies to allow them to emit a crippling electro-magnetic pulse that disables all vehicles in the vicinity.", 1000);

	upgradeOne.addUnit(NOD_VEHICLE[1]);
	upgradeOne.addUnit(NOD_VEHICLE[2]);
	upgradeOne.addUnit(NOD_AIR[0]);
	upgradeTwo.addUnit(NOD_VEHICLE[1]);

	upgradesProvided.push_back(upgradeOne);
	upgradesProvided.push_back(upgradeTwo);
}
ChemicalPlant::ChemicalPlant()
{
	name = NOD[9];
	power = -15;
	hitPoint = hitPointFull = 3000;
	cost = 3000;
	supportStructure = true;

	requirements.push_back(NOD[0]);
	requirements.push_back(NOD[8]);
}



// SCRIN Child Constructors
DronePlatform::DronePlatform()
{
	name = SCRIN[0];
	power = 10;
	hitPoint = hitPointFull = 20000;
	cost = 3500;
	powerProvider = true;
}
Reactor::Reactor()
{
	name = SCRIN[1];
	power = 20;
	hitPoint = 1500;
	hitPointFull = 4000;
	cost = 700;
	powerProvider = true;

	requirements.push_back(SCRIN[0]);
}
Extractor::Extractor()
{
	name = SCRIN[2];
	power = -15;
	hitPoint = hitPointFull = 10000;
	cost = 3000;
	refinery = true;

	requirements.push_back(SCRIN[0]);
}
Portal::Portal()
{
	name = SCRIN[3];
	power = -5;
	hitPoint = hitPointFull = 3000;
	cost = 500;

	requirements.push_back(SCRIN[0]);
	requirements.push_back(SCRIN[1]);
}
WarpSphere::WarpSphere()
{
	name = SCRIN[4];
	power = -7;
	hitPoint = hitPointFull = 10000;
	cost = 2000;

	requirements.push_back(SCRIN[0]);
	requirements.push_back(SCRIN[1]);
	requirements.push_back(SCRIN[2]);
}
NerveCenter::NerveCenter()
{
	name = SCRIN[5];
	power = -9;
	hitPoint = hitPointFull = 5000;
	cost = 1500;
	supportStructure = true;
	upgradeStructure = true;

	requirements.push_back(SCRIN[0]);
	requirements.push_back(SCRIN[1]);
	requirements.push_back(SCRIN[2]);

	Upgrade upgradeOne("Attenuated Forcefields", "This upgrade bestows a small defensive shield onto Seekers and Gun Walkers.", 2000);

	upgradeOne.addUnit(SCRIN_VEHICLE[0]);
	upgradeOne.addUnit(SCRIN_VEHICLE[1]);

	upgradesProvided.push_back(upgradeOne);
}
GravityStabilizer::GravityStabilizer()
{
	name = SCRIN[6];
	power = -8;
	hitPoint = hitPointFull = 4000;
	cost = 1000;
	airField = true;
	totalAirUnits = 0;

	requirements.push_back(SCRIN[0]);
	requirements.push_back(SCRIN[5]);
}
StasisChamber::StasisChamber()
{
	name = SCRIN[7];
	power = -7;
	hitPoint = hitPointFull = 3000;
	cost = 1000;
	supportStructure = true;
	upgradeStructure = true;

	requirements.push_back(SCRIN[0]);
	requirements.push_back(SCRIN[1]);
	requirements.push_back(SCRIN[3]);

	Upgrade upgradeOne("Plasma Disc Launchers", "Shock Troops gain additional firepower and the ability to target aircraft when fitted with Plasma Disc Launchers.", 1500);
	Upgrade upgradeTwo("Blink Packs", "Blink Packs provide a short-ranged teleportation ability to Shock Troops, granting them additional battlefield mobility.", 500);

	upgradeOne.addUnit(SCRIN_INFANTRY[3]);
	upgradeTwo.addUnit(SCRIN_INFANTRY[3]);

	upgradesProvided.push_back(upgradeOne);
	upgradesProvided.push_back(upgradeTwo);
}
TechnologyAssembler::TechnologyAssembler()
{
	name = SCRIN[8];
	power = -12;
	hitPoint = hitPointFull = 10000;
	cost = 4000;
	supportStructure = true;
	upgradeStructure = true;

	requirements.push_back(SCRIN[0]);
	requirements.push_back(SCRIN[5]);

	Upgrade upgradeOne("Forcefield Generators", "The Scrin can upgrade their Annihilator Tripods, Planetary Assault Carriers, and Devastator Warships with Forcefields, providing additional protection.", 4000);

	upgradeOne.addUnit(SCRIN_VEHICLE[5]);
	upgradeOne.addUnit(SCRIN_AIR[2]);
	upgradeOne.addUnit(SCRIN_AIR[3]);

	upgradesProvided.push_back(upgradeOne);
}
SignalTransmitter::SignalTransmitter()
{
	name = SCRIN[9];
	power = -15;
	hitPoint = hitPointFull = 3000;
	cost = 3000;
	supportStructure = true;

	requirements.push_back(SCRIN[0]);
	requirements.push_back(SCRIN[8]);
}


// Air field child methods                  Needs Change
void AirField::addAirUnit(string name)
{
	totalAirUnits++;
	airUnits.push_back(name);
}
void AirField::removeAirUnit(int index)
{
	totalAirUnits--;
	airUnits.erase(airUnits.begin() + index);
	if (totalAirUnits < 0)
	{
		totalAirUnits = 0;
	}
}
string AirField::getAirUnitName(int index)
{
	return airUnits[index];
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
	for (int x = 0; x < totalAirUnits; x++)
	{
		cout << "\t  " << airUnits[x] << endl;
	}
	cout << (online ? "\tBuilding is online" : "\tBuilding is offline") << endl;
}


void AirTower::addAirUnit(string name)
{
	totalAirUnits++;
	airUnits.push_back(name);
}
void AirTower::removeAirUnit(int index)
{
	totalAirUnits--;
	airUnits.erase(airUnits.begin() + index);
	if (totalAirUnits < 0)
	{
		totalAirUnits = 0;
	}
}
string AirTower::getAirUnitName(int index)
{
	return airUnits[index];
}
int AirTower::getTotalAirUnit()
{
	return totalAirUnits;
}
void AirTower::printInfo()
{
	cout << "\tName: " << name << endl;
	cout << "\tPower: " << power << endl;
	cout << "\tCost: " << cost << endl;
	cout << "\tHit points: " << hitPoint << "/" << hitPointFull << endl;
	cout << "\tSpace: " << totalAirUnits << "/" << 4 << endl;
	for (int x = 0; x < totalAirUnits; x++)
	{
		cout << "\t  " << airUnits[x] << endl;
	}
	cout << (online ? "\tBuilding is online" : "\tBuilding is offline") << endl;
}


void GravityStabilizer::addAirUnit(string name)
{
	totalAirUnits++;
	airUnits.push_back(name);
}
void GravityStabilizer::removeAirUnit(int index)
{
	totalAirUnits--;
	airUnits.erase(airUnits.begin() + index);
	if (totalAirUnits < 0)
	{
		totalAirUnits = 0;
	}
}
string GravityStabilizer::getAirUnitName(int index)
{
	return airUnits[index];
}
int GravityStabilizer::getTotalAirUnit()
{
	return totalAirUnits;
}
void GravityStabilizer::printInfo()
{
	cout << "\tName: " << name << endl;
	cout << "\tPower: " << power << endl;
	cout << "\tCost: " << cost << endl;
	cout << "\tHit points: " << hitPoint << "/" << hitPointFull << endl;
	cout << "\tSpace: " << totalAirUnits << "/" << 4 << endl;
	for (int x = 0; x < totalAirUnits; x++)
	{
		cout << "\t  " << airUnits[x] << endl;
	}
	cout << (online ? "\tBuilding is online" : "\tBuilding is offline") << endl;
}