// Inspired by http://www.softwareandfinance.com/Visual_CPP/TextMode_Grid.html
#pragma once
#include <iostream>
#include <string>
#include "ConsoleHandler.h"

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
	
	int getStartX();
	int getStartY();

private:
	ConsoleHandler* handle = ConsoleHandler::getInstance();
	void drawBorders();
	int startX, startY, endX, endY;
	int width, height;
	int numRows, numCols;
	int rowHeight;
	int colWidth;
};

