#pragma once
#include "LogDecorator.h"
class LogStartup: public LogDecorator
{
public:
	LogStartup(ILog* logger) : LogDecorator(logger) {};
	virtual void displayLog();
	virtual void update() { this->displayLog(); };
	~LogStartup();
};

