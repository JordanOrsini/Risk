#pragma once
#include "Observer.h"
#include "Player.h"
#include "ConsoleHandler.h"
#include <iostream>
#include <string>

/*
Log decorator interface
*/
class ILog : public Observer
{
public:
	ILog(Player* player);
	virtual void displayLog() = 0;
	virtual void update() = 0;
	Player* getPlayer() { return this->player; };
private:
	Player* player;
};

class LogDecorator: public ILog
{
public:
	LogDecorator(ILog* logger);
	virtual void displayLog() { logger->displayLog(); };
	virtual void update() { this->displayLog(); };
	~LogDecorator();
private:
	ILog* logger;
};

class Logger : public ILog
{
public:
	Logger(Player* player): ILog(player) {};
	virtual void displayLog();
	virtual void update() { this->displayLog(); };
	~Logger() {};
};

class LogTimestamp: public LogDecorator
{
public:
	LogTimestamp(ILog* logger) : LogDecorator(logger) {};
	virtual void displayLog();
	virtual void update() { this->displayLog(); };
	~LogTimestamp() {};
private:
	string getTimestamp();
};

class LogPlayerName : public LogDecorator
{
public:
	LogPlayerName(ILog* logger) : LogDecorator(logger) {};
	virtual void displayLog();
	virtual void update() { this->displayLog(); };
	~LogPlayerName() {};
private:
	ConsoleHandler* handle = ConsoleHandler::getInstance();
};

