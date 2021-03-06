#include "MapView.h"
#include <limits>

MapView::MapView()
{
	preGameMapCreation(); 
}

MapView::MapView(GameController* gameC)
{
	this->gameC = gameC;
	this->mapC = this->gameC->getMC();
	this->board = new Board(1, 1, endX, endY);
	this->mapC->loadMapFromFile();

	this->board->setNumCols(8); // 8 columns
	this->board->setNumRows(5); // 5 rows
	this->rowHeight = this->board->getRowHeight();
	this->colWidth = this->board->getColumnWidth();
	mapC->getMap()->attach(this);
	mapC->getMap()->notify();
}

void MapView::update() {
	this->board->clearBoard();
	this->displayBoard();
}

void MapView::displayBoard() {
	vector<Country*> countries;
	countries = mapC->getMap()->allCountries;
	
	int k = 0;
	int offset = 0;
	int numOfFillableColumns = 7;
	int color = 10; // green (default color)
	Player* player;
	while (k < countries.size()) {
		this->board->drawBoard();
		this->handle->gotoXYPrint(4, ((rowHeight) / 2) + this->board->getStartY(), "Country");
		this->handle->gotoXYPrint(4, ((rowHeight) / 2) + (rowHeight) + this->board->getStartY(), "Continent");
		this->handle->gotoXYPrint(4, ((rowHeight) / 2) + 2 * (rowHeight) + this->board->getStartY(), "Owner");
		this->handle->gotoXYPrint(4, ((rowHeight) / 2) + 3 * (rowHeight) + this->board->getStartY(), "Armies");
		this->handle->gotoXYPrint(4, ((rowHeight) / 2) + 4 * (rowHeight) + this->board->getStartY(), "Neighbors");

		if (offset + numOfFillableColumns >= countries.size()) {
			numOfFillableColumns = countries.size() - offset;
		}
		int x, y;
		string country;
		offset = k;
		// print countries
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = (colWidth + (i * colWidth) + 3);
			y = ((rowHeight / 2) - 2) + this->board->getStartY();
			country = countries.at(offset)->getName();
			player = countries.at(offset)->owner;
			if (player != nullptr)
				color = player->getColor();
			if (country.length() >= (colWidth - 3)) {
				country = country.substr(0, colWidth - 3) + "."; // Northwest territories will become Northwest Terr.
			}
			offset++;
			this->handle->gotoXYPrint(x, y, country, color);
			color = 10;
		}
		offset = k;
		string continent = "";
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = (colWidth + (i * colWidth) + 3);
			y = ((rowHeight / 2) - 2) + rowHeight + this->board->getStartY();
			continent = countries.at(offset)->getParentContinentName();
			if (continent.length() >= (colWidth)) {
				continent = continent.substr(0, colWidth - 3) + ".";
			}
			offset++;
			this->handle->gotoXYPrint(x, y, continent);
		}

		// print country owner
		string owner = "";
		offset = k;
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = (colWidth + (i * colWidth) + 3);
			y = ((rowHeight / 2) - 2) + (2 * rowHeight) + this->board->getStartY();
			player = countries.at(offset)->owner;
			if (player == nullptr) {
				owner = "N/A";
			}
			else {
				owner = player->getPlayerName();
				color = player->getColor();
			}
			if (owner.length() >= (colWidth)) {
				owner = owner.substr(0, (colWidth) - 3) + ".";
			}
			offset++;
			this->handle->gotoXYPrint(x, y, owner, color);
			int color = 10;

		}
		player = nullptr;

		//print num of armies on country
		int armies;
		offset = k;
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = (colWidth + (i * colWidth) + 3);
			y = ((rowHeight / 2) - 2) + (3 * rowHeight) + this->board->getStartY();
			armies = countries.at(offset)->getArmyCount();
			offset++;
			this->handle->gotoXYPrint(x, y, to_string(armies));
		}

		vector<Country*> adjCountries;
		offset = k;
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = colWidth + (i * (colWidth) + 3);
			y = ((rowHeight / 2) - 2) + (4 * rowHeight) + this->board->getStartY();
			adjCountries = countries.at(offset)->adjacentCountries;
			for (int j = 0; j < adjCountries.size(); j++) {
				country = adjCountries.at(j)->getName();
				player = adjCountries.at(j)->owner;
				if (player != nullptr)
					color = player->getColor();
				if (country.length() >= (colWidth - 3)) {
					country = country.substr(0, (colWidth) - 3) + "."; // Northwest territories will become Northwest Terr.
				}
				this->handle->gotoXYPrint(x, y, country, color);
				color = 10;
				++y;
			}
			offset++;
		}

		k += numOfFillableColumns;
		
		this->handle->gotoXYPrint(0, this->board->getHeight() + this->board->getStartY() + 2, "");	
	}
}

