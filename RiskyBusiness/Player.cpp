#include "Player.h"

Player::Player() {
}

Player::Player(string playerName) {
	this->playerName = playerName;
	this->setStrategy(new UserStrategy());
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

void Player::getCard()
{
	hand.push_back(deck.getCard()); 
}

void Player::disCard(int index)
{
	index--; 
	hand.erase(hand.begin() + index); // Erases hand[index+1]
}

void Player::receiveCards(vector<Card*> playerDefeatCards)
{
	for (int i = 0; i < playerDefeatCards.size(); i++)
	{
		hand.push_back(playerDefeatCards.at(i));
	}

}

void Player::takeOver(Country* attack, Country* defend)
{
	// Pointer Placeholders
	Player* defender = defend->owner; 
	Player* attacker = attack->owner; 

	// STEP 1: ERASE DEFENDING COUNTRY FROM DEFENDER LIST
	int defendIndex; 

	for (int i = 0; i < defender->countriesOwned.size(); i++)
	{
		if (defend->getName() == defender->countriesOwned[i]->getName())
		{
			defender->countriesOwned.erase(defender->countriesOwned.begin() + i); 
			break; 
		}
	}

	// STEP 2: SET NEW OWNER



	/*
	for (int i = 0; i < defendingPlayer->countriesOwned.size(); i++)
	{
		if (attackTo == defendingPlayer->countriesOwned.at(i)->getName())
		{
			countryIndexToErase = i;
		}
	}
	//erases country from defending player's countriesOwned vector
	defendingPlayer->countriesOwned.erase(defendingPlayer->countriesOwned.begin() + countryIndexToErase);

	//adds country to attacking player's countriesOwned vector
	player->countriesOwned.push_back(player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex));

	//changes owner of country to be the attacking player
	player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->owner = player;

	cout << "Player \"";
	handle->print(player->getPlayerName(), player->getColor());
	cout << "\", how many armies would you like to move to your new country \"" << player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getName() << "\"? (" << player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount() - 1 << " armies available to move. Must move at least " << attackAmount - attackerTroopsLost << ")" << endl << endl;

	cin >> countryTakeOverMoveAmount;

	while (countryTakeOverMoveAmount < (attackAmount - attackerTroopsLost) || countryTakeOverMoveAmount > player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount() - 1)
	{
		cout << "Invalid input! Enter amount between " << attackAmount - attackerTroopsLost << " and " << player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount() - 1 << ":" << endl << endl;
		cin >> countryTakeOverMoveAmount;
	}

	//adds armies from attacking country to newly aquired country
	player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->setArmyCount(countryTakeOverMoveAmount);

	//decrements armies from attacking country according to how many were chosen to be moved
	player->countriesOwned.at(battleCountryIndex)->setArmyCount(player->countriesOwned.at(battleCountryIndex)->getArmyCount() - countryTakeOverMoveAmount);

	//if country takeover results in defeat of defending player, transfer all cards
	if (defendingPlayer->countriesOwned.size() == 0)
	{
		player->receiveCards(defendingPlayer->hand);

	}

	cout << "Country takeover successful!" << endl << endl;
}

}

				else
					cout << "\nInvalid action!" << endl << endl;

			}

			else
				cout << "\nInvalid action!" << endl << endl;


	}

	//if at least one country was taken over by the player this turn a card is awarded to his hand.
	if (countryTakeover)
	{
		player->getCard(myDeck->getCard());
	}


	delete myDeck; //remove this line if myDeck initialisation location has changed.

	myDeck = NULL;//remove this line if myDeck initialisation location has changed.
	*/
	
}


void Player::setLogMessage(string logMessage) {
	this->logMessage = logMessage;
	this->notify();
}
