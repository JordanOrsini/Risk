#pragma once
//CONTROLLER
#include "Map.h"
class MapController {
public:
	MapController();
	~MapController();
	void loadMapFromFile();
	void createMap();
	void editMap();
	void saveMapToFile();
	bool testMap(); //test for correctness

					//New
	bool testMapHasCountries();
	bool testMapIsConnected();
	bool testEachContinentIsConnected();
	bool testContinentsAreValid();
	Map* getMap();
private:
	Map* map;
};