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
int Player::getTotalBuildings()
{
	return buildings.size();
}
int Player::getTotalUnits()
{
	return units.size();
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
		cout << "\t" << x << ". " << units[x]->getName() << " - total=" << units[x]->getTotal() << endl;
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
				for (int i = 0; i < current.getTotaUnitsUpgrading(); i++)
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
				Unit* harvester = new Harvester;

				// Placeholder
				// Linear search to check if we already have this unit in our list
				bool found = false;
				int index = 0;
				for (index; index < units.size(); index++)
				{
					if (harvester->getName() == units[index]->getName())
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					units.push_back(harvester);
				}

				int currentTotal = units[index]->getTotal() + 1;
				units[index]->setTotal(currentTotal);
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

	// Check if we have engineer available
	for (int x = 0; x < units.size(); x++)
	{
		if (units[x]->getName() == "Engineer")
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
// Similar to buildings it will allow the player to train units depending on the structures they have
// As a placeholder for now, units will not have their own instance
void Player::buildUnit(Unit* unit)
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
	
	cout << "\tHow many do you want to train?" << endl;
	int size,index2 = 0;
	cin >> size;
	// Analyze if we have enough resources to build the unit
	for (int x = 0; x < size; x++)
	{
		if (unit->getCost() <= resources)
		{
			bool airUnitCheck = false;
			bool regularUnit = false;

			// Condition in the case we are training air units that have a limit based on the number of airfields we have
			// For example each airfield can only allow 4 air units to be trained
			// Placeholder
			if (unit->getAirUnit())
			{
				for (index2; index2 < buildings.size(); index2++)
				{
					if (buildings[index2]->getName() == GDI[6] && buildings[index2]->getTotalAirUnit() < 4 && buildings[index2]->getOnline())
					{
						buildings[index2]->addAirUnit();
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

				if (!found)
				{
					// Apply corresponding upgrades to the new unit we are buying
					// For example if we have upgrade that is used by the new unit we bought add that upgrade to it
					for (int i = 0; i < currentUpgrades.size(); i++)
					{
						for (int y = 0; y < currentUpgrades[i].getTotaUnitsUpgrading(); y++)
						{
							if (unit->getName() == currentUpgrades[i].getUnit(y))
							{
								unit->addUpgrade(currentUpgrades[i].getName());
							}
						}
					}

					units.push_back(unit);
					found = true;
				}

				int currentTotal = units[index]->getTotal() + 1;
				units[index]->setTotal(currentTotal);
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
// Destroy Unit Method
// Will remove the specified amount of units from our current total that we have
void Player::destroyUnit(int index, int amount)
{
	// Remove that unit if we are destroying all the ones we have
	if (units[index]->getTotal() - amount <= 0)
	{
		cout << "\tYou lost all your " << units[index]->getName() << "/s" << endl;
		

		// Condition in case the unit we are deleting is a special air unit
		// We have to free up space from our airfield
		// Placeholder
		// Needs Fix
		if (units[index]->getAirUnit())
		{
			for (int x = buildings.size() - 1; x >= 0; x--)
			{
				if (buildings[x]->getName() == GDI[6])
				{
					while (buildings[x]->getTotalAirUnit() > 0 && amount > 0)
					{
						buildings[x]->removeAirUnit();
						amount--;
					}					
				}
			}
		}

		units.erase(units.begin() + index);
	}
	else // Just destroy the amount specified
	{
		int total = units[index]->getTotal() - amount;
		cout << "\tYou lost " << amount << " " << units[index]->getName() << "/s" << endl;
		units[index]->setTotal(total);

		// Special Air Unit Condition
		if (units[index]->getAirUnit())
		{
			for (int x = buildings.size() - 1; x >= 0; x--)
			{
				if (buildings[x]->getName() == GDI[6])
				{
					while (buildings[x]->getTotalAirUnit() > 0 && amount > 0)
					{
						buildings[x]->removeAirUnit();
						amount--;
					}
				}
			}
		}
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