#include "GameController.h"

int main() {
	srand(time(0)); //used to randomize number when rand() is used

	GameController GC;

	GC.startUpPhase();

	GC.runGame();

	GC.cleanUp(); //call destructors and all
}