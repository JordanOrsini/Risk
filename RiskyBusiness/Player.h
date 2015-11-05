#pragma once
// MODEL
#include <string>
#include <vector>
#include "Map.h"
using namespace std;

class Player {
public:
	Player();
	Player(string playerName);
	~Player();
	string getPlayerName() { return playerName; };
	void setOwns(Country *country);
	bool iOwn(Country *country);
	int getArmyCountByCountry(Country* cName);
	int getContinentBonus();
	vector<Country*> countriesOwned;
private:
	string playerName;
};