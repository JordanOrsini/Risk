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
	Board();
	Board(int startX,int startY,int endX, int endY);
	~Board();
	void setNumRows(int rows);
	void setNumCols(int columns);
	void setRowHeight(int r, int height);
	void setColWidth(int c, int height);
	void drawBoard();
	void clearBoard();
	void gotoXYPrint(int x, int y, char chr);
	void gotoXYPrint(int x, int y, string str);

private:
	void drawBorders();
	int startX, startY, endX, endY;
	int numRows, numCols;
	int rowHeights[5];
	int colWidths[5];
	void gotoXY(int x, int y);
};

