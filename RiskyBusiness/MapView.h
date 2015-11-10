#pragma once
#include "Board.h"
#include "MapController.h"

class MapView
{
public:
	MapView();
	~MapView();
	void displayBoard();
private:
	int endX = 69;
	int endY = 36;
	int rowHeight;
	int colWidth;
	Board* board;
	MapController mapC;
};

