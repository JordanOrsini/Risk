#pragma once
#include "ILog.h"

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

