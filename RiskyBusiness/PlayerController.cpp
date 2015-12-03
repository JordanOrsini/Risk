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

void PlayerController::checkForWin()
{
	bool notFinished = true;
	int playerToDeleteIndex = 0;
	
	//checks to see if player is dead, if the boolean alive == false, removes player from game loop
	while (notFinished)
	{
		notFinished = false;
		for (int i = 0; i < playerList.size(); i++)
		{
			if (playerList.at(i)->alive == false)
			{
				playerToDeleteIndex = i;
				notFinished = true;
			}
		}

		//deletes player
		if (notFinished)
		{
			playerList.erase(playerList.begin() + playerToDeleteIndex);
		}
	}

	//checks to see if there is a winner in the game (if playerList size is of length 1)
	if (playerList.size() == 1)
	{
		cout << "GAME OVER!" << endl << endl;
		playerList.at(0)->setLogMessage("Player \"" + playerList.at(0)->getPlayerName() + "\" is the winner!");
		cout << "Thank you for playing!" << endl;
		system("pause");
		system("exit");
	}

}
