#pragma once
#include "Player.h"
#include "ConsoleHandler.h"
#include <string>

class Strategy
{
public: 
	virtual void attack(Player * player) = 0; 
	ConsoleHandler* handle = ConsoleHandler::getInstance();
	string name; 
};

class UserStrategy : public Strategy
{
public: 
	UserStrategy() { name = "User Defined"; };
	void attack(Player* player); 
};

class AggressiveStrategy: public Strategy
{
public:
	AggressiveStrategy() { name = "Aggressive"; };
	void attack(Player* player);
};

class DefensiveStrategy : public Strategy
{
public:
	DefensiveStrategy() { name = "Defensive"; }; 
	void attack(Player* player);
};

class RandomStrategy : public Strategy
{
public:
	RandomStrategy() { name = "Random"; }; 
	void attack(Player* player);
};
