#include "MapController.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;
using std::cout;
using std::cin;

// Default constructor. Note: Nothing needs to be implemented. 
MapController::MapController() {}

// Default destructor. 
MapController::~MapController()
{
	delete map;
	map = NULL;
}

// Method to read map from user specified input file
void MapController::loadMapFromFile()
{
	string mapFile;
	string mapName;
	fstream fileReader;

	// Ask user for *.map file
	while (1)
	{
		cout << "Please type in the name of the *.map file: ";
		cin >> mapFile;
		cout << "The name of the map file is: " << mapFile << endl;

		if (mapFile.find(".map") == string::npos) {
			cout << "The file is not a *.map file." << endl;
			cout << "Try a different name." << endl << endl;
		}
		else {
			fileReader.open(mapFile, ios::in);
			if (fileReader.good() == 0)
				cout << "There was an error reading the file. Try again." << endl << endl;
			else
			{
				cout << "File successfully opened." << endl << endl;
				break;
			}
		}
	}

	// Get map name from map file name
	mapName = mapFile.substr(0, mapFile.find(".map"));

	//------------ READ IN WORLD MAP DATA ------------//
	string line;			// Used to read in one line from the file at a time
	string temp;			// Temporary string
	int pos;				// Temporariliy store the length of the string

	string author;			// These temporarily store data about the Map to be used in the constructor
	string imageFile;
	string wrap;
	string scroll;
	string warn;

	// First line of file should be: "[Map]"
	getline(fileReader, line);
	if (line.compare("[Map]") != 0)
	{
		cout << "ERROR:" << endl << "The first line of the input file should be [Map]." << endl;
		cout << "Exiting program..." << endl;
		system("pause");
		exit(1);
	}

	cout << endl << "LOADING MAP FROM FILE" << endl << "----------------------" << endl << endl;
	cout << "Map \"" << mapName << "\" Information: " << endl;


	//Read in info until there is no more
	getline(fileReader, line);
	while (line != "")
	{
		pos = line.find("=");
		temp = line.substr(0, pos + 1);

		if (temp.compare("author=") == 0)
		{
			pos = 7;
			author = line.substr(pos);
			cout << "\t -author: " << author << endl;
		}

		if (temp.compare("image=") == 0)
		{
			pos = 6;
			imageFile = line.substr(pos);
			cout << "\t -image: " << imageFile << endl;
		}

		if (temp.compare("wrap=") == 0)
		{
			pos = 5;
			wrap = line.substr(pos);
			cout << "\t -wrap: " << wrap << endl;
		}

		if (temp.compare("scroll=") == 0)
		{
			pos = 7;
			scroll = line.substr(pos);
			cout << "\t -scroll: " << scroll << endl;
		}
		if (temp.compare("warn=") == 0)
		{
			pos = 5;
			warn = line.substr(pos);
			cout << "\t -warn: " << warn << endl;
		}

		getline(fileReader, line);
	}

	cout << endl;

	// create the map
	map = new Map(mapName, author, imageFile, wrap, scroll, warn);


	//------------ READ IN CONTINENT DATA ------------//
	string continentName;		// Temporarily stores data from input file
	int continentValue;			// Temporarily stores data from input file
	Continent* newContinent;		// Pointer to temporarily store new continents

	while (line == "")
		getline(fileReader, line);

	// First line should be: "[Continents]"
	if (line.compare("[Continents]") != 0)
	{
		cout << "ERROR:" << endl << "The next section of the input file after [Map] should be [Continents]." << endl;
		cout << "Exiting program..." << endl;
		system("pause");
		exit(1);
	}

	cout << endl << "Continents: " << endl;

	//Read in continents until there are no more
	getline(fileReader, line);
	while (line != "")
	{
		// Data is in file as "continentName=continentValue"
		pos = line.find("=");
		continentName = line.substr(0, pos);		// Parse out name
		temp = line.substr(pos + 1);
		continentValue = atoi(temp.c_str());		// Parse out value

													// Create Continent and add it to the Map
		newContinent = new Continent(continentName, continentValue);
		(*map).addContinent(newContinent);

		cout << "\t" << continentName << endl;

		// Read in next line
		getline(fileReader, line);
	}

	//------------ READ IN COUNTRY DATA ------------//
	Country* newCountry;		// Pointer to temporarily store new country
	Continent* tempContinent;	// Pointer to temporarily store address of Continents
								//int pos;					// Keeps track of position of character in a string
	string countryName;			// Following variables temporarily store data from input file. Used to create countries
	string xAxis, yAxis;
	int x, y;
	string parentContinent;


	while (line == "") {
		getline(fileReader, line);
	}

	// First line should be: "[Territories]"
	if (line.compare("[Territories]") != 0)
	{
		cout << "ERROR:" << endl << "The next section of the input file after [Continents] should be [Territories]." << endl;
		cout << "Exiting program..." << endl;
		system("pause");
		exit(1);
	}

	cout << endl << "Countries: " << endl;

	// Read in territories until there are no more
	while (getline(fileReader, line))
	{
		if (line != "")
		{
			// get name
			pos = line.find(",");
			countryName = line.substr(0, pos);

			// Check that the country has not already been added to the map. If it has, declare an error. 
			Country * temp;
			temp = (*map).getCountryPointerByName(countryName); // If the country does not exist, then temp SHOULD be null

			if (temp != NULL)
			{
				cout << "ERROR:" << endl << "Country " << countryName << " has been declared more than once in the *.map file" << endl;
				cout << "Exiting program..." << endl;
				system("pause");
				exit(1);
			}

			//get xAxis
			line = line.substr(pos + 1);
			pos = line.find(",");
			xAxis = line.substr(0, pos);
			x = atoi(xAxis.c_str());

			//get yAxis
			line = line.substr(pos + 1);
			pos = line.find(",");
			yAxis = line.substr(0, pos);
			y = atoi(yAxis.c_str());

			//get continent
			line = line.substr(pos + 1);
			pos = line.find(",");
			parentContinent = line.substr(0, pos);

			//check that the continent exists
			tempContinent = (*map).getContinentPointerByName(parentContinent);

			if (tempContinent == NULL)
			{
				cout << "ERROR:" << endl << "Country " << countryName << " has been declared to have parent continent " << parentContinent << " which does not exist" << endl;
				cout << "Exiting program..." << endl;
				system("pause");
				exit(1);
			}

			// keep rest of string to initialize adjacent countries later
			line = line.substr(pos + 1);

			// Create new country and add it to the Map and correct continent
			newCountry = new Country(countryName, x, y, parentContinent, line);
			(*map).addCountry(newCountry);
			(*tempContinent).addCountry(newCountry);

		}
	}

	// Link each territory with thier neighbour
	Country* countryToAddNeighbors;						// Placeholder for easier reading
	Country* newNeighbor;								// Placeholder for easier reading
	string newNeighborStr;								// Placeholder for easier reading

	cout << endl << "All territories have been added. Linking territories..." << endl << endl;

	for (std::size_t i = 0; i < ((*map).allCountries).size(); i++)
	{

		countryToAddNeighbors = (*map).allCountries[i];
		for (std::size_t i = 0; i < (*countryToAddNeighbors).tempAdjCountryNames.size(); i++) {
			newNeighborStr = (*countryToAddNeighbors).tempAdjCountryNames[i];
			newNeighbor = (*map).getCountryPointerByName(newNeighborStr);

			//Check that neighbor exists!
			if (newNeighbor == NULL)
			{
				cout << "ERROR:" << endl << "Country " << countryName << " has been declared to have neighbor country " << newNeighborStr << " which does not exist" << endl;
				cout << "Exiting program..." << endl;
				system("pause");
				exit(1);
			}

			(*countryToAddNeighbors).addAdjCountry(newNeighbor);
		}
	}

	//------------ END OF INITIALIZATION ------------//
	cout << "The map has been successfully loaded." << endl << endl;

	fileReader.close();
}


