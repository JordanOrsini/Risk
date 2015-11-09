#pragma once
//CONTROLLER
#include "MapController.h"
#include "PlayerController.h"
#include <cstdlib>
#include <ctime>

class GameController {
public:
	GameController();
	~GameController();
	void startUpPhase();
	void runGame();
	void reinforcementPhase(Player* player);
	//void battlePhase();
	void fortificationPhase(Player* player);
	//int rollDice();
	void cleanUp();
private:
	MapController* MC;
	PlayerController* PC;
};