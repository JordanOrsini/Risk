#pragma once
#include "Observer.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

class IGameStats : public Observer
{
public:
	IGameStats(Player* player) { this->player = player; };
	virtual void displayStats() = 0;
	virtual void update() = 0;
	Player* getPlayer() { return this->player; };
private:
	Player* player;
};

class GameStats : public IGameStats
{
	GameStats(Player* player) : IGameStats(player) {};
	virtual void displayStats();
	virtual void update() { this->displayStats(); };
	int getNumOfCountries();
	int getTotalArmies();
	int getTotalCards();
	~GameStats() {};
};

class GameStatsDecorator : public IGameStats
{
public:
	GameStatsDecorator(IGameStats* stats);
	virtual void displayStats() { stats->displayStats(); };
	virtual void update() { this->displayStats(); };
	~GameStatsDecorator() { delete this->stats; };
private:
	IGameStats* stats;
};

class GameWorldPercentage : public GameStatsDecorator
{
public:
	GameWorldPercentage(IGameStats* stats) : GameStatsDecorator(stats) {};
	virtual void displayStats();
	virtual void update() { this->displayStats(); };
	double getWorldOwnership();
	~GameWorldPercentage() {};
};

class GameBattles : public GameStatsDecorator
{
public:
	GameBattles(IGameStats* stats) : GameStatsDecorator(stats) {};
	virtual void displayStats();
	virtual void update() { this->displayStats(); };
	~GameBattles() {};
};


