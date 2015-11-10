#include "MapView.h"

MapView::MapView()
{
	mapC.loadMapFromFile();
	board->setNumCols(3);
	board->setNumRows(4);

}

void MapView::displayBoard() {
	board->setRowHeight(0, height / 5);
	board->setRowHeight(1, height / 5);
	board->setRowHeight(2, height / 5);
	board->setRowHeight(3, height / 5);
	board->setRowHeight(4, height / 5);

	board->setColWidth(0, width / 4);
	board->setColWidth(1, width / 4);
	board->setColWidth(2, width / 4);
	board->setColWidth(3, width / 4);

	//board->clearBoard();
	

	vector<Country*> allCountries = mapC.getMap()->allCountries;
	int k = 0;
	int offset = 0;
	int numOfFillableColumns = 3;
	while (k < allCountries.size()) {
		board->drawBoard();
		board->gotoXYPrint(4, ((height / 5) / 2) + board->getStartY(), "Country");
		board->gotoXYPrint(4, ((height / 5) / 2) + (height / 5) + board->getStartY(), "Continent");
		board->gotoXYPrint(4, ((height / 5) / 2) + 2 * (height / 5) + board->getStartY(), "Owner");
		board->gotoXYPrint(4, ((height / 5) / 2) + 3 * (height / 5) + board->getStartY(), "Armies");
		board->gotoXYPrint(4, ((height / 5) / 2) + 4 * (height / 5) + board->getStartY(), "Neighbors");

		if (offset + 3 >= allCountries.size()) {
			numOfFillableColumns = allCountries.size() - offset;
		}
		int x, y;
		string country;
		offset = k;
		// print countries
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((width / 4) + i * (width / 4) + 3);
			y = (((height / 5) / 2) - 2) + board->getStartY();
			country = allCountries.at(offset)->getName();
			int test = width / 4;

			if (country.length() >= (width / 4)) {
				country = country.substr(0, (width / 4) - 3) + "."; // Northwest territories will become Northwest Terr.
			}
			offset++;
			board->gotoXYPrint(x, y, country);
		}
		offset = k;
		string continent = "";
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((width / 4) + i * (width / 4) + 3);
			y = (((height / 5) / 2) - 2) + (height / 5) + board->getStartY();
			continent = allCountries.at(offset)->getParentContinentName();
			if (continent.length() >= (width / 4)) {
				continent = continent.substr(0, (width / 4) - 3) + ".";
			}
			offset++;
			board->gotoXYPrint(x, y, continent);
		}

		// print country owner
		string owner = "";
		offset = k;
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((width / 4) + i * (width / 4) + 3);
			y = (((height / 5) / 2) - 2) + 2 * (height / 5) + board->getStartY();
			//owner = allCountries.at(i)->owner->getPlayerName();
			owner = "N/A";
			if (owner.length() >= (width / 4)) {
				owner = owner.substr(0, (width / 4) - 3) + ".";
			}
			offset++;
			board->gotoXYPrint(x, y, owner);
		}

		//print num of armies on country
		int armies;
		offset = k;
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((width / 4) + i * (width / 4) + 3);
			y = (((height / 5) / 2) - 2) + 3 * (height / 5) + board->getStartY();
			armies = allCountries.at(offset)->getArmyCount();
			offset++;
			board->gotoXYPrint(x, y, to_string(armies));
		}

		vector<Country*> adjCountries;
		offset = k;
		for (int i = 0; i < numOfFillableColumns; i++) {
			x = ((width / 4) + i * (width / 4) + 3);
			y = (((height / 5) / 2) - 2) + 4 * (height / 5) + board->getStartY();
			adjCountries = allCountries.at(offset)->adjacentCountries;
			for (int j = 0; j < adjCountries.size(); j++) {
				country = adjCountries.at(j)->getName();
				if (country.length() >= (width / 4)) {
					country = country.substr(0, (width / 4) - 4) + "."; // Northwest territories will become Northwest Terr.
				}
				board->gotoXYPrint(x, y, country);
				++y;
			}
			offset++;
		}

		k += 3;
		
		board->gotoXYPrint(0, height + board->getStartY() + 2, "");
		
	}
}

MapView::~MapView()
{
	delete this->board;
	board = nullptr;
}
