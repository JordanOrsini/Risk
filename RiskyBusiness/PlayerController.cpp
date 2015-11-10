#include "PlayerController.h"

PlayerController::PlayerController() {
	whoseTurn = 0;
}

PlayerController::~PlayerController() {
	//need to add deletes for players
}

void PlayerController::addPlayerToGame(int numOfPlayers) {

	string playerName;
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "What is the player's name?" << endl;
		cin >> playerName;
		this->playerList.push_back(new Player(playerName));
	}
}

Player* PlayerController::getWhoseTurn() {
	if (whoseTurn == (playerList.size() - 1)) {
		whoseTurn = 0;
		return playerList[whoseTurn];
	}

	whoseTurn++;
	return playerList[whoseTurn];
}
