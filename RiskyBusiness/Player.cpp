#include "Player.h"

Player::Player() {

}

Player::Player(string playerName) {
	this->playerName = playerName;
}

Player::~Player() {

}

bool Player::iOwnCountry(Country *country) {
	if (country->owner == this)
		return true; 

	return false; 
}

bool Player::iOwnContinent(Continent *continent) {
	for (int i = 0; i < continent->subCountries.size(); i++)
	{
		// If any of the sub countries have a different owner, break and return false
		if (continent->subCountries[i]->owner != this)
			return false; 
	}
	
	return true; 
}

int Player::getArmyCountByCountry(Country* country) {
	return country->getArmyCount(); 
}

int Player::getContinentBonus(Map * map) {
	
	int bonus = 0; 
	
	for (int i = 0; i < map->allContinents.size(); i++)
	{
		if (iOwnContinent(map->allContinents[i]))
			bonus += map->allContinents[i]->getBonusValue(); 
	}

	return bonus; 
}

bool Player::checkCountryHasNeighborsUOwn(Country* country)
{
	for (int i = 0; i < country->adjacentCountries.size(); i++)
	{
		if (country->adjacentCountries[i]->owner == this)
			return true; 
	}
	return false; 
}