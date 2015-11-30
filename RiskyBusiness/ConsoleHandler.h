#pragma once
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <iostream>

using namespace std;

/*
 This class is used to print text with color
*/
class ConsoleHandler
{
public:
	HANDLE getHandle() { return this->h; };
	CONSOLE_SCREEN_BUFFER_INFO getBuffer() { return this->SBInfo; };
	static ConsoleHandler* getInstance();
	int getCusrsorPosition();
	void setConsoleCursorPosition(COORD ord) { SetConsoleCursorPosition(this->h, ord); };
	void setConsoleTextAttribute(int color) { SetConsoleTextAttribute(this->h, color); };
	void gotoXY(int x, int y);
	void gotoXYPrint(int x, int y, char chr);
	void gotoXYPrint(int x, int y, string str);
	void gotoXYPrint(int x, int y, string str, int color);
	void print(string str, int color);
private:
	ConsoleHandler() {};
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	static ConsoleHandler* instance;
};
