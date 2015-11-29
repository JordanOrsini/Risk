#include "SaveLoadAdapter.h"
#include <fstream>

Map* LegacySaveLoadAdapter::load(string fileName)
{
	string mapFile = fileName;
	string mapName;
	fstream fileReader; 

	// Open the file
	fileReader.open(mapFile, ios::in);

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
	Map * map = new Map(mapName, author, imageFile, wrap, scroll, warn);


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


	while (line == ""){
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

			cout << countryName << ", " << x << ", " << y << ", " << parentContinent << ", " << line << endl;

		}
	}


	fileReader.close();

	return map; 
}

Map* NewSaveLoadAdapter::load(string fileName)
{
	string mapFile = fileName;
	string mapName;
	fstream fileReader;

	// Open the file
	fileReader.open(mapFile, ios::in);

	// Get map name from map file name
	mapName = mapFile.substr(0, mapFile.find(".altmap"));

	//------------ READ IN WORLD MAP DATA ------------//
	string line;			// Used to read in one line from the file at a time
	string temp;			// Temporary string
	int pos;				// Temporariliy store the length of the string

	string author;			// These temporarily store data about the Map to be used in the constructor
	string imageFile;
	string wrap;
	string scroll;
	string warn;

	// First line of file should be: "--MAP--"
	getline(fileReader, line);
	if (line.compare("--MAP--") != 0)
	{
		cout << "ERROR:" << endl << "The first line of the input file should be: --MAP--" << endl;
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
	Map * map = new Map(mapName, author, imageFile, wrap, scroll, warn);

	//------------ READ IN CONTINENT AND TERRITORY DATA ------------//
	// FOR CONTINENTS
	string continentName;		// Temporarily stores data from input file
	int continentValue;			// Temporarily stores data from input file
	Continent* newContinent;	// Pointer to temporarily store new continents

	//FOR TERRITORIES
	Country* newCountry;		// Pointer to temporarily store new country
	string countryName;			// Country value to be read from file
	string xAxis, yAxis;		// Country value to be read from file
	int x, y;					// Country value to be read from file
	string parentContinent;		// Country value to be read from file

	// Start reading file
	while (getline(fileReader, line))
	{
		// Check in case we have read past the end of the file
		if (fileReader.eof())
			break;

		// Ignore any empty lines
		if (line == "")
			getline(fileReader, line);

		// Once we read "--CONTINENT--" we have a new continent and its territories
		if (line.compare("--CONTINENT--") == 0)
		{
			// Next line will be the continent name
			getline(fileReader, line);
			pos = line.find("=");
			continentName = line.substr(pos + 1);

			// Second line will be the continent value
			getline(fileReader, line);
			pos = line.find("=");
			temp = line.substr(pos + 1);
			continentValue = atoi(temp.c_str());

			// Create Continent and add it to the Map
			newContinent = new Continent(continentName, continentValue);
			(*map).addContinent(newContinent);

			cout << endl << "Continent: " << continentName << endl;
			cout << "\tValue: " << continentValue << endl;
			cout << "\tTerritories: " << endl;
		}
		else if (line != "") // If we aren't reading in a continent, then we are reading the territories that belong to the last read continent (all are listed after --CONTINENT--; name= ; value = ; territories... )
		{
			// get territory name
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
			parentContinent = continentName;

			// keep rest of string (the list of adjacent countries) as a string to initialize adjacent countries later
			line = line.substr(pos + 1);

			// Create new country and add it to the Map and correct continent
			newCountry = new Country(countryName, x, y, parentContinent, line);
			map->addCountry(newCountry);
			(map->getContinentPointerByName(continentName))->addCountry(newCountry);

			// Output to screen
			cout << "\t\t- " << countryName << ", " << x << ", " << y << "  Neighbors: " << line << endl;
		}
		else {
			// Blank line, do nothing
		}

	}

	fileReader.close();

	return map; 
}

void LegacySaveLoadAdapter::save(Map* map)
{
	cout << "\n\nSAVING MAP TO FILE\n" << "----------------------------\n";

	ofstream output((*map).getName() + "-edited.map");
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

	for (std::size_t i = 0; i < map->allContinents.size(); i++)
	{
		// Follow by listing all of that continent's territories
		for (std::size_t j = 0; j < (*(*map).allContinents[i]).subCountries.size(); j++)
		{
			output << (*(*map).allContinents[i]).subCountries[j]->getName() << "," << (*(*map).allContinents[i]).subCountries[j]->getX() << "," << (*(*map).allContinents[i]).subCountries[j]->getY() << "," << (*(*map).allContinents[i]).subCountries[j]->getParentContinentName();

			// List that country's neighbors too
			for (std::size_t k = 0; k < (*(*map).allContinents[i]).subCountries[j]->adjacentCountries.size(); k++)
			{
				output << "," << (*(*map).allContinents[i]).subCountries[j]->adjacentCountries[k]->getName();
			}

			output << endl;
		}

		output << endl;
	}
}

void NewSaveLoadAdapter::save(Map * map)
{
	cout << "\n\nSAVING MAP TO FILE\n" << "----------------------------\n";

	ofstream output((*map).getName() + "-edited.altmap");
	output << "--MAP--" << endl;
	output << "author=" << (*map).getAuthor() << endl;
	output << "image=" << (*map).getImage() << endl;
	output << "wrap=" << (*map).getWrap() << endl;
	output << "scroll=" << (*map).getScroll() << endl;
	output << "warn=" << (*map).getWarn() << endl;


	for (std::size_t i = 0; i < map->allContinents.size(); i++)
	{
		// List each continent, name and value
		output << endl << "--CONTINENT--" << endl;
		output << "name=" << (*(*map).allContinents[i]).getName() << endl;
		output << "value=" << (*(*map).allContinents[i]).getBonusValue() << endl;

		// Follow by listing all of that continent's territories
		for (std::size_t j = 0; j < (*(*map).allContinents[i]).subCountries.size(); j++)
		{
			output << (*(*map).allContinents[i]).subCountries[j]->getName() << "," << (*(*map).allContinents[i]).subCountries[j]->getX() << "," << (*(*map).allContinents[i]).subCountries[j]->getY();

			// List that country's neighbors too
			for (std::size_t k = 0; k < (*(*map).allContinents[i]).subCountries[j]->adjacentCountries.size(); k++)
			{
				output << "," << (*(*map).allContinents[i]).subCountries[j]->adjacentCountries[k]->getName();
			}

			output << endl;
		}
	}

	output.close();
}