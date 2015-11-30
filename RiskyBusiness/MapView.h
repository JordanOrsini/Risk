#pragma once
#include "Board.h"
#include "Observer.h"
#include "GameController.h"
#include "ConsoleHandler.h"

class MapView: public Observer
{
public:
	MapView(); 
	MapView(GameController* gameC);
	~MapView();
	void update(); // calls display() when triggered by the subject (observer pattern)
	void displayBoard();
	void editMap(MapController* tempMC); 
	void preGameMapCreation(); 

private:
	int endX = 145;
	int endY = 36;
	int rowHeight;
	int colWidth;
	Board* board;
	MapController* mapC;
	GameController* gameC;
	ConsoleHandler* handle = ConsoleHandler::getInstance();
};

