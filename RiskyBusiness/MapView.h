#pragma once
#include "Board.h"
#include "Observer.h"
#include "MapController.h"

class MapView: public Observer
{
public:
	MapView();
	~MapView();
	void update(); // calls display() when triggered by the subject (observer pattern)
	void displayBoard();
private:
	int endX = 69;
	int endY = 36;
	int rowHeight;
	int colWidth;
	Board* board;
	MapController mapC;
};

