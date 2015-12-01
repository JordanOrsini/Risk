#include "Player.h"

Player::Player() {
	this->logSubject = new Subject();

}

Player::Player(string playerName) {
	this->playerName = playerName;
	this->logSubject = new Subject();
}

Player::~Player() {
	delete this->logSubject;
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

void Player::getCard(Card* card)
{
	hand.push_back(card); 
}

void Player::disCard(int index)
{
	index--; 
	hand.erase(hand.begin() + index); // Erases hand[index+1]
}

void Player::attack()
{
	string enterBattle;
	string attackFrom;
	bool battleOwnsCountry = false;
	bool battleHasEnoughTroops = false;
	int battleCountryIndex = 0;
	int attackTargetIndex = 0;
	string attackTo;
	bool attackTargetValid1 = false;
	bool attackTargetValid2 = true;
	int attackAmount = 0;
	int defendAmount = 0;
	bool countryTakeover = false;
	int attackerTroopsLost = 0;
	int countryIndexToErase = 0;

	while (true)
	{
		cout << "Player \"";
		handle->print(player->getPlayerName(), player->getColor());
		cout << "\", enter attack phase? (y/n) ";

		if (cin.peek() == '\n')
		{
			cin.ignore(1, '\n');
		}
		getline(cin, enterBattle);

		if (enterBattle == "y" || enterBattle == "Y")
		{
			cout << "\nPlayer \"";
			handle->print(player->getPlayerName(), player->getColor());
			cout << "\", select country to attack from: (country must have more than one army)" << endl << endl;

			if (cin.peek() == '\n')
			{
				cin.ignore(1, '\n');
			}
			getline(cin, attackFrom);



			//Check 1 (player owns attackFrom)
			for (int i = 0; i < player->countriesOwned.size(); i++)
			{
				if (attackFrom == player->countriesOwned.at(i)->getName())
				{
					battleOwnsCountry = true;
					battleCountryIndex = i;
				}
			}

			//Check 2 (player has more than 1 army on attackFrom)
			if (player->countriesOwned.at(battleCountryIndex)->getArmyCount() > 1)
			{
				battleHasEnoughTroops = true;
			}

			//If both checks are passed.
			if (battleOwnsCountry && battleHasEnoughTroops)
			{
				cout << "\nPlayer \"";
				handle->print(player->getPlayerName(), player->getColor());
				cout << "\", select country to attack: (country must be adjacent to attacking country)" << endl << endl;

				if (cin.peek() == '\n')
				{
					cin.ignore(1, '\n');
				}
				getline(cin, attackTo);

				//Check 1 to see if attackTo is adjacent to attackFrom
				for (int i = 0; i < player->countriesOwned.at(battleCountryIndex)->adjacentCountries.size(); i++)
				{
					//If attack target selected is adjacent to attacking country (attack is valid)
					if (attackTo == player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(i)->getName())
					{
						attackTargetValid1 = true;
						attackTargetIndex = i;
					}
				}

				//Check 2 to make sure attacking player does not own attackTo
				for (int i = 0; i < player->countriesOwned.size(); i++)
				{
					if (attackTo == player->countriesOwned.at(i)->getName())
					{
						attackTargetValid2 = false;
					}
				}

				if (attackTargetValid1 && attackTargetValid2)
				{
					cout << "\nPlayer \"";
					handle->print(player->getPlayerName(), player->getColor());
					cout << "\", select 1-3 armies to attack with: (" << player->countriesOwned.at(battleCountryIndex)->getArmyCount() << " armies, " << player->countriesOwned.at(battleCountryIndex)->getArmyCount() - 1 << " available to attack)" << endl << endl;
					cin >> attackAmount;

					//Error message if invalid armies is input for attacker(must be an integer 1-3, provided player has enough armies available(must leave at least one army behind))
					while (attackAmount > player->countriesOwned.at(battleCountryIndex)->getArmyCount() - 1 || attackAmount < 1 || attackAmount > 3)
					{
						cout << "\nInvalid input, must select a value between 1-3: (" << player->countriesOwned.at(battleCountryIndex)->getArmyCount() - 1 << " available armies to attack)" << endl << endl;
						cin >> attackAmount;
					}

					cout << "\nPlayer \"";
					handle->print(player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->owner->getPlayerName(), player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->owner->getColor());
					cout << "\", select 1-2 armies to defend with: (" << player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount() << " armies available)" << endl << endl;
					cin >> defendAmount;

					//Error message of invalid armies is input for defender (must be an integer 1-2, provided player has enough armies available)
					while (defendAmount < 1 || defendAmount > 2 || defendAmount > player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount())
					{
						cout << "\nInvalid input, must select a value betweeen 1-2: (" << player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount() << " available armies to defend)" << endl << endl;
						cin >> defendAmount;
					}


					//insert dice roll section here
					//
					//
					//
					//




					//if player successfully takes over country
					if (countryTakeover)
					{
						for (int i = 0; i < player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->owner->countriesOwned.size(); i++)
						{
							if (attackTo == player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->owner->countriesOwned.at(i)->getName())
							{
								countryIndexToErase = i;
							}
						}
					}
					//player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->owner->countriesOwned.erase()

				}













			}










		}
		else
		{
			break;
		}
	}

	// Whole function should be contained in while loop becuase you can attack as many times as you want

	// CHECK 1: Ask player if they want to attack
	//		-if no, break; 

	// CHECK 2: Can you even attack a country?
	//			- Must have country that has at least 2 armies adjacent to another player's country
	//			- Check should be a function that returns a boolean
	//		- If no, break; 


	// While (1)
	//	 - Player chooses country to attack from
	//	 - Choose number of armies (Max 3, min 1)
	//   - Player chooses country to attack
	//	 - Other player chooses number of defending armies (min 1, max 2)
	//	 - CHECK 3: Is this a valid choice?
	//	IF choice is valid, break; 

	// Actual attack! Roll dice for each player, result of armies, etc. 

	//Result: 
	//	- Did you win the territory? If yes, move all attacking troops
	//		- Did the attacked player lose the game? If yes get thier cards

	//Ask player if they want to continue battling
	// - If no, break; 

}

/**
*	Fortification phase. Will give user option to enter the phase.
*	Will ask user to select a country he owns.
*	Will ask user how many troops he would like to move. (Must leave at least 1 army on country.
*	Will ask user to select an adjacent country to complete the move.
*	Will decrement troops on initial country selected accordingly.
*	Will increment troops on adjacent country selected if owned by player accordingly.
*/







