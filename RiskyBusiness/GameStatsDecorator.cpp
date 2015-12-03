#include "GameStatsDecorator.h"

//-----------------------------------

GameStatsDecorator::GameStatsDecorator(IGameStats* stats) : IGameStats(stats->getPlayer())
{
	this->stats = stats;
}

//-----------------------------------

void GameStats::displayStats() {
	cout << endl;
	cout << "Number of countries you own: " << this->getNumOfCountries() << endl;
	cout << "Total number of Troops under your command: " << this->getTotalArmies() << endl;
	cout << "Total number of cards in your hand: " << this->getTotalCards() << endl;
}

int GameStats::getNumOfCountries() {
	return this->getPlayer()->countriesOwned.size();
}

int GameStats::getTotalCards() {
	return this->getPlayer()->hand.size();
}

int GameStats::getTotalArmies(){
	vector<Country*> countries = this->getPlayer()->countriesOwned;
	int totalArmies = 0;
	for (int i = 0; i < countries.size(); i++) {
		totalArmies += countries.at(i)->getArmyCount();
	}

	return totalArmies;
}

//-----------------------------------

void GameWorldPercentage::displayStats() {
	cout.precision(2);
	cout << "Percentage of the world you own: " << this->getWorldOwnership() << "%" << endl;
}

double GameWorldPercentage::getWorldOwnership() {
	double ownership = 0.0;
	ownership = (this->getPlayer()->countriesOwned.size() / this->getPlayer()->getMap()->allCountries.size()) * 100;
	return ownership;
}

//-----------------------------------

void GameBattles::displayStats() {
	cout.precision(2);
	cout << "Number of battles won: " << this->getPlayer()->getNumOfBattlesWon() << endl;
}
