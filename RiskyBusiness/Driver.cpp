#include "GameController.h"
#include "MapView.h"

int main() {
	srand(time(0)); //used to randomize number when rand() is used

	MapView mapView;
	mapView.displayBoard();

	GameController GC;

	GC.startUpPhase();

	GC.runGame();

	GC.cleanUp(); //call destructors and all
}