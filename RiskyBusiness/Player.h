#pragma once
// MODEL
#include <string>
#include <vector>
#include <algorithm> // used to sort the dice rolls
#include "Map.h"
#include "Subject.h"
#include "LogDecorator.h"
#include "Deck.h"
#include "ConsoleHandler.h"
#include "MapController.h"

using namespace std;

class Strategy
{
public:
	virtual void attack(Player * player) = 0;
	ConsoleHandler* handle = ConsoleHandler::getInstance();
	string name;
	vector<int> rolldice(int attackAmount, int defendAmount, Player* attackingPlayer, Player* defendingPlayer); //used only during attack phase
protected:
	MapController* MC;
};

class Player: public Subject {
public:
	Player();
	Player(string playerName);
	~Player();
	string getPlayerName() { return playerName; };
	void setLogMessage(string logMessage);
	int getColor() { return color; };
	void setColor(int color) { this->color = color; };
	void setOwnsCountry(Country *country) { countriesOwned.push_back(country); country->owner = this; }
	bool iOwnCountry(Country *country);
	bool iOwnContinent(Continent *continent);
	int getArmyCountByCountry(Country* country);
	int getContinentBonus(Map* map);
	bool checkCountryHasNeighborsUOwn(Country* country);
	void setMap(Map* map) { this->map = map; };
	Map* getMap() { return this->map; };
	int getNumOfBattlesWon() { return numOfBattlesWon; };
	vector<Country*> countriesOwned;
	bool alive = true;
	void takeOver(Country* attack, Country* defend, int atkAMT, int atkLOST);

	void attack() { strategy->attack(this); };				// attack uses strategy pattern
	void setStrategy(Strategy* str) { strategy = str; }
	string getStrategy() { return strategy->name; }; 
	ConsoleHandler* handle = ConsoleHandler::getInstance();


	// Victory card
	vector<Card *> hand; 
	void getCard(); 
	void disCard(int index); 

	void receiveCards(vector<Card*> playerDefeatCards);
	
private:
	string playerName;
	string logMessage;
	friend class Logger;
	int color;
	int numOfBattlesWon = 0;
	Strategy* strategy; 
	Deck deck;
	Map* map;
};


class UserStrategy : public Strategy
{
public:
	UserStrategy(MapController* MC) { name = "User Defined"; this->MC = MC; };
	void attack(Player* player);
};

class AggressiveStrategy : public Strategy
{
public:
	AggressiveStrategy(MapController* MC) { name = "Aggressive"; this->MC = MC; };
	void attack(Player* player);
};

class DefensiveStrategy : public Strategy
{
public:
	DefensiveStrategy(MapController* MC) { name = "Defensive"; this->MC = MC; };
	void attack(Player* player);
};

class RandomStrategy : public Strategy
{
public:
	RandomStrategy(MapController* MC) { name = "Random"; this->MC = MC; };
	void attack(Player* player);
};
