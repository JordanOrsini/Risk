#include "MapView.h"

MapView::MapView(MapController* inputMap)
{
	mapC = inputMap;
	(*mapC).loadMapFromFile();

	this->board = new Board(1, 1, endX, endY);
	this->board->setNumCols(4); // 4 columns
	this->board->setNumRows(5); // 5 rows
	this->rowHeight = this->board->getRowHeight();
	this->colWidth = this->board->getColumnWidth();
}

void MapView::update() {
	this->board->clearBoard();
	this->displayBoard();
}

void MapView::displayBoard() {
	vector<Country*> allCountries = (*mapC).getMap()->allCountries;
	int k = 0;
	int offset = 0;
	int numOfFillableColumns = 3;
	while (k < allCountries.size()) {
		this->board->drawBoard();
		this->board->gotoXYPrint(4, ((rowHeight) / 2) + this->board->getStartY(), "Country");
		this->board->gotoXYPrint(4, ((rowHeight) / 2) + (rowHeight) + this->board->getStartY(), "Continent");
		this->board->gotoXYPrint(4, ((rowHeight) / 2) + 2 * (rowHeight) + this->board->getStartY(), "Owner");
		this->board->gotoXYPrint(4, ((rowHeight) / 2) + 3 * (rowHeight) + this->board->getStartY(), "Armies");
		this->board->gotoXYPrint(4, ((rowHeight) / 2) + 4 * (rowHeight) + this->board->getStartY(), "Neighbors");

		if (offset + numOfFillableColumns >= allCountries.size()) {
			numOfFillableColumns = allCountries.size() - offset;
		}
		int x, y;
		string country;
		offset = k;
		// print countries
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((colWidth) + i * (colWidth) + 3);
			y = (((rowHeight) / 2) - 2) + this->board->getStartY();
			country = allCountries.at(offset)->getName();
			int test = colWidth;

			if (country.length() >= (colWidth)) {
				country = country.substr(0, (colWidth) - 3) + "."; // Northwest territories will become Northwest Terr.
			}
			offset++;
			this->board->gotoXYPrint(x, y, country);
		}
		offset = k;
		string continent = "";
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((colWidth) + i * (colWidth) + 3);
			y = (((rowHeight) / 2) - 2) + (rowHeight) + this->board->getStartY();
			continent = allCountries.at(offset)->getParentContinentName();
			if (continent.length() >= (colWidth)) {
				continent = continent.substr(0, (colWidth) - 3) + ".";
			}
			offset++;
			this->board->gotoXYPrint(x, y, continent);
		}

		// print country owner
		string owner = "";
		offset = k;
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((colWidth) + i * (colWidth) + 3);
			y = (((rowHeight) / 2) - 2) + 2 * (rowHeight) + this->board->getStartY();
			//owner = allCountries.at(i)->owner->getPlayerName();
			owner = "N/A";
			if (owner.length() >= (colWidth)) {
				owner = owner.substr(0, (colWidth) - 3) + ".";
			}
			offset++;
			this->board->gotoXYPrint(x, y, owner);
		}

		//print num of armies on country
		int armies;
		offset = k;
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((colWidth) + i * (colWidth) + 3);
			y = (((rowHeight) / 2) - 2) + 3 * (rowHeight) + this->board->getStartY();
			armies = allCountries.at(offset)->getArmyCount();
			offset++;
			this->board->gotoXYPrint(x, y, to_string(armies));
		}

		vector<Country*> adjCountries;
		offset = k;
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((colWidth) + i * (colWidth) + 3);
			y = (((rowHeight) / 2) - 2) + 4 * (rowHeight) + this->board->getStartY();
			adjCountries = allCountries.at(offset)->adjacentCountries;
			for (int j = 0; j < adjCountries.size(); j++) {
				country = adjCountries.at(j)->getName();
				if (country.length() >= (colWidth)) {
					country = country.substr(0, (colWidth) - 4) + "."; // Northwest territories will become Northwest Terr.
				}
				this->board->gotoXYPrint(x, y, country);
				++y;
			}
			offset++;
		}

		k += 3;
		
		this->board->gotoXYPrint(0, this->board->getHeight() + this->board->getStartY() + 2, "");	
	}
}

MapView::~MapView()
{
	delete this->board;
	board = nullptr;
}

void MapView::editMap()
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
			cin >> continentName;
			cout << "Enter the bonus value of owning the continent: ";
			cin >> value;

			// Create continent and get MapController to add it to the map
			mapC->createContinent(continentName, atoi(value.c_str())); 

			cout << endl << continentName << " was added to the map." << endl << endl;
		}

		// CREATE A NEW COUNTRY
		if (userInput == "2")
		{
			
			while (1)
			{
				cout << "Enter the name of the continent to add a new country to: ";
				cin >> continentName;

				cout << "Enter the name of the new country: ";
				cin >> name;

				cout << "Enter an x-axis value: ";
				cin >> x;

				cout << "Enter a y-axis value: ";
				cin >> y;

				functionResult = (*mapC).addCountryToContinent(name, atoi(x.c_str()), atoi(y.c_str()), continentName); 
				if (functionResult)
					break;
				else
					cout << "Error: The continent does not exist\n"; 
			}

			cout << endl << name << " was added to the map." << endl << endl;
		}

		// ADD NEIGHBORS TO A COUNTRY
		if (userInput == "3")
		{	
			while (1)
			{
				cout << "Enter the name of the country you wish to add neighbors: ";
				cin >> name;

				cout << "Enter the name of the neighbor country";
				cin >> str;

				functionResult = mapC->addNeighborToCountry(name, str); 
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
			cout << "Ending editing session. Test map again for correctness...\n";
			break;
		}

	}
}