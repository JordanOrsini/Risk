#include "LogDecorator.h"

//--------------------------ILog Decorator interface-------------------

ILog::ILog(Player* player) {
	this->player = player;
}

//--------------------------LogDecorator class-------------------------

LogDecorator::LogDecorator(ILog* logger): ILog(logger->getPlayer())
{
	this->logger = logger;
}

LogDecorator::~LogDecorator()
{
	delete this->logger;
}

//--------------------------Logger class--------------------------------

void Logger::displayLog() {
	cout << "[LOG] - " << this->getPlayer()->logMessage << " - ";
}

//--------------------------LogTimestamp class--------------------------

void LogTimestamp::displayLog() {
	LogDecorator::displayLog();
	cout << "[" << this->getTimestamp() << "] ";
}

string LogTimestamp::getTimestamp() {
	time_t now;
	struct tm *current;
	now = time(0);
	current = localtime(&now);
	string str = asctime(current);
	str = str.substr(0, str.length() - 1);
	return str;
}

//--------------------------LogPlayerName class-------------------------

void LogPlayerName::displayLog() {
	LogDecorator::displayLog();
	handle->print("[" + this->getPlayer()->getPlayerName() + "] ", this->getPlayer()->getColor());
}