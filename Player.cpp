#include "Player.h"
#include "ConstructionYard.h"
#include "PowerPlant.h"
#include "Refinery.h"
#include "WarFactory.h"
#include "Harvester.h"
#include "Mcv.h"

#include "GDI/Barracks.h"
#include "GDI/CommandPost.h"
#include "GDI/Airfield.h"
#include "GDI/Armory.h"
#include "GDI/TechCenter.h"
#include "GDI/CommandLink.h"
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

#include "NOD/HandOfNod.h"
#include "NOD/OperationsCenter.h"
#include "NOD/Airtower.h"
#include "NOD/SecretShrine.h"
#include "NOD/TechLab.h"
#include "NOD/ChemicalPlant.h"
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

const string unitTypes[] = { "Infantry","Vehicle","Air" };
const string factions[] = { "GDI","NOD","Scrin" };
string line;



// Linear Search
bool searchUnit(vector <string> list, string value)     // Change Here
{
	for (int x = 0; x < list.size(); x++)
	{
		if (value == list[x])
		{
			return true;
		}
	}
	return false;
}



Player::Player()
{
	// Players will select their faction
	cout << "Which faction do you want to play as commander?" << endl;
	cout << "1. GDI" << endl;
	cout << "2. NOD" << endl;
	cout << "3. Scrin" << endl;
	int choice;
	cin >> choice;
	while (choice < 1 || choice > 3)
	{
		cout << "Please enter a correct value (1-3)" << endl;
		cin >> choice;
	}
	switch (choice)
	{
	case 1:
		faction = factions[0];
		break;
	case 2:
		faction = factions[1];
		break;
	case 3:
		faction = factions[2];
		break;
	}

	// Players will always start with a Construction Yard/Drone platform
	Building* start;
	if (choice == 1 || choice == 2)
	{
		start = new ConstructionYard();
		buildings.push_back(start);
	}
	else
	{
		start = new DronePlatform();
		buildings.push_back(start);
	}
	
	// They will select how much resources they start with
	cout << endl << "Select your starting resource" << endl;
	cout << "1. 10,000" << endl;
	cout << "2. 20,000" << endl;
	cout << "3. 30,000" << endl;
	cout << "4. 40,000" << endl;
	cin >> choice;
	while (choice < 1 || choice > 4)
	{
		cout << "Please enter a correct value (1-4)" << endl;
		cin >> choice;
	}

	switch (choice)
	{
	case 1:
		resources = 10000;
		break;
	case 2:
		resources = 20000;
		break;
	case 3:
		resources = 30000;
		break;
	case 4:
		resources = 40000;
		break;
	}

	currentPower = 10;
	alive = true;
	lowPower = false;
}

// Setter Methods
void Player::setResources(int money)
{
	resources = money;
}
void Player::setCurrentPower(int power)
{
	currentPower = power;
}
void Player::setRequiredPower(int power)
{
	if (power < 0)
	{
		requiredPower = 0;
	}
	else
	{
		requiredPower = power;
	}
	
}

// Getter Methods
int Player::getResources()
{
	return resources;
}
int Player::getCurrentPower()
{
	return currentPower;
}
int Player::getRequiredPower()
{
	return requiredPower;
}
string Player::getFaction()
{
	return faction;
}
bool Player::getAlive()
{
	return alive;
}
int Player::getTotalBuildings()
{
	return buildings.size();
}
int Player::getTotalUnits()
{
	return units.size();
}
int Player::getTotalSpecificUnit(string name)
{
	int total = 0;

	for (int x = 0; x < units.size(); x++)
	{
		if (name == units[x]->getName())
		{
			total++;
		}
	}

	return total;
}

