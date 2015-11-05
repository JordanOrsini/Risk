#pragma once
// CONTROLLER
#include "Player.h"

class PlayerController {
public:	
	PlayerController();
	~PlayerController();
	bool addPlayerToGame();
	bool removePlayerFromGame(Player* player);
	Player* getWhoseTurn();
	//void attack(Player* attackingPlayer, Player* defendingPlayer);
private:
	vector<Player*> playerList;
	int whoseTurn; // refers to player list
};