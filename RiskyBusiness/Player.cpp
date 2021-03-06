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

	setLogMessage(getPlayerName() + " gets " + to_string(bonus) + " more armies due to the continent bonus."); 
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

void Player::getCard()
{	
	Card * card = deck.getCard(); 
	hand.push_back(card); 
	setLogMessage(getPlayerName() + " recieved an " + card->getTypeName() + " victory card"); 
}

void Player::disCard(int index)
{
	hand.erase(hand.begin() + index); // Erases hand[index+1]
}

void Player::receiveCards(vector<Card*> playerDefeatCards)
{
	for (int i = 0; i < playerDefeatCards.size(); i++)
	{
		hand.push_back(playerDefeatCards.at(i));
	}

}

void Player::takeOver(Country* attack, Country* defend, int atkAMT, int atkLOST)
{
	// Pointer Placeholders
	Player* defender = defend->owner; 
	Player* attacker = attack->owner; 

	// STEP 1: ERASE DEFENDING COUNTRY FROM DEFENDER LIST
	int defendIndex; 

	for (int i = 0; i < defender->countriesOwned.size(); i++)
	{
		if (defend->getName() == defender->countriesOwned.at(i)->getName())
		{
			defender->countriesOwned.erase(defender->countriesOwned.begin() + i); 
			break; 
		}
	}

	// STEP 2: ADD NEW COUNTRY TO ATTACKERS COUNTRY LIST
	attacker->countriesOwned.push_back(defend);

	//STEP 3: SET NEW OWNER
	int countryTakeOverMoveAmount = 0;
	defend->owner = attacker;

	cout << "Player \"";
	handle->print(attacker->getPlayerName(), attacker->getColor());
	cout << "\", how many armies would you like to move from \"";
	handle->print(attack->getName(), attacker->getColor());
	cout << "\" to your new country \"";
	handle->print(defend->getName(), attacker->getColor());
	cout << "\"? (" << attack->getArmyCount() - 1 << " armies available to move. Must move at least " << atkAMT - atkLOST << ")" << endl << endl;
	cin >> countryTakeOverMoveAmount;

	while (countryTakeOverMoveAmount < (atkAMT - atkLOST) || countryTakeOverMoveAmount > attack->getArmyCount() - 1)
	{
		this->setLogMessage("Invalid input! Enter amount between " + to_string(atkAMT - atkLOST) + " and " + to_string(attack->getArmyCount() - 1) + ":");
		cin >> countryTakeOverMoveAmount;
	}
	
	this->setLogMessage(getPlayerName() + " took over " + defend->getName() + " and moved " + to_string(countryTakeOverMoveAmount) + " armies from " + attack->getName()); 

	//STEP 4: ADD SELECTED TROOPS TO NEW COUNTRY
	defend->setArmyCount(countryTakeOverMoveAmount);
	
	//STEP 5: REMOVE MOVED TROOPS FROM ATTACKING COUNTRY
	attack->setArmyCount(attack->getArmyCount() - countryTakeOverMoveAmount);
	
	//STEP 6: IF DEFENDING PLAYER IS DEAD --> TRANSFER ALL CARDS TO ATTACKING PLAYER, REMOVE DEFENDING PLAYER FROM GAME LOOP, CHECK IF THE GAME IS WON (1 PLAYER REMAINING) 
	if (defender->countriesOwned.size() == 0)
	{
		attacker->receiveCards(defender->hand);
		defender->alive = false;
		defender->setLogMessage(defender->getPlayerName() + " DIED"); 
	}
	
	this->setLogMessage( "Country takeover successful!");
	
	this->numOfBattlesWon++;
}


void Player::setLogMessage(string logMessage) {
	this->logMessage = logMessage;
	this->notify();
}
