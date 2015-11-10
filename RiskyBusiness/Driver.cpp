#include "GameController.h"
#include "MapView.h"

int main() {
	srand(time(0)); //used to randomize number when rand() is used

	// Pregame map creatio n
	MapView tempView; 

	// Start actual game
	GameController* GC = new GameController();

	MapView* mapView = new MapView(GC);

	GC->startUpPhase();

	GC->runGame();

	GC->cleanUp(); //call destructors and all
}