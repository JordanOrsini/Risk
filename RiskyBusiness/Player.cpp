#include "Player.h"

Player::Player() {

}

Player::Player(string playerName) {
	this->playerName = playerName;
}

Player::~Player() {

}

bool Player::iOwnCountry(Country *country) {
	return true; //change this
}

bool Player::iOwnContinent(Continent *continent) {
	return true; //change this
}

int Player::getArmyCountByCountry(Country* country) {
	return 0; //change this
}

int Player::getContinentBonus() {
	return 0; //change this
}

