#include "GameController.h"
#include "MapView.h"

int main() {
	srand(time(0)); //used to randomize number when rand() is used

	GameController GC;

	MapView mapView(GC.getMC());
	mapView.displayBoard();

	GC.startUpPhase();

	GC.runGame();

	GC.cleanUp(); //call destructors and all
}