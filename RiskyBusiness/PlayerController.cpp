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
		Player* player = new Player(playerName);
		playerList.push_back(player);
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
