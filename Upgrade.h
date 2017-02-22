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

public:
	Upgrade(string, string, int);
	void setActive(bool);
	string getName();
	string getInfo();
	int getCost();
	void printInfo();
};

#endif