#pragma once
#include "ILog.h"

class LogDecorator: public ILog
{
public:
	LogDecorator(ILog* logger);
	virtual void displayLog() { logger->displayLog(); };
	~LogDecorator();
private:
	ILog* logger;
};

