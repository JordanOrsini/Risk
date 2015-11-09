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
	bool quitFlag = false;
	Player* currentPlayer = new Player();

	do {
	currentPlayer = PC->getWhoseTurn();
	//reinforcementPhase(currentPlayer); //uncomment once implemented
	//fortificationPhase(currentPlayer); //uncomment once implemented

	//ask if want to quit

	} while (!quitFlag);
}

/** Reinforcements are distributed as follows:
*	- The total number of countries owned by a player is divided by 3 and rounded down. If this is less than 3, then it is rounded up to 3 armies
*	- If the player owned an entire continent, they get a bonus depending on the bonus of that continent
*/
void GameController::reinforcementPhase(Player* player) {
	int numberOfCountriesOwned;
	int reinforcements = 0;

	numberOfCountriesOwned = player->countriesOwned.size();

	reinforcements = numberOfCountriesOwned / 3;

	if (reinforcements < 3) {
		reinforcements = 3;
	}

	reinforcements += player->getContinentBonus();

	//TO-DO: prompt user to distrubute reinforcements
}

//void GameController::battlePhase() {}

void GameController::fortificationPhase(Player* player) {

}

void GameController::cleanUp() {

}