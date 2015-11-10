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
	int width = 68;
	int height = 35;
	Board* board = new Board( width, height);
	MapController mapC;
};