// Print Building Method
void Player::printBuildings()
{
	for (int x = 0; x < buildings.size(); x++)
	{
		buildings[x]->printInfo();
		cout << endl;
	}
}
// Print Units Method
void Player::printUnits()
{
	vector<string> tempList;
	
	for (int x = 0; x < units.size(); x++)
	{
		if (x == 0)
		{
			tempList.push_back(units[x]->getName());
			cout << "\tYou have a total of " << getTotalSpecificUnit(units[x]->getName()) << " " << units[x]->getName() << "/s" << endl;
			units[x]->printInfo();
			cout << endl;
		}
		else if(!searchUnit(tempList, units[x]->getName()))
		{
			tempList.push_back(units[x]->getName());
			cout << "\tYou have a total of " << getTotalSpecificUnit(units[x]->getName()) << " " << units[x]->getName() << "/s" << endl;
			units[x]->printInfo();
			cout << endl;
		}
	}
}
// Print Upgrades Method
void Player::printUpgrades()
{
	for (int x = 0; x < currentUpgrades.size(); x++)
	{
		currentUpgrades[x].printInfo();
		cout << endl;
	}
}
// Print Building Method
// This will work as an option menu for the player
void Player::printBuildingList()
{
	int total = buildings.size();
	cout << "\tSelect your structure" << endl;

	for (int x = 0; x < total; x++)
	{
		cout << "\t" << x << ". " << buildings[x]->getName() << " - " << buildings[x]->getHitPoint() << "|" << buildings[x]->getHitPointFull() << " - " << (buildings[x]->getOnline() ? "online " : "offline ");

		if (buildings[x]->getAirField())
		{
			cout << "- " << buildings[x]->getTotalAirUnit() << "/4" << endl;
		}
		else
		{
			cout << endl;
		}
	}
}
// Print Unit Method
void Player::printUnitList()
{
	int total = units.size();
	cout << "\tSelect your unit" << endl;
	for (int x = 0; x < total; x++)
	{
		cout << "\t" << x << ". " << units[x]->getName() << " - total=" << getTotalSpecificUnit(units[x]->getName()) << endl;
	}
}

// Buy Upgrade Method
// We check if we have any structure which allow the player to buy upgrades
// Once the player selects the specified structure they can choose which upgrade they wish to purchase
void Player::buyUpgrades(int& select)
{
	UpgradeSelection:
		// Loop showcasing which structures allow us to buy upgrades
		// Will keep track of structures that support upgrades
		int menuIndex = 0;
		vector <int> buildingIndex;
		for (int x= 0; x < buildings.size(); x++)
		{
			if (buildings[x]->getUpgradeStructure() && buildings[x]->getOnline())
			{
				if (menuIndex == 0)
				{
					cout << "\tWhich structure do you want to buy upgrades from?" << endl;
				}
			
				cout << "\t" << menuIndex << ". " << buildings[x]->getName() << endl;
				buildingIndex.push_back(x);
				menuIndex++;
			}
		}

	if (menuIndex == 0)
	{
		cout << "\tUnable to buy upgrades, reasons can be:" << endl;
		cout << "\t1. You do have any structures that allow you buy upgrades" << endl;
		cout << "\t2. Your upgrade structure might be offline" << endl;
		return;
	}
	
	cout << "\t-1. Go Back" << endl;
	cin >> select;

	if (select == -1)
	{
		return;
	}
	else
	{
	
		cout << "\tWhich upgrade do you want to buy from the " << buildings[buildingIndex[select]]->getName() << endl;
		buildings[buildingIndex[select]]->printUpgradeList();
		cout << "\t-1 Go Back" << endl;
		int upgradeSelect;
		cin >> upgradeSelect;

		if (upgradeSelect == -1)
		{
			goto UpgradeSelection;
		}
		else
		{
			Upgrade current = buildings[buildingIndex[select]]->getUpgrade(upgradeSelect);
			int newCost = resources - current.getCost();

			// Analyze if we have enough resources for the selected upgrade
			if (newCost >= 0)
			{
				// Checking if we have that current upgrade
				for (int y = 0; y < currentUpgrades.size(); y++)
				{
					if (current.getName() == currentUpgrades[y].getName())
					{
						cout << "\tUnable to purchase, you already have this upgrade" << endl;
						return;
					}
				}
				
				// Update our resources and add the upgrade to our list
				cout << "\tUpgrade Complete" << endl;
				cout << "\tYou have purchased " << current.getName() << endl;
				setResources(newCost);
				currentUpgrades.push_back(current);

				// Apply the upgrades to the corresponding units
				for (int i = 0; i < current.getTotalUnitsUpgrading(); i++)
				{
					for (int y = 0; y < units.size(); y++)
					{
						if (units[y]->getName() == current.getUnit(i))
						{
							units[y]->addUpgrade(current.getName());
						}
					}
				}
				
			}
			else
			{
				cout << "\tInsufficient Funds, unable to buy" << endl;
			}
		}
	}
}

