#include "GameController.h"

/// Default constructor
GameController::GameController() {
	MapController MC;
	PlayerController PC;
}

/// Destructor 
GameController::~GameController() {

}

/// 
void GameController::startUpPhase() {

	PC->addPlayerToGame(numOfPlayers);
}

void GameController::runGame() {
	/* loop {
	currentPlayer = PC.getWhoseTurn();
	reinforcementPhase(currentPlayer);
	fortificationPhase(currentPlayer);
	}
	*/
}

void GameController::reinforcementPhase(Player* player) {

}

//void GameController::battlePhase() {}

void GameController::fortificationPhase(Player* player) {

}