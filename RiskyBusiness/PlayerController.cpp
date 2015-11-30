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
		int color = colors.assignNewColor();
		handle->print("What is the player ");
		handle->print(to_string(i + 1), color);
		handle->print("'s name?\n");
		cin >> playerName;
		player = new Player(playerName);
		player->setColor(color);
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
