#include "GameController.h"
#include "MapView.h"
#include "LogStartup.h"
#include "Logger.h"

int main() {
	ILog* test = new LogStartup(new Logger());
	test->setStartupTroopsAdded(29);
	test->setCountry("Hayastan");
	test->displayLog();
	system("pause");
	/*
	// Make sure to set your console screen size to full screen

	system("COLOR 0A"); // green on black
	// Pregame map creation
	MapView tempView; 

	// Start actual game
	GameController* GC = new GameController();

	MapView* mapView = new MapView(GC);

	GC->startUpPhase();

	GC->runGame();

	*/
}