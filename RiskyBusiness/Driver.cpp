#include "GameController.h"

int main() {
	GameController GC;

	GC.startUpPhase();

	GC.runGame();

	/*
	while (1) { //need to change condition
		GC.reinforcementPhase();
		//GC.battlePhase();
		GC.fortificationPhase();
	}*/

	GC.cleanUp(); //call destructors and all
}