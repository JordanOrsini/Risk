#pragma once
// MODEL
#include <string>
#include <vector>
#include "Map.h"
#include "Subject.h"
#include "Deck.h"
#include "ConsoleHandler.h"

using namespace std;

class Strategy
{
public:
	virtual void attack(Player * player) = 0;
	ConsoleHandler* handle = ConsoleHandler::getInstance();
	string name;
};

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
	bool alive = true;
	void takeOver(Country* country);

	void attack() { strategy->attack(this); };				// attack uses strategy pattern
	void setStrategy(Strategy* str) { strategy = str; }
	string getStrategy() { return strategy->name; }; 


	// Victory card
	vector<Card *> hand; 
	void getCard(); 
	void disCard(int index); 

	void receiveCards(vector<Card*> playerDefeatCards);
	
private:
	string playerName;
	Subject* logSubject;
	int color;
	Strategy* strategy; 
	Deck deck; 
};


class UserStrategy : public Strategy
{
public:
	UserStrategy() { name = "User Defined"; };
	void attack(Player* player);
};

class AggressiveStrategy : public Strategy
{
public:
	AggressiveStrategy() { name = "Aggressive"; };
	void attack(Player* player);
};

class DefensiveStrategy : public Strategy
{
public:
	DefensiveStrategy() { name = "Defensive"; };
	void attack(Player* player);
};

class RandomStrategy : public Strategy
{
public:
	RandomStrategy() { name = "Random"; };
	void attack(Player* player);
};