// Sell Building Method
void Player::sellBuilding(int& index)
{
	line.assign(50, '-');

	cout << endl << line << endl << "\tWhich structure do you want to sell?" << endl;
	printBuildingList();
	cout << "\t-1. Go Back" << endl;
	cin >> index;

	if (index != -1)
	{
		cout << "\tSelling a/an " << buildings[index]->getName() << endl;

		// Condition to determine whether the current building we are selling is a power plant or any other structure
		// This will impact the power status
		if (buildings[index]->getPowerProvider())
		{
			// Update the power
			int newPower = getCurrentPower() - buildings[index]->getPower();
			setCurrentPower(newPower);

			// Update the resources
			int newMoney = getResources() + (buildings[index]->getCost() / 2);
			setResources(newMoney);
			cout << "\tYou got " << buildings[index]->getCost() / 2 << " resources in return" << endl;

			// Remove from list of buildings
			buildings.erase(buildings.begin() + index);
		}
		else
		{
			bool found = false;

			// Check if that building is in offline mode
			for (int x = 0; x < offlineBuildings.size(); x++)
			{
				if (buildings[index] == offlineBuildings[x])
				{
					found = true;
				}
			}

			// Update the power only if that building was online or was in offline mode
			// Offline mode is any building automatically power down due to low power
			// This does not include buildings power down manually
			if (buildings[index]->getOnline() || found)
			{
				int newPower = getRequiredPower() - buildings[index]->getPower()*-1;
				setRequiredPower(newPower);
			}

			// Update the resources
			int newMoney = getResources() + (buildings[index]->getCost() / 2);
			setResources(newMoney);
			cout << "\tYou got " << buildings[index]->getCost() / 2 << " resources in return" << endl;

			// Special case in which the building we are selling is an airfield that has special air units on deck
			if (buildings[index]->getAirField() && buildings[index]->getTotalAirUnit() > 0)
			{
				// We also remove the air units from our unit list
				// Example if this airfield we are deleting has 2 orcas and 1 firehawk
				// We also have to destroy 2 orcas and 1 firehawk from our list
				cout << "\tYou sold an airfield which contained a/an:" << endl;
				
				for (int x = 0; x < buildings[index]->getTotalAirUnit(); x++)
				{
					cout << "\t  " << x+1 << ". " << buildings[index]->getAirUnitName(x) << endl;
					for (int y = 0; y < units.size(); y++)
					{
						if (buildings[index]->getAirUnitName(x) == units[y]->getName())
						{
							units.erase(units.begin() + y);
							y--;
							break;
						}
					}
				}
			}

			// Remove from our list of buildings
			buildings.erase(buildings.begin() + index);
		}
	}
}

