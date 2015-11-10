#include "GameController.h"
#include "MapView.h"

int main() {
	srand(time(0)); //used to randomize number when rand() is used

<<<<<<< HEAD
	//ask user if they want to edit/make map
	MapController discard; 
	
	
	//Start game
	//choose map

	GameController GC;
=======
	GameController* GC = new GameController();
>>>>>>> Print map only for current player.

	MapView* mapView = new MapView(GC);
	mapView->displayBoard();

	GC->startUpPhase();

	GC->runGame();

	GC->cleanUp(); //call destructors and all
}