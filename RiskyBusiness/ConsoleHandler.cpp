#include "ConsoleHandler.h"


/*
 Only one instance of this class is needed
*/

ConsoleHandler* ConsoleHandler::instance = nullptr;

ConsoleHandler* ConsoleHandler::getInstance() {
	if (!instance)
		instance = new ConsoleHandler();

	return instance;
}

int ConsoleHandler::getCusrsorPosition() {
	GetConsoleScreenBufferInfo(this->h, &SBInfo);
	return SBInfo.dwCursorPosition.Y;
}

void ConsoleHandler::gotoXY(int x, int y)
{
	COORD ord;
	ord.X = x;
	ord.Y = y;
	this->setConsoleCursorPosition(ord);
}

void ConsoleHandler::gotoXYPrint(int x, int y, string str)
{
	this->gotoXYPrint(x, y, str, 10);
}

void ConsoleHandler::gotoXYPrint(int x, int y, string str, int color)
{
	this->gotoXY(x, y);
	this->setConsoleTextAttribute(color);
	cout << str;
}

void ConsoleHandler::gotoXYPrint(int x, int y, char chr)
{
	this->gotoXY(x, y);
	cout << chr;
}

void ConsoleHandler::print(string str, int color) {

}

