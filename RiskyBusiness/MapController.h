#pragma once
//CONTROLLER
#include "Map.h"
#include <string>

class MapController {
public:
	MapController();
	~MapController();
	void loadMapFromFile();
	void createMap(string author, string mapName);
	void editMap();
	void saveMapToFile();
	bool testMap(); //test for correctness

	// Functions to replace editMap() in order to work with the view
	void createContinent(string name, int bonusValue); 
	bool addCountryToContinent(string countryName, int x, int y, string continentName); 
	bool addNeighborToCountry(string country, string newNeighbor); 

					//New
	bool testMapHasCountries();
	bool testMapIsConnected();
	bool testEachContinentIsConnected();
	bool testContinentsAreValid();
	Map* getMap();
private:
	Map* map;
};