// Build Building Method
void Player::buildBuilding(int& select, vector <string> factionBuildings)
{
	line.assign(50, '-');
	Building* A;
	vector <Building*> BUILDINGS;
	if (faction == factions[0]) // GDI Buildings
	{
		Building* temp[] = { new PowerPlant, new Refinery, new Barracks, new WarFactory, new CommandPost, new AirField, new Armory, new TechCenter, new CommandLink };

		for (int x = 0; x < factionBuildings.size(); x++)
		{
			BUILDINGS.push_back(temp[x]);
		}
	}
	else if (faction == factions[1]) // NOD Buildings
	{
		Building* temp[] = { new PowerPlant, new Refinery, new HandOfNod, new WarFactory, new OperationsCenter, new AirTower, new SecretShrine, new TechLab, new ChemicalPlant };
		for (int x = 0; x < factionBuildings.size(); x++)
		{
			BUILDINGS.push_back(temp[x]);
		}
	}
	else if (faction == factions[2]) // Scrin Buildings
	{
		Building* temp[] = { new Reactor, new Extractor, new Portal, new WarpSphere, new NerveCenter, new GravityStabilizer, new StasisChamber, new TechnologyAssembler, new SignalTransmitter };
		for (int x = 0; x < factionBuildings.size(); x++)
		{
			BUILDINGS.push_back(temp[x]);
		}
	}

	// Menu to allow the player to choose which building they want to buy
	// Placeholder, since I will pass a vector containing the list of buildings based on the faction the player picks
	cout << endl << line << endl << "\tWhich structure do you want to build?" << endl;
	for (int x = 0; x < factionBuildings.size(); x++)
	{
		cout << "\t" << x << ". " << factionBuildings[x] << endl;
	}
	cout << "\t-1. Go Back" << endl;
	cin >> select;

	if (select != -1)
	{
		A = BUILDINGS[select];

		// First check if the particular building can be build based on its requirements
		// Will check our current list to see if the requirements are met
		vector <string> check = A->getRequirements();

		bool allow;

		for (int x = 0; x < check.size(); x++)
		{
			allow = false;

			for (int y = 0; y < buildings.size(); y++)
			{
				if (check[x] == buildings[y]->getName() && buildings[y]->getOnline())
				{
					allow = true;
				}
			}

			if (!allow)
			{
				cout << "\tYou are unable to build this structure (" << A->getName() << ")" << endl;
				cout << "\tRequires a " << check[x] << endl;
				return;
			}
		}

		// Second check if we have enough resources to buy the structure
		int newMoney = getResources() - A->getCost();
		if (newMoney > 0)
		{
			// Update the resources
			setResources(newMoney);
			cout << "\tConstruction Complete" << endl;
			// Condition to determine if this is a power plant
			if (A->getPowerProvider())
			{
				// Update the power
				int newPower = getCurrentPower() + A->getPower();
				setCurrentPower(newPower);
			}
			else
			{
				// Update the power
				int newPower = getRequiredPower() + A->getPower()*-1;
				setRequiredPower(newPower);

				// In the case we build a refinery the player gains a harvester
				if (A->getRefinery())
				{
					if (faction == factions[0] || faction == factions[1])
					{
						Unit* harvester = new Harvester;
						units.push_back(harvester);
					}
					else
					{
						Unit* harvester = new ScrinHarvester;
						units.push_back(harvester);
					}
					
				}
			}

			A->printInfo();
			// Add the building
			buildings.push_back(A);
		}
		else
		{
			cout << "\tInsufficient Funds, unable to buy" << endl;
		}
	}
}

// Needs Repair Method
// Checks if the selected structure can be repaired. 
// If the current health is lower than the full amount of health allowed, than repairing is acceptable
bool Player::needsRepair(int index)
{
	if (buildings[index]->getHitPoint() == buildings[index]->getHitPointFull())
	{
		cout << "\tUnable to repair this structure because it already has full health" << endl;
		return false;
	}
	return true;
}

// First Repair Method
// This is using the repair tool, it will use resources to restore the hitpoint of our structure
void Player::repairBuilding(int index)
{
	// Analyze the cost for repairing the structure
	// Will also update our resources and repair the specified structure
	cout << "\tUsing the repair tool" << endl;
	int difference = buildings[index]->getHitPointFull() - buildings[index]->getHitPoint();
	int cost = resources - difference;

	// Condition to determine if we have enough money to fully repair our structure
	if (cost > 0)
	{
		cout << "\tThe " << buildings[index]->getName() << " will be repaired for the cost of " << difference << " resources";
		buildings[index]->setHitPoint(buildings[index]->getHitPointFull());
		setResources(cost);
	}
	else
	{
		cout << "\tThe " << buildings[index]->getName() << " will be repaired for the cost of " << resources << " resources";
		buildings[index]->setHitPoint(buildings[index]->getHitPoint()+resources);
		setResources(0);
	}
}

// Second Repair Method
// This variation uses an engineer instead of the repair tool
// The player most have an engineer available
void Player::repairBuilding2(int index)
{
	// Check if we have engineer available
	for (int x = 0; x < units.size(); x++)
	{
		if (units[x]->getEngineer())
		{
			cout << "\tUsing an engineer" << endl;
			// We will need to destroy our current engineer
			destroyUnit(x, 1);

			// Also update our building hit point
			buildings[index]->setHitPoint(buildings[index]->getHitPointFull());
			cout << "\tThe " << buildings[index]->getName() << " has been repaired" << endl;
			return;
		}
	}

	cout << "\tUnable to repair the " << buildings[index]->getName() << ", you do not have an engineer available" << endl;
}

