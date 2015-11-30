#include "LogDecorator.h"



LogDecorator::LogDecorator(ILog* logger)
{
	this->logger = logger;
}


LogDecorator::~LogDecorator()
{
	delete this->logger;
}
