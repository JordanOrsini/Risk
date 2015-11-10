// Inspired by http://www.softwareandfinance.com/Visual_CPP/TextMode_Grid.html
#pragma once
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

class Board
{
public:
	Board(int startX, int startY, int endX, int endY);
	~Board();
	void setNumRows(int rows);
	void setNumCols(int columns);
	int getRowHeight();
	int getColumnWidth();
	int getHeight();
	int getWidth();
	void drawBoard();
	void clearBoard();
	void gotoXYPrint(int x, int y, char chr);
	void gotoXYPrint(int x, int y, string str);
	int getStartX();
	int getStartY();

private:
	void drawBorders();
	int startX, startY, endX, endY;
	int width, height;
	int numRows, numCols;
	int rowHeight;
	int colWidth;
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	void gotoXY(int x, int y);
};

