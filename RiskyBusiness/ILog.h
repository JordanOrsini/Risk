#pragma once
#include "Observer.h"
#include <iostream>
#include <string>

using namespace std;

/*
Log decorator interface
*/
class ILog: public Observer
{
public:
	ILog() {};
	void setStartupTroopsAdded(int n) { this->startupTroopsAdded = n; };
	void setCountry(string c) { this->country = c; };
	int getStartupTroopsAdded() { return this->startupTroopsAdded; };
	string getCountry() { return this->country; };
	virtual void displayLog() = 0;
	virtual void update() = 0;
private:
	int startupTroopsAdded;
	string country;
};

