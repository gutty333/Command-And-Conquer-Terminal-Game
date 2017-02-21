#include <iostream>
#include <string>
using namespace std;

#ifndef UPGRADE_H
#define UPGRADE_H

class Upgrade
{
private:
	string name;
	string info;
	int cost;
	bool active;

public:
	Upgrade(string, string, int);
	void setActive(bool);
	string getName();
	string getInfo();
	int getCost();
	bool getActive();
	void printInfo();
};

#endif