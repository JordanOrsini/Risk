#pragma once
//CONTROLLER
#include "MapController.h"
#include "PlayerController.h"

class GameController {
public:
	GameController();
	~GameController();
	void startUpPhase();
	void runGame();
		/* loop {
		currentPlayer = PC.getWhoseTurn();
		reinforcementPhase(currentPlayer);
		fortificationPhase(currentPlayer);
		}
		*/

	void reinforcementPhase(Player* player);
	//void battlePhase();
	void fortificationPhase(Player* player);
	//int rollDice();
private:
	MapController MC;
	PlayerController PC;
};