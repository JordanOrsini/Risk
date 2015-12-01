#include "GameController.h"
#include "MapView.h"

int main() {
	// Make sure to set your console screen size to full screen

	system("COLOR 0A"); // green on black
	// Pregame map creation
	MapView tempView; 

	// Start actual game
	GameController* GC = new GameController();

	MapView* mapView = new MapView(GC);

	GC->runGame();

}