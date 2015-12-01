#pragma once
// MODEL
#include <string>
#include <vector>
#include "Map.h"
#include "Subject.h"
#include "Deck.h"

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
	Subject* getLogSubject() { return this->logSubject; };
	vector<Country*> countriesOwned;

	// Victory card
	vector<Card *> hand; 
	void getCard(Card* card); 
	void disCard(int index); 
	
private:
	string playerName;
	Subject* logSubject;
	int color;
};