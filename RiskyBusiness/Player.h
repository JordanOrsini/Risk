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
	int getColor() { return color; };
	void setColor(int color) { this->color = color; };
	void setOwnsCountry(Country *country) { countriesOwned.push_back(country); country->owner = this; }
	bool iOwnCountry(Country *country);
	bool iOwnContinent(Continent *continent);
	int getArmyCountByCountry(Country* country);
	int getContinentBonus(Map* map);
	bool checkCountryHasNeighborsUOwn(Country* country);
	vector<Country*> countriesOwned;
	
private:
	string playerName;
	int color;
};