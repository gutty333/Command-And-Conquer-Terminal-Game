#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Player.h"
using namespace std;

const string factions[] = { "GDI","NOD","Scrin" };

void getFileInfo(vector <string>& target, istream& file)
{
	string line;

	while (getline(file,line))
	{
		target.push_back(line);
	}
}


int main()
{
	int choice,select = 0;
	string line;
	line.assign(50, '-');
	vector <string> buildings;
	vector <string> infantry;
	vector <string> vehicle;
	vector <string> air;

	cout << "Welcome back commander" << endl;
	Player player;

	// File selection depending on the faction they choose
	if (player.getFaction() == factions[0])
	{
		ifstream gdiBuildings("GDI_BUILDINGS.txt");
		ifstream gdiInfantry("GDI_INFANTRY.txt");
		ifstream gdiVehicle("GDI_VEHICLE.txt");
		ifstream gdiAir("GDI_AIR.txt");

		// Passing the file data
		getFileInfo(buildings, gdiBuildings);
		getFileInfo(infantry, gdiInfantry);
		getFileInfo(vehicle, gdiVehicle);
		getFileInfo(air, gdiAir);
	}
	else if (player.getFaction() == factions[1])
	{
		ifstream nodBuildings("NOD_BUILDINGS.txt");
		ifstream nodInfantry("NOD_INFANTRY.txt");
		ifstream nodVehicle("NOD_VEHICLE.txt");
		ifstream nodAir("NOD_AIR.txt");

		getFileInfo(buildings, nodBuildings);
		getFileInfo(infantry, nodInfantry);
		getFileInfo(vehicle, nodVehicle);
		getFileInfo(air, nodAir);
	}
	else
	{
		ifstream scrinBuildings("SCRIN_BUILDINGS.txt");
		ifstream scrinInfantry("SCRIN_INFANTRY.txt");
		ifstream scrinVehicle("SCRIN_VEHICLE.txt");
		ifstream scrinAir("SCRIN_AIR.txt");

		getFileInfo(buildings, scrinBuildings);
		getFileInfo(infantry, scrinInfantry);
		getFileInfo(vehicle, scrinVehicle);
		getFileInfo(air, scrinAir);
	}

	cout << endl << "This is Command and Conquer, you will be playing as the " << player.getFaction() << " faction" << endl;
	cout << "Entering Sandbox Mode" << endl;
	cout << line << endl;

	do
	{
		// Player command menu
		cout << endl << endl << "Action Menu (Please select an action by entering corresponding number)" << endl;
		cout << line << endl;
		cout << "1. Check Stats" << endl;
		cout << "2. Buy Building" << endl;
		cout << "3. Sell Building" << endl;
		cout << "4. Power Manage" << endl;
		cout << "5. Repair Building" << endl;
		cout << "6. Buy Units" << endl;
		cout << "7. Destroy Units" << endl;
		cout << "8. Buy Upgrades" << endl;
		cout << "9. Exit" << endl;
		cin >> choice;

		// User input validation
		while (choice < 1 || choice > 9)
		{
			cout << "Please enter a valid choice number (1-9)" << endl;
			cin >> choice;
		}

		switch (choice)
		{
			case 1: // View Stats
			{
				cout << endl << line << endl << "\tHere are your stats commander" << endl;

				cout << endl << line << endl<<"\tResources" << endl;
				cout << "\tMoney: " << player.getResources() << endl;

				cout << endl << line << endl << "\tPower Status" << endl;
				cout << "\tCurrent Power: " << player.getCurrentPower() << endl;
				cout << "\tRequired Power: " << player.getRequiredPower() << endl;

				cout << endl << line << endl << "\tYou have a total of " << player.getTotalBuildings() << " Buildings" << endl;
				player.printBuildings();

				cout << endl << line << endl << "\tUnits" << endl;
				player.printUnits();

				cout << endl << line << endl << "\tUpgrades" << endl;
				player.printUpgrades();
				break;
			}
			case 2: // Build Building
			{
				player.buildBuilding(select, buildings);
				player.checkPower();
				break;
			}
			case 3: // Sell Building
			{
				player.sellBuilding(select);
				player.checkPower();
				break;
			}
			case 4: // Power Manage
			{
				player.managePower(select);
				player.checkPower();
				break;
			}
			case 5: // Repair Buildings
			{
				RepairSelection:
					cout << endl << line << endl << "\tWhich structure do you want to repair?" << endl;
					player.printBuildingList();
					cout << "\t-1. Go Back" << endl;
					cin >> select;

				if (select != -1 && player.needsRepair(select))
				{
					// Menu to decide how we will repair our structure
					cout << "\tWhat do you want to use to repair the structure?" << endl;
					cout << "\t1. Repair Tool" << endl;
					cout << "\t2. Engineer" << endl;
					cout << "\t-1. Go Back" << endl;
					int repairChoice;
					cin >> repairChoice;

					switch (repairChoice)
					{
						case 1: 
						{
							player.repairBuilding(select);
							break;
						}
						case 2:
						{
							player.repairBuilding2(select);
							break;
						}
						case -1:
						{
							goto RepairSelection;
						}
					}
				}
				
				break;
			}
			case 6: // Buy Units
			{
				player.buildUnit(select, infantry, vehicle, air);
				break;
			}
			case 7: // Destroy Units
			{
				if (player.getTotalUnits() > 0)
				{
					cout << "\tWhich unit do you want to destroy?" << endl;
					player.printUnitList();
					cout << "\t-1. Go Back" << endl;
					cin >> select;

					if (select != -1)
					{
						cout << "\tHow many do you want to destroy?" << endl;
						int destroyTotal;
						cin >> destroyTotal;

						player.destroyUnit(select, destroyTotal);
					}
				}
				else
				{
					cout << "\tYou do not have any units" << endl;
				}
				
				break;
			}
			case 8: // Buy Upgrades
			{
				player.buyUpgrades(select);
			}
		}

		if (choice > 1 && choice < 9 && select != -1)
		{
			player.harvest();
		}

		player.checkAlive();
	}while (choice != 9 && player.getAlive());

	cout << endl << line << endl << "\tThank you for playing" << endl;

	return 0;
}