// Check Power Method
// If the player is low on power any support structures will be power down
// This check will repeat each time when either the player buys,sells, or power manages a structure
void Player::checkPower()
{
	// If low power, disable structures that depend on power usage
	if (getCurrentPower() < getRequiredPower())
	{
		cout << "\tLow on Power" << endl;

		// Loop to disable support structures which depend on power always being online
		// This only disables support structures that were online
		// So any support structure manually power downed will not be affected
		// Will turned them off and also add to our offline building list
		for (int x = 0; x < buildings.size(); x++)
		{
			if (buildings[x]->getSupportStructure() && buildings[x]->getOnline())
			{
				buildings[x]->setOnline(false);
				offlineBuildings.push_back(buildings[x]);
			}
		}

		// Update to lets us know we were in a low power mode
		lowPower = true;
	}
	else if (lowPower && getCurrentPower() >= getRequiredPower())
	{
		cout << "\tBack Online, You have enough Power" << endl;

		// Loop to turn on any of the offline Buildings
		for (int x = 0; x < offlineBuildings.size(); x++)
		{
			offlineBuildings[x]->setOnline(true);
		}
		offlineBuildings.clear();

		lowPower = false;
	}
}
// Power Management Method
// Will disable or enable the building selected by the user
void Player::managePower(int& index)
{
	line.assign(50, '-');
	cout << endl << line << endl << "\tWhich structure do you want to power manage?" << endl;
	printBuildingList();
	cout << "\t-1. Go Back" << endl;
	cin >> index;

	if (index != -1)
	{
		if (buildings[index]->getPowerProvider())
		{
			cout << "\tUnable to disable the " << buildings[index]->getName() << endl;
		}
		else
		{
			// Condition to turn off or ON
			if (buildings[index]->getOnline())
			{
				cout << "\tThe " << buildings[index]->getName() << " will be turned off" << endl;
				buildings[index]->setOnline(false);

				// Update our power
				int newPower = getRequiredPower() - buildings[index]->getPower()*-1;
				setRequiredPower(newPower);
			}
			else if (!buildings[index]->getOnline() && !buildings[index]->getSupportStructure())
			{
				cout << "\tThe " << buildings[index]->getName() << " will be turned on" << endl;
				buildings[index]->setOnline(true);

				// Update our power
				int newPower = getRequiredPower() + buildings[index]->getPower()*-1;
				setRequiredPower(newPower);
			}
			else if (!buildings[index]->getOnline() && buildings[index]->getSupportStructure() && getCurrentPower() > getRequiredPower())
			{
				cout << "\tThe " << buildings[index]->getName() << " will be turned on" << endl;
				buildings[index]->setOnline(true);

				// Update our power
				int newPower = getRequiredPower() + buildings[index]->getPower()*-1;
				setRequiredPower(newPower);
			}
			else
			{
				cout << "\tUnable to turn on the " << buildings[index]->getName() << endl;
				cout << "\tYou do not have enough power to support that structure" << endl;
			}
		}
	}
}

// Check Player Life
// If the player still has buildings left they can continue to play
void Player::checkAlive()
{
	if (buildings.size() <= 0)
	{
		alive = false;
		cout << endl << "\tYou have been defeated" << endl;
	}
}

