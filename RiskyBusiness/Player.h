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
	void setOwnsCountry(Country *country) { countriesOwned.push_back(country); };
	void setOwnsContinent(Continent *continent) { continentsOwned.push_back(continent); };
	bool iOwnCountry(Country *country);
	bool iOwnContinent(Continent *continent);
	int getArmyCountByCountry(Country* country);
	int getContinentBonus();
	vector<Country*> countriesOwned;
	vector<Continent*> continentsOwned;
private:
	string playerName;
};