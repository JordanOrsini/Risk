#pragma once
//CONTROLLER
#include "MapController.h"
#include "PlayerController.h"
#include "ConsoleHandler.h"
#include "LogStartup.h"
#include "Logger.h"
#include <cstdlib>
#include <ctime>

class GameController {
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

private:
	int getNumOfPlayers();
	void assignCountries();
	void addTroopsToCountry(Player* player, int numOfTroops, string str);
	int getStartingArmies();
	int getReinforcmentTroops();
	Country* findCountry(string country, vector<Country*> countries);
	ConsoleHandler* handle = ConsoleHandler::getInstance();
	MapController* MC;
	PlayerController* PC;
};