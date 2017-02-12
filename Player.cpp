#include "Player.h"
#include "ConstructionYard.h"
#include "Harvester.h"

// List of GDI buildings
const string GDI[] = { "Construction Yard" , "Power Plant", "Refinery", "Barracks", "War Factory", "Command Post", "Airfield" , "Armory", "Tech Center", "Space Command Uplink" };
// GDI Infantry Units
const string GDI_INFANTRY[] = { "Rifleman Squad", "Missile Squad", "Engineer", "Grenadier Squad", "Sniper Team", "Zone Trooper" };
// GDI Vehicle Units
const string GDI_VEHICLE[] = { "CC-6 Pitbull", "Guardian APC","MBT-6 Predator", "Harvester", "Mobile Construction Vehicle", "Rig", "Juggernaut MK. III", "Mammoth MK. III" };
// GDI Air Units
const string GDI_AIR[] = { "A-15 Orca", "Firehawk" };

Player::Player()
{
	// Players will always start with Construction Yard
	Building* start = new ConstructionYard();
	buildings.push_back(start);

	currentPower = 10;
	alive = true;
	lowPower = false;
	resources = 0;
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
bool Player::getAlive()
{
	return alive;
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
	for (int x = 0; x < units.size(); x++)
	{
		units[x]->printInfo();
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
		cout << "\t" << x << ". " << buildings[x]->getName() << " - " << buildings[x]->getHitPoint() << "|" << buildings[x]->getHitPointFull() << " - " << (buildings[x]->getOnline() ?"online ":"offline " ) << endl;
	}
}
// Print Unit Method
void Player::printUnitList()
{
	int total = units.size();
	cout << "\tSelect your unit" << endl;

	for (int x = 0; x < total; x++)
	{
		cout << "\t" << x << ". " << units[x]->getName() << " - total= " << units[x]->getTotal() << endl;
	}
}



// Sell Building Method
void Player::sellBuilding(int index)
{
	cout << "\tSelling a " << buildings[index]->getName() << endl;

	// Condition to determine whether the current building we are selling is a power plant or any other structure
	// This will impact the power status
	if (buildings[index]->getName() == GDI[0] || buildings[index]->getName() == GDI[1])
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
		// Update the power only if that building was online
		if (buildings[index]->getOnline())
		{
			int newPower = getRequiredPower() - buildings[index]->getPower()*-1;
			setRequiredPower(newPower);
		}
		
		// Update the resources
		int newMoney = getResources() + (buildings[index]->getCost() / 2);
		setResources(newMoney);
		cout << "\tYou got " << buildings[index]->getCost() / 2 << " resources in return" << endl;

		// Remove from list of buildings
		buildings.erase(buildings.begin() + index);
	}
}

// Build Building Method
void Player::buildBuilding(Building* A)
{
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
			cout << "\tYou are unable to build this structure ("<< A->getName() <<")" << endl;
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
		if (A->getName() == GDI[1])
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
			if (A->getName() == GDI[2])
			{
				Unit* newUnit = new Harvester;

				// Since the buildUnit method will charge for the unit
				// We add the unit cost here to our resources
				resources += newUnit->getCost();
				buildUnit(newUnit, 1);
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


// Needs Repair Method
// Checks if the selected structure can be repaired. 
// If the current health is lower than the full amount of health allowed than repairing is acceptable
bool Player::needsRepair(int index)
{
	if (buildings[index]->getHitPoint() == buildings[index]->getHitPointFull())
	{
		cout << "\tUnable to repair this structure because it already has full health" << endl;
		return false;
	}
	return true;
}
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
	cout << "\tUsing an engineer" << endl;

	// Check if we have engineer available
	for (int x = 0; x < units.size(); x++)
	{
		if (units[x]->getName() == "Engineer")
		{
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
void Player::managePower(int index)
{
	if (buildings[index]->getName() == GDI[0] || buildings[index]->getName() == GDI[1])
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
		else if (!buildings[index]->getOnline() && getCurrentPower() > getRequiredPower())
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


// Check Player Life
// If the player still has buildings left they can continue to play
void Player::checkAlive()
{
	if (buildings.size() <= 0)
	{
		alive = false;
		cout << "\tYou have been defeated" << endl;
	}
}

// Build Units Method
// Similar to buildings it will allow the player to train units depending on the structures they have
// As a placeholder for now, units will not have their own instance
void Player::buildUnit(Unit* unit, int size)
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

	// Placeholder
	// Linear search to check if we already have this unit in our list
	bool found = false;
	int index = 0;
	for (index; index < units.size(); index++)
	{
		if (units[index]->getName() == unit->getName())
		{
			found = true;
			break;
		}
	}
	
	// Analyze if we have enough resources to build the unit
	for (int x = 0; x < size; x++)
	{
		if (unit->getCost() <= resources)
		{
			cout << "\tTrainning: " << unit->getName() << " ready for combat" << endl;
			resources -= unit->getCost();

			if (!found)
			{
				units.push_back(unit);
				found = true;
			}

			int currentTotal = units[index]->getTotal() + 1;
			units[index]->setTotal(currentTotal);
			
		}
		else
		{
			cout << "\tInsufficient funds to train " << size << " " << unit->getName() << endl;
			cout << "\tYou can only afford to train " << x << " " << unit->getName() << endl;
			return;
		}
	}
}
// Destroy Unit Method
// Will remove the specified amount of units from our current total that we have
void Player::destroyUnit(int index, int amount)
{
	// Remove that unit if we are destroying all the ones we have
	if (units[index]->getTotal() - amount <= 0)
	{
		cout << "\tYou lost all your " << units[index]->getName() << "/s" << endl;
		units.erase(units.begin() + index);
	}
	else // Just destroy the amount specified
	{
		int total = units[index]->getTotal() - amount;
		cout << "\tYou lost " << amount << " " << units[index]->getName() << "/s" << endl;
		units[index]->setTotal(total);
	}
}

// Placeholder
// Harvest Method used to generate money to the player
// Income will be based on our harvester count
void Player::harvest()
{
	int harvesterTotal = 0;
	bool deposit = false;

	// Find our harvester count
	for (int x = 0; x < units.size(); x++)
	{
		if (units[x]->getName() == GDI_VEHICLE[3])
		{
			harvesterTotal = units[x]->getTotal();
			deposit = true;
			break;
		}
	}

	int result = harvesterTotal * 700;

	// Placeholder
	// Also check if they have a refinery to deposit the resources
	bool deposit2 = false;
	for (int x = 0; x < buildings.size(); x++)
	{
		if (buildings[x]->getName() == GDI[2] && buildings[x]->getOnline())
		{
			deposit2 = true;
			break;
		}
	}

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