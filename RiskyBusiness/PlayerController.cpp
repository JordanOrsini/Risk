#include "PlayerController.h"

PlayerController::PlayerController() {
	whoseTurn = 0;
}

PlayerController::~PlayerController() {
	for (int i = 0; i < this->playerList.size(); i++) {
		delete this->playerList.at(i);
	}
}

void PlayerController::addPlayerToGame(int numOfPlayers) {
	Colors colors;
	string playerName;
	Player* player;
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "What is the player " << i + 1 <<"'s name?" << endl;
		cin >> playerName;
		player = new Player(playerName);
		player->setColor(colors.assignNewColor());
		this->playerList.push_back(player);
	}
}

Player* PlayerController::getTurn() {
	if (playerList.size() == 0)
		return nullptr;
	return playerList.at(whoseTurn);
}
Player* PlayerController::nextTurn() {
	if (whoseTurn == playerList.size() - 1) {
		whoseTurn = 0;
	}
	else {
		whoseTurn++;
	}
	return playerList.at(whoseTurn);
}