// Method to create map from scratch
void MapController::createMap()
{
	string mapName;
	string author;

	cout << endl << "Enter your name: ";
	cin >> author;
	cout << endl << "Enter the name of the new map: ";
	cin >> mapName;

	map = new Map(mapName, author);

	cout << endl << "Congratulations, you have created a new blank map.\nPlease note that an empty map cannot be saved as valid.\n\n";
}

void MapController::createContinent(string name, int bonusValue)
{
	// Create continent and add it to the map
	Continent* newContinent = new Continent(name, bonusValue);
	(*map).addContinent(newContinent);
}

bool MapController::addCountryToContinent(string countryName, int x, int y, string continentName)
{
	// Test that continent actually exists, otherwise return false
	if ((*map).getContinentPointerByName(continentName) == NULL)
		return false; 

	// Create country 
	Country* newCountry = new Country(countryName, x, y, continentName, "");

	// Add it to the map
	(*map).addCountry(newCountry);

	// Add it to the continent
	(*(*map).getContinentPointerByName(continentName)).addCountry(newCountry);

	return true; 
}

bool MapController::addNeighborToCountry(string country, string newNeighbor)
{
	// Test that country exists
	if ((*map).getCountryPointerByName(country) == NULL)
		return false; 

	// Test that neighbor exists
	if ((*map).getCountryPointerByName(newNeighbor) == NULL)
		return false

	// Good to go, update both countries so they know they are each other's neighbor
	(*(*map).getCountryPointerByName(country)).addAdjCountry((*map).getCountryPointerByName(newNeighbor));
	(*(*map).getCountryPointerByName(newNeighbor)).addAdjCountry((*map).getCountryPointerByName(country));

	return true; 
}


