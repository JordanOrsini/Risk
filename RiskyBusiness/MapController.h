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
	void testMap(); //test for correctness
private:
	Map* map;
};