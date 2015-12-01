#pragma once
#include "ILog.h"

class Logger: public ILog
{
public:
	Logger();
	virtual void displayLog();
	virtual void update() { this->displayLog(); };
	~Logger();
};
