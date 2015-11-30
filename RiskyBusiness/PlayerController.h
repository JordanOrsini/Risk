#pragma once
// CONTROLLER
#include "Player.h"
#include "Colors.h"
#include "ConsoleHandler.h"

class PlayerController {
public:	
	PlayerController();
	~PlayerController();
	void addPlayerToGame(int numberOfPlayers);
	bool removePlayerFromGame(Player* player);
	Player* nextTurn();
	Player* getTurn();
	vector<Player*> getPlayerList() { return playerList; };
	//void attack(Player* attackingPlayer, Player* defendingPlayer);
private:
	ConsoleHandler* handle = ConsoleHandler::getInstance();
	vector<Player*> playerList;
	int whoseTurn; // refers to player list
};