MapView::~MapView()
{
	delete this->board;
	board = nullptr;
}

void MapView::editMap(MapController* tempMC)
{
	string userInput;
	string name, continentName, x, y, value, str;
	bool functionResult; 

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
			if (cin.peek() == '\n') {
				cin.ignore(1, '\n');
			}
			getline(cin, continentName); 
			cout << "Enter the bonus value of owning the continent: ";
			cin >> value;

			// Create continent and get MapController to add it to the map
			functionResult = tempMC->createContinent(continentName, atoi(value.c_str())); 

			if (functionResult)
				cout << endl << continentName << " was added to the map." << endl << endl;
			else
				cout << "Error: the continent already exists\n"; 
		}

		// CREATE A NEW COUNTRY
		if (userInput == "2")
		{
			
			while (1)
			{
				cout << "Enter the name of the continent to add a new country to: ";
				if (cin.peek() == '\n') {
					cin.ignore(1, '\n');
				}
				getline(cin, continentName);

				cout << "Enter the name of the new country: ";
				if (cin.peek() == '\n') {
					cin.ignore(1, '\n');
				}
				getline(cin, name); 

				cout << "Enter an x-axis value: ";
				cin >> x;

				cout << "Enter a y-axis value: ";
				cin >> y;

				functionResult = (*tempMC).addCountryToContinent(name, atoi(x.c_str()), atoi(y.c_str()), continentName); 
				if (functionResult)
					break;
				else
					cout << "Error: The continent does not exist or the country already exists\n"; 
			}

			cout << endl << name << " was added to the map." << endl << endl;
		}

		// ADD NEIGHBORS TO A COUNTRY
		if (userInput == "3")
		{	
			while (1)
			{
				cout << "Enter the name of the country you wish to add neighbors: ";
				if (cin.peek() == '\n') {
					cin.ignore(1, '\n');
				}
				getline(cin, name); 

				cout << "Enter the name of the neighbor country: ";
				if (cin.peek() == '\n') {
					cin.ignore(1, '\n');
				}
				getline(cin, str); 

				functionResult = tempMC->addNeighborToCountry(name, str); 
				if (functionResult)
				{
					cout << "Added new neighbor.\n";
					break;
				}
				else
					cout << "Error: Either the stated country or it's neighbor does not exist. Try again.\n"; 
					
			}
		}

		// EXIT EDITING PHASE
		if (userInput == "4")
		{
			cout << "Ending editing session.\n";
			break;
		}

	}
}

void MapView::preGameMapCreation()
{
	char userInput; 
	bool mapIsCorrect = false; 

	// Note that this mapController is temporary, it is not used for gameplay rather it is used for the pregame option of creating/editing a map
	MapController* tempMC = new MapController(); 

	cout << "Before you start the game, would you like to create a map or edit one from a file?\n"; 
	cout << "Enter 'y' for yes, anything else for no:"; 
	cin >> userInput; 

	if (userInput == 'y') {
		cout << "\nWhat would you like to do:\n\t1) Create a map from scratch\n\t2) Edit a map from a file\n"; 
		
		while (1) {
			cout << "Enter 1 or 2: ";
			cin >> userInput;

			if (userInput == '1' || userInput == '2')
				break; 
		}
		

		if (userInput == '1')
		{
			string mapName;
			string author;

			cout << endl << "Enter your name: ";
			if (cin.peek() == '\n') {
				cin.ignore(1, '\n');
			}
			getline(cin, author); 
			cout << endl << "Enter the name of the new map: ";
			cin >> mapName;

			tempMC->createMap(author, mapName); 

			cout << endl << "Congratulations, you have created a new blank map.\nPlease note that an empty map cannot be saved as valid.\n\n";
		}

		if (userInput == '2')
		{
			tempMC->loadMapFromFile(); 
		}


		//Edit map, only save to file if it is correct
		while (1)
		{
			editMap(tempMC);

			cout << "Testing that the map satisfies these preconditions:\n\t- The map is a connected graph\n\t- The continents are connected subgraphs"; 
			mapIsCorrect = tempMC->testMap();
			
			if (mapIsCorrect)
			{
				cout << "The map meets the preconditions for correctness.\n";
				break; 
			}
			else
			{
				cout << "The map has errors. Would you like to continue editing? Note that only verified maps can be saved to file.\nEnter 'y' for yes, anything else for no: "; 
				cin >> userInput; 
				if (userInput != 'y')
					break; 
			}

		}

		if (mapIsCorrect)
		{
			cout << "Saving map to file...\n"; 
			tempMC->saveMapToFile(); 
		}

	}

	delete tempMC;
	tempMC = nullptr;
}