#include "LogStartup.h"


void LogStartup::displayLog() {
	LogDecorator::displayLog();
	cout << this->getStartupTroopsAdded() << " troops were added successfully to " << this->getCountry() << "." << endl << endl;
}
LogStartup::~LogStartup()
{
}
