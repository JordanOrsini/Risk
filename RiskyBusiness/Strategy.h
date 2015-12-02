#pragma once
#include "Player.h"
#include "ConsoleHandler.h"

class Strategy
{
public: 
	virtual void attack(Player * player) = 0; 
	ConsoleHandler* handle = ConsoleHandler::getInstance();
};

class UserStrategy : public Strategy
{
public: 
	void attack(Player* player); 
};