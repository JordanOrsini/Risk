#include "PlayerController.h"

PlayerController::PlayerController() {

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