// Build Units Method
// Similar to building a structure it will allow the player to train units depending on the structures they have
// As a placeholder for now, units will not have their own instance
void Player::buildUnit(int& select, vector <string> factionInfantry, vector <string> factionVehicle, vector <string> factionAir)
{
	line.assign(50, '-');
	vector <Unit*> infantry;
	vector <Unit*> vehicle;
	vector <Unit*> air;
	Unit* unit = NULL;

	if (faction == factions[0]) // GDI Units
	{
		Unit* infantryTemp[] = { new Rifleman, new MissileSquad, new Engineer, new Grenadier, new SniperTeam, new ZoneTrooper };
		Unit* vehicleTemp[] = { new Pitbull, new Apc, new Predator, new Harvester, new Mcv, new Rig, new Juggernaut, new MammothTank };
		Unit* airTemp[] = { new Orca, new Firehawk , new HammerHead };
		for (int x = 0; x < factionInfantry.size(); x++)
		{
			infantry.push_back(infantryTemp[x]);
		}
		for (int x = 0; x < factionVehicle.size(); x++)
		{
			vehicle.push_back(vehicleTemp[x]);
		}
		for (int x = 0; x < factionAir.size(); x++)
		{
			air.push_back(airTemp[x]);
		}
	}
	else if (faction == factions[1]) // NOD Units
	{
		Unit* infantryTemp[] = { new MilitantSquad, new RocketSquad, new Saboteur, new Fanatic, new ShadowTeam, new BlackHand };
		Unit* vehicleTemp[] = { new AttackBike, new RaiderBuggy, new ScorpionTank, new Harvester, new Mcv, new FlameTank, new StealthTank, new Avatar };
		Unit* airTemp[] = { new Venom, new Vertigo};
		for (int x = 0; x < factionInfantry.size(); x++)
		{
			infantry.push_back(infantryTemp[x]);
		}
		for (int x = 0; x < factionVehicle.size(); x++)
		{
			vehicle.push_back(vehicleTemp[x]);
		}
		for (int x = 0; x < factionAir.size(); x++)
		{
			air.push_back(airTemp[x]);
		}
	}
	else // Scrin Units
	{
		Unit* infantryTemp[] = { new Buzzer, new Disintegrator, new Assimilator, new ShockTrooper, new Ravager };
		Unit* vehicleTemp[] = { new GunWalker, new Seeker, new ScrinHarvester, new DevourerTank, new Corrupter, new Tripod };
		Unit* airTemp[] = { new StormRider, new DroneShip , new DevastatorWarship, new PlanetaryAssault };
		for (int x = 0; x < factionInfantry.size(); x++)
		{
			infantry.push_back(infantryTemp[x]);
		}
		for (int x = 0; x < factionVehicle.size(); x++)
		{
			vehicle.push_back(vehicleTemp[x]);
		}
		for (int x = 0; x < factionAir.size(); x++)
		{
			air.push_back(airTemp[x]);
		}
	}

	

	// Allow the user to select the type of unit they want to buy
	UnitSelection:
		cout << endl << line << endl << "\tWhich unit type do you want to buy?" << endl;
		for (int x = 0; x < 3; x++)
		{
			cout << "\t" << x + 1 << " " << unitTypes[x] << endl;
		}
		cout << "\t-1. Go Back" << endl;
		cin >> select;
	
	int unitChoice;
	switch (select)
	{
		case 1: // Infantry Units
		{
			cout << endl << line << endl << "\tWhich infantry unit do you want to buy?" << endl;
			for (int x = 0; x < factionInfantry.size(); x++)
			{
				cout << "\t" << x << ". " << factionInfantry[x] << endl;
			}
			cout << "\t-1. Go Back" << endl;
			cin >> unitChoice;

			if (unitChoice == -1)
			{
				goto UnitSelection;
			}
			else
			{
				unit = infantry[unitChoice];
			}
			break;
		}
		case 2: // Vehicle Units
		{
			cout << endl << line << endl << "\tWhich vehicle unit do you want to buy?" << endl;
			for (int x = 0; x < factionVehicle.size(); x++)
			{
				cout << "\t" << x << ". " << factionVehicle[x] << endl;
			}
			cout << "\t-1. Go Back" << endl;
			cin >> unitChoice;

			if (unitChoice == -1)
			{
				goto UnitSelection;
			}
			else
			{
				unit = vehicle[unitChoice];
			}
			break;;
		}
		case 3: // Air Units
		{
			cout << endl << line << endl << "\tWhich air unit do you want to buy?" << endl;
			for (int x = 0; x < factionAir.size(); x++)
			{
				cout << "\t" << x << ". " << factionAir[x] << endl;
			}
			cout << "\t-1. Go Back" << endl;
			cin >> unitChoice;

			if (unitChoice == -1)
			{
				goto UnitSelection;
			}
			else
			{
				unit = air[unitChoice];
			}
			break;
		}
	}

	if (select != -1)
	{
		// Checking if we have the required structures to build this unit
		vector <string> requirements = unit->getRequirements();
		for (int x = 0; x < requirements.size(); x++)
		{
			bool allow = false;

			for (int y = 0; y < buildings.size(); y++)
			{
				if (requirements[x] == buildings[y]->getName() && buildings[y]->getOnline())
				{
					allow = true;
				}
			}

			if (!allow)
			{
				cout << "\tYou are unable to train this unit (" << unit->getName() << ")" << endl;
				cout << "\tRequires a " << requirements[x] << endl;
				return;
			}
		}

		// Buying our Unit
		cout << "\tHow many do you want to train?" << endl;
		int size, index2 = 0;
		cin >> size;
		for (int x = 0; x < size; x++)
		{
			infantry.clear();
			vehicle.clear();
			air.clear();
			if (faction == factions[0])
			{
				Unit* infantryTemp[] = { new Rifleman, new MissileSquad, new Engineer, new Grenadier, new SniperTeam, new ZoneTrooper };
				Unit* vehicleTemp[] = { new Pitbull, new Apc, new Predator, new Harvester, new Mcv, new Rig, new Juggernaut, new MammothTank };
				Unit* airTemp[] = { new Orca, new Firehawk , new HammerHead };
				for (int x = 0; x < factionInfantry.size(); x++)
				{
					infantry.push_back(infantryTemp[x]);
				}
				for (int x = 0; x < factionVehicle.size(); x++)
				{
					vehicle.push_back(vehicleTemp[x]);
				}
				for (int x = 0; x < factionAir.size(); x++)
				{
					air.push_back(airTemp[x]);
				}
			}
			else if (faction == factions[1])
			{
				Unit* infantryTemp[] = { new MilitantSquad, new RocketSquad, new Saboteur, new Fanatic, new ShadowTeam, new BlackHand };
				Unit* vehicleTemp[] = { new AttackBike, new RaiderBuggy, new ScorpionTank, new Harvester, new Mcv, new FlameTank, new StealthTank, new Avatar };
				Unit* airTemp[] = { new Venom, new Vertigo };
				for (int x = 0; x < factionInfantry.size(); x++)
				{
					infantry.push_back(infantryTemp[x]);
				}
				for (int x = 0; x < factionVehicle.size(); x++)
				{
					vehicle.push_back(vehicleTemp[x]);
				}
				for (int x = 0; x < factionAir.size(); x++)
				{
					air.push_back(airTemp[x]);
				}
			}
			else
			{
				Unit* infantryTemp[] = { new Buzzer, new Disintegrator, new Assimilator, new ShockTrooper, new Ravager };
				Unit* vehicleTemp[] = { new GunWalker, new Seeker, new ScrinHarvester, new DevourerTank, new Corrupter, new Tripod };
				Unit* airTemp[] = { new StormRider, new DroneShip , new DevastatorWarship, new PlanetaryAssault };
				for (int x = 0; x < factionInfantry.size(); x++)
				{
					infantry.push_back(infantryTemp[x]);
				}
				for (int x = 0; x < factionVehicle.size(); x++)
				{
					vehicle.push_back(vehicleTemp[x]);
				}
				for (int x = 0; x < factionAir.size(); x++)
				{
					air.push_back(airTemp[x]);
				}
			}

			if (select == 1)
			{
				unit = infantry[unitChoice];
			}
			else if (select == 2)
			{
				unit = vehicle[unitChoice];
			}
			else if (select == 3)
			{
				unit = air[unitChoice];
			}

			// Analyze if we have enough resources to build the unit
			if (unit->getCost() <= resources)
			{
				bool airUnitCheck = false;
				bool regularUnit = false;

				// Condition in the case we are training air units that have a limit based on the number of airfields we have
				// For example each airfield can only allow 4 air units to be trained
				// Will check if the airfield we have has space, so we can add our special air unit
				// Placeholder
				if (unit->getAirUnit())
				{
					for (index2; index2 < buildings.size(); index2++)
					{
						if (buildings[index2]->getAirField() && buildings[index2]->getTotalAirUnit() < 4 && buildings[index2]->getOnline())
						{
							buildings[index2]->addAirUnit(unit->getName());
							airUnitCheck = true;
							break;
						}

					}
				}
				else
				{
					regularUnit = true;
				}

				if (airUnitCheck || regularUnit)
				{
					cout << "\tTraining: " << unit->getName() << " ready for combat" << endl;
					resources -= unit->getCost();

					// Apply corresponding upgrades to the new unit we are buying
					// For example if we have an upgrade that is used by the new unit we bought add that upgrade to it
					for (int i = 0; i < currentUpgrades.size(); i++)
					{
						for (int y = 0; y < currentUpgrades[i].getTotalUnitsUpgrading(); y++)
						{
							if (unit->getName() == currentUpgrades[i].getUnit(y))
							{
								unit->addUpgrade(currentUpgrades[i].getName());
							}
						}
					}

					// Adding our unit
					units.push_back(unit);
				}
				else
				{
					cout << "\tUnable to train the other " << size - x << " " << unit->getName() << "/s" << endl;
					cout << "\tYou must build another airfield. An airfield only supports 4" << endl;
					break;
				}
			}
			else
			{
				cout << "\tInsufficient funds to train " << size << " " << unit->getName() << endl;
				cout << "\tYou can only afford to train " << x << " " << unit->getName() << endl;
				return;
			}
		}
	}
}

