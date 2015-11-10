#include "MapView.h"

MapView::MapView()
{
	mapC.loadMapFromFile();
	this->board = new Board(1, 1, endX, endY);
	this->board->setNumCols(4); // 4 columns
	this->board->setNumRows(5); // 5 rows
	this->rowHeight = this->board->getRowHeight();
	this->colWidth = this->board->getColumnWidth();
}

void MapView::displayBoard() {
	vector<Country*> allCountries = mapC.getMap()->allCountries;
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
