#pragma once
//CONTROLLER
#include "MapController.h"
#include "PlayerController.h"
#include "ConsoleHandler.h"
#include "LogDecorator.h"
#include "GameStatsDecorator.h"
#include "Deck.h"
#include "Subject.h"
#include <cstdlib>
#include <ctime>

class GameController:public Subject {
public:
	GameController();
	~GameController();
	void startUpPhase();
	void runGame();
	void reinforcementPhase(Player* player);
	void battlePhase(Player* player);
	void fortificationPhase(Player* player);
	//int rollDice();
	MapController* getMC() { return MC; }
	PlayerController* getPC() { return PC; }

	// Let the deck be available to everyone
	Deck deck; 

private:
	int getNumOfPlayers();
	void assignCountries();
	void addTroopsToCountry(Player* player, int numOfTroops, string str);
	int getStartingArmies(vector<Country*> ownedCountries);
	int getReinforcmentTroops(Player* player);
	int getVictoryCardReinforcements(Player* player); 
	Country* findCountry(string country, vector<Country*> countries);
	ConsoleHandler* handle = ConsoleHandler::getInstance();
	void setLogger(Player* player);
	void setGameStats(Player* player);
	ILog* logger;
	MapController* MC;
	PlayerController* PC;
	Deck* myDeck;
	Subject* logSubject;
};