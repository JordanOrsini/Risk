#include "GameController.h"

int main() {
	GameController GC;

	GC.startUpPhase();

	GC.runGame();

	GC.cleanUp(); //call destructors and all
}