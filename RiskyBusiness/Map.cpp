#include "Map.h"
#include <string>

using namespace std;

// -------------------------------------------------------MAP CLASS IMPLEMENTATION-------------------------------------------------------//

// Default Constructor, Not used for anything
Map::Map() {}

// Constructor. Used when creating a new map from scratch. 
Map::Map(string name, string author)
{
	this->name = name;
	this->author = author;
	this->imageFile = " ";
	this->wrap = " ";
	this->scroll = " ";
	this->warn = " ";
}

// Constructor. Used when reading a map from an input file. Most parameters are from input file. 
Map::Map(string name, string author, string imageFile, string wrap, string scroll, string warn)
{
	this->name = name;
	this->author = author;
	this->imageFile = imageFile;
	this->wrap = wrap;
	this->scroll = scroll;
	this->warn = warn;
}

// Default Destructor
Map::~Map() {}

// Given name of a country, returns the pointer to the country. Return NULL if not found
Country* Map::getCountryPointerByName(string name)
{
	for (std::size_t i = 0; i < allCountries.size(); i++)
	{
		if (name == (*allCountries[i]).getName())
			return allCountries[i];
	}

	return NULL;
}

// Return the pointer to a country by giving the name
Continent* Map::getContinentPointerByName(string name)
{
	for (std::size_t i = 0; i < allContinents.size(); i++)
	{
		if (name == (*allContinents[i]).getName())
			return allContinents[i];
	}

	return NULL;
}

// Tests if the map is a connected graph. Returns 'true' if it is connected.
bool Map::mapIsConnected() { return true; }

// Add a continent (already created) to the map
void Map::addContinent(Continent* cName)
{
	allContinents.push_back(cName);
}

// Add a country (already created) to the map
void Map::addCountry(Country* cName)
{
	allCountries.push_back(cName);
}

// -------------------------------------------------------CONTINENT CLASS IMPLEMENTATION-------------------------------------------------------//

// Default Constructor, Not used for anything
Continent::Continent() {}

// Main constructor. 
Continent::Continent(string continentName, int continentValue)
{
	name = continentName;
	bonusValue = continentValue;
}

// Default Destructor
Continent::~Continent() {} //default dtor

						   // Test if the continent is a connected subgraph. Returns 'true' if it is connected
bool Continent::continentIsConnected() { return true; }

// Add a country (already created) to the continent
void Continent::addCountry(Country* cName)
{
	subCountries.push_back(cName);
}



// -------------------------------------------------------COUNTRY CLASS IMPLEMENTATION-------------------------------------------------------//

// Default Constructor, not used for anything
Country::Country() {}

// Main Constructor. 
Country::Country(string countryName, int x, int y, string continentName, string listOfAdjacencies)
{
	numOfArmies = 0; // No armies have been placed
	connected = false; // Country not yet linked to map


	name = countryName;
	this->x = x;
	this->y = y;
	parentContinentName = continentName;

	cout << countryName << ", " << x << ", " << y << ", " << parentContinentName << ", " << listOfAdjacencies << endl;

	/*
	Note: We pass 'listOfAdjacencies' as a string that contains the name of all adjacent countries.
	These are not yet used to create the vector of pointers to adjacent countries because the other
	countries may not have been loaded yet (and thus have no pointers). We wait for all countries to
	be loaded, and then the MapController will link all countries based on this string. In the meantime
	create an array of the names of adjacent countries for quicker processing later. Similarly,
	parentContinentName will also be used later to link to *parentContinent
	*/

	int pos;					//Used to keep track of position in string
	string temp;				//Temporarily stores name of adjacent country


	while (listOfAdjacencies != "")
	{
		// Get adjacent country name and remove from initializationString. Names are separated by commas
		if (listOfAdjacencies.find(",") == string::npos)			// No more commas -> last name in the string
		{
			temp = listOfAdjacencies;
			listOfAdjacencies = "";
		}
		else
		{
			pos = listOfAdjacencies.find(",");
			temp = listOfAdjacencies.substr(0, pos);
			listOfAdjacencies = listOfAdjacencies.substr(pos + 1); // Remove name from string
		}

		// Add adjacent country to vector of country names. 
		tempAdjCountryNames.push_back(temp);
	}
}

// Default Destructor
Country::~Country() {}

// Test that the country has neighbours. Returns 'true' if the country has adjacent neighbours. 
bool Country::countryIsconnected()
{
	return true;
}

// Add a countries pointer to the list of adjacent countries
void Country::addAdjCountry(Country* cName)
{
	adjacentCountries.push_back(cName);
}

// Return the number of armies placed on the country
int Country::getArmyCount()
{
	return numOfArmies;
}

// Set method to change the current number of armies within the country
void Country::setArmyCount(int newCount)
{
	if (newCount < 0)
		numOfArmies = 0;
	else
		numOfArmies = newCount;
}