// Destroy Unit Method
// Will remove the specified amount of units from our current total that we have
void Player::destroyUnit(int index, int amount)
{
	int tempAmount = amount;
	int total = getTotalSpecificUnit(units[index]->getName());

	// Remove that unit if we are destroying all of them
	if (total - amount <= 0)
	{
		cout << "\tYou lost all your " << units[index]->getName() << "/s" << endl;
		
		// Condition in case the unit we are deleting is a special air unit
		// We have to free up space from our airfield
		// It will remove the air unit specified from our airfield.
		if (units[index]->getAirUnit())
		{
			for (int x = buildings.size() - 1; x >= 0; x--)
			{
				if (buildings[x]->getAirField())
				{
					for (int y = 0; y < buildings[x]->getTotalAirUnit() && amount > 0; y++)
					{
						if (buildings[x]->getAirUnitName(y) == units[index]->getName())
						{
							buildings[x]->removeAirUnit(y);
							amount--;
							y--;
						}
					}
				}
			}
		}

		// Remove all the units from our list
		string name = units[index]->getName();
		for (int x = 0; x < units.size(); x++)
		{
			if (name == units[x]->getName())
			{
				units.erase(units.begin() + x);
				x--;
			}
		}
	}
	else // Just destroy the amount specified
	{
		cout << "\tYou lost " << amount << " " << units[index]->getName() << "/s" << endl;

		// Special Air Unit Condition
		if (units[index]->getAirUnit())
		{
			for (int x = buildings.size() - 1; x >= 0; x--)
			{
				if (buildings[x]->getAirField())
				{
					for (int y = 0; y < buildings[x]->getTotalAirUnit() && amount > 0; y++)
					{
						if (buildings[x]->getAirUnitName(y) == units[index]->getName())
						{
							buildings[x]->removeAirUnit(y);
							amount--;
							y--;
						}
					}
				}
			}
		}

		// Remove the amount specified from our list
		string name = units[index]->getName();
		int totalRemoved = 0;
		for (int x = 0; x < units.size() && totalRemoved < tempAmount; x++)
		{
			if (name == units[x]->getName())
			{
				units.erase(units.begin() + x);
				x--;
				totalRemoved++;
			}
		}
	}
}

// Placeholder
// Harvest Method used to generate money to the player
// Income will be based on our harvester count
void Player::harvest()
{
	bool deposit = false;

	// Find our harvester count
	int harvesterTotal = getTotalSpecificUnit("Harvester");
	if (harvesterTotal > 0)
	{
		deposit = true;
	}

	// Placeholder
	// Also check if they have a refinery to deposit the resources
	bool deposit2 = false;
	for (int x = 0; x < buildings.size(); x++)
	{
		if (buildings[x]->getRefinery() && buildings[x]->getOnline())
		{
			deposit2 = true;
			break;
		}
	}

	int result = harvesterTotal * 700;

	if (deposit && deposit2)
	{
		cout << endl << "\tYou will gain $" << result << " resources from harvesting" << endl;
		resources += result;
	}
	else
	{
		cout << endl << "\tYou are unable to harvest." << endl;
		cout << "\tSolutions Can Be: " << endl;
		cout << "\t1. Build a refinery and have one online" << endl;
		cout << "\t2. Get harvesters" << endl;
	}
}