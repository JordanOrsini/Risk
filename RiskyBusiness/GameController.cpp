#include "GameController.h"

/// Default constructor
GameController::GameController() {
	MapController* MC = new MapController();
	PlayerController* PC = new PlayerController();
}

/// Destructor 
GameController::~GameController() {
	delete MC;
	MC = NULL;
	delete PC;
	PC = NULL;
}

/** This is the start-up phase of the game
*   It will prompt the user for a user-saved map file
*	and then load the map as a connected graph.
*	It will also prompt the user for the number of players
*	and randomly assign the countries to the players.
*/
void GameController::startUpPhase() {
	int numOfPlayers;

	// TO-DO: ask for user-saved file and load

	cout << "How many players will be playing?" << endl;
	cin >> numOfPlayers;

	// TO-DO: check if player number and number of countries make sense

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