// Method edit existing map (the map that is currently loaded)
void MapController::editMap()
{
	string userInput;
	string name, continentName, x, y, value, str;

	cout << endl << "EDITING MAP" << endl << "----------------------" << endl << endl;

	while (1)
	{
		cout << "How would you like to edit the map?\n";
		cout << "\t1) Create a new continent\n\t2) Create a new country (note: needs a continent to be assigned to)\n\t3) Define a country's neighbors\n\t4) Quit editing\n";
		cout << "Enter 1, 2, 3 or 4: ";
		cin >> userInput;

		while (userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4")
		{
			cout << "Please enter 1, 2, 3 or 4: ";
			cin >> userInput;
		}

		cout << endl;

		// CREATE A NEW CONTINENT
		if (userInput == "1")
		{
			cout << "Enter the name of the new continent: ";
			cin >> continentName;
			cout << "Enter the bonus value of owning the continent: ";
			cin >> value;

			// Create continent and add it to the map
			Continent* newContinent = new Continent(continentName, atoi(value.c_str()));
			(*map).addContinent(newContinent);

			cout << endl << continentName << " was added to the map." << endl << endl;
		}

		// CREATE A NEW COUNTRY
		if (userInput == "2")
		{
			cout << "Enter the name of the continent to add a new country to: ";
			cin >> continentName;
			while ((*map).getContinentPointerByName(continentName) == NULL)
			{
				cout << "Continent does not exist. Enter the name of the continent to add a new country to: ";
				cin >> continentName;
			}

			cout << "Enter the name of the new country: ";
			cin >> name;

			cout << "Enter an x-axis value: ";
			cin >> x;

			cout << "Enter a y-axis value: ";
			cin >> y;

			// Create country and add it to the map + continent
			Country* newCountry = new Country(name, atoi(x.c_str()), atoi(y.c_str()), continentName, "");
			(*map).addCountry(newCountry);
			(*(*map).getContinentPointerByName(continentName)).addCountry(newCountry);

			cout << endl << name << " was added to the map." << endl << endl;
		}

		// ADD NEIGHBORS TO A COUNTRY
		if (userInput == "3")
		{
			cout << "Enter the name of the country you wish to add neighbors: ";
			cin >> name;
			while ((*map).getCountryPointerByName(name) == NULL)
			{
				cout << "Country does not exist. Enter the name of the country to add neighbors to: ";
				cin >> name;
			}

			cout << "Please note that you can only add a country as a neighbor if it already exists.\nIf the country does not yet exist, please add it first and then add this country as its neighbor.\nAlso note that the adjacent country will have the opposite operation.\n\n";
			while (1)
			{
				cout << "Enter the name of the neighbor country (or type exit to quit): ";
				cin >> str;
				if (str == "exit")
					break;
				if ((*map).getCountryPointerByName(str) == NULL)
					cout << "The country does not exist, try again." << endl;
				else
				{
					// Add adjacent country to country
					(*(*map).getCountryPointerByName(name)).addAdjCountry((*map).getCountryPointerByName(str));
					// Don't forget to add country to adjacent country too!
					(*(*map).getCountryPointerByName(str)).addAdjCountry((*map).getCountryPointerByName(name));
					cout << "Added " << str << " as an adjacent country.\n";
				}


			}
			cout << "\nDone adding countries as neighbors.\n\n";
		}

		// EXIT EDITING PHASE
		if (userInput == "4")
		{
			cout << "Ending editing session. Test map again for correctness...\n";
			break;
		}

	}



}

// Method to save the current map to an output file
void MapController::saveMapToFile()
{
	cout << "\n\nSAVING MAP TO FILE\n" << "----------------------------\n";

	ofstream output((*map).getName() + ".map");
	output << "[Map]" << endl;
	output << "author=" << (*map).getAuthor() << endl;
	output << "image=" << (*map).getImage() << endl;
	output << "wrap=" << (*map).getWrap() << endl;
	output << "scroll=" << (*map).getScroll() << endl;
	output << "warn=" << (*map).getWarn() << endl;

	output << endl << "[Continents]" << endl;
	for (std::size_t i = 0; i < (*map).allContinents.size(); i++)
	{
		output << (*(*map).allContinents[i]).getName() << "=" << (*(*map).allContinents[i]).getBonusValue() << endl;
	}

	output << endl << "[Territories]" << endl;
	for (std::size_t i = 0; i < (*map).allCountries.size(); i++)
	{
		output << (*(*map).allCountries[i]).getName() << "," << (*(*map).allCountries[i]).getX() << "," << (*(*map).allCountries[i]).getY() << "," << (*(*map).allCountries[i]).getParentContinentName();
		for (std::size_t k = 0; k < (*(*map).allCountries[i]).adjacentCountries.size(); k++)
		{
			output << "," << (*(*(*map).allCountries[i]).adjacentCountries[k]).getName();
		}
		output << endl;
	}

	output.close();
}

// Method to test the currently loaded map for correctness. 
bool MapController::testMap()
{
	cout << endl << "TESTING MAP FOR CORRECTNESS" << endl << "----------------------------" << endl << endl;

	return testMapHasCountries() && testContinentsAreValid() && testMapIsConnected() && testEachContinentIsConnected();
}

// First check: Map must have countries to be a map
bool MapController::testMapHasCountries()
{
	if ((*map).allCountries.size() <= 1) {
		cout << "ERROR: The map has only one or fewer sub-countries. This is invalid." << endl;
		return false;
	}
	else
		cout << "The map has more than one country. This is valid." << endl << endl;
	return true;
}

// Method that tests that each continent has >1 countries
bool MapController::testContinentsAreValid() {
	//Placeholder to store the current continent
	Continent* tempContinent;
	bool returnVal = true;

	for (std::size_t i = 0; i < (*map).allContinents.size(); i++)
	{
		tempContinent = (*map).allContinents[i];
		if ((*tempContinent).subCountries.size() <= 1)
		{
			cout << "ERROR: " << (*tempContinent).getName() << " has only one or fewer sub-countries. This is invalid." << endl;
			returnVal = false;
		}
		else
			cout << (*tempContinent).getName() << " has a valid number of sub countries." << endl;
	}
	return returnVal;
}

// Method that tests that the map is a connected graph
bool MapController::testMapIsConnected()
{
	// Used to store if map is connected. Assume true, if not it will be changed
	bool connected = true;

	// Initialize every country to "not connected"
	for (std::size_t i = 0; i < (*map).allCountries.size(); i++)
		(*(*map).allCountries[i]).disconnect();

	// Use a Breadth-First-Traversal and mark each Country that has been reached. 
	// At the end of the traversal, if there are any unmarked countries then the map is disjoint

	queue <Country*> q;

	// Use first country loaded into the map as the starting point.
	Country* start = (*map).allCountries[0];
	q.push(start);

	//Placeholder to store the pointer to the current country
	Country* tempCountry, *tempAdjCountry;

	while (q.empty() == false)
	{
		tempCountry = q.front();
		q.pop();

		for (std::size_t i = 0; i < (*tempCountry).adjacentCountries.size(); i++)
		{
			tempAdjCountry = ((*tempCountry).adjacentCountries[i]);
			if ((*tempAdjCountry).isConnected() == false)
			{
				tempAdjCountry->connect();
				q.push(tempAdjCountry);
			}
		}
	}

	// Now check if there exists a country that cannot be reached

	for (std::size_t i = 0; i < (*map).allCountries.size(); i++)
	{
		if ((*(*map).allCountries[i]).isConnected() == false) // This country has not been reached by the BFT
		{
			connected = false;
		}
	}

	if (connected)
		cout << endl << "The map is a connected graph" << endl << endl;
	else
		cout << endl << "ERROR: The graph is not a connected graph." << endl << endl;

	return connected;
}

// Method that tests that each continent is a connected subgraph
bool MapController::testEachContinentIsConnected()
{
	//Placeholders to store the pointer to the current country/continent
	Country* tempCountry, *tempAdjCountry;
	Continent* tempContinent;

	//Stores is the continent is connected
	bool connected = true;
	bool returnVal = true;

	// Queue for the BFT
	queue <Country*> q;

	// Initialize every country to "not connected"
	for (std::size_t i = 0; i < (*map).allCountries.size(); i++)
		(*(*map).allCountries[i]).disconnect();

	// For each continent, use a Breadth-First-Traversal and mark each Country that has been reached. 
	// At the end of the traversal, if there are any unmarked countries then the continent is disjoint

	for (std::size_t i = 0; i < (*map).allContinents.size(); i++)
	{
		tempContinent = (*map).allContinents[i];
		connected = true;		//Assume continent is connected. Will be set to false if not

								//Use first country in the continent as the starting point
		Country* start = (*tempContinent).subCountries[0];
		q.push(start);


		while (q.empty() == false)
		{
			tempCountry = q.front();
			q.pop();

			for (std::size_t i = 0; i < (*tempCountry).adjacentCountries.size(); i++)
			{
				tempAdjCountry = ((*tempCountry).adjacentCountries[i]);
				if ((*tempAdjCountry).isConnected() == false && (*tempAdjCountry).getParentContinentName() == (*tempContinent).getName())
				{
					tempAdjCountry->connect();
					q.push(tempAdjCountry);
				}
			}
		}

		// Now check if there exists a country that cannot be reached

		for (std::size_t i = 0; i < (*tempContinent).subCountries.size(); i++)
		{
			if ((*(*tempContinent).subCountries[i]).isConnected() == false) // This country has not been reached by the BFT
			{
				connected = false;
				returnVal = false;
			}
		}

		if (connected)
			cout << "Continent " << (*tempContinent).getName() << " is a connected subgraph." << endl;
		else
			cout << "ERROR: Continent " << (*tempContinent).getName() << " is not a connected subgraph." << endl;

	}
	return returnVal;
}

Map* MapController::getMap() {
	return map;
}