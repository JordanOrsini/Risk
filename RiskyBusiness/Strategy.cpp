#include "Player.h"

void UserStrategy::attack(Player* player)
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

// This strategy will always attack if the player controls a country that has one adjacent enemy country
// with less armies than it has
void AggressiveStrategy::attack(Player* player)
{
	//loop until no more countries fit attack description
	while (1) {
		Country* attack = NULL; // Placeholders
		Country* defend = NULL; 

		// Find first country that fits description
		for (int i = 0; i < player->countriesOwned.size(); i++)
		{
			attack = player->countriesOwned[i];
			for (int j = 0; j < player->countriesOwned[i]->adjacentCountries.size(); j++) {
				//if (player->countriesOwned[i]->adjacentCountries[j]->getArmyCount() < attack->getArmyCount() && attack->getArmyCount > 1)
				//{
				//	defend = player->countriesOwned[i]->adjacentCountries[j];
				//	break; 
				//}
			}
			if (defend != NULL)
				break; 
		}

		if (defend != NULL) {
			// Attack that country 
			handle->print("Attacking " + defend->getName() + " from " + attack->getName() + "\n", player->getColor());

			// INCOMPLETE
		}
		else
			break; // No countries to attack, end turn
	}

	handle->print("No more countries to attack. End of attack phase", player->getColor());

}

// This strategy will never attack unless the player controls a country for which
// all adjacent enemy countries have significantly less armies ie. half or less
void DefensiveStrategy::attack(Player* player)
{
	bool result; 

	//loop until no more countries fit attack description
	while (1) {
		Country* attack = NULL; // Placeholders
		Country* defend = NULL;
		Country* temp = NULL; 

		// Find first country that fits description
		for (int i = 0; i < player->countriesOwned.size(); i++)
		{
			result = true; 
			temp = player->countriesOwned[i];

			for (int j = 0; j < player->countriesOwned[i]->adjacentCountries.size(); j++) {
				if (player->countriesOwned[i]->adjacentCountries[j]->getArmyCount() >= (int)(temp->getArmyCount() / 2))
					result = false; 
			}
			if (result = true)
			{
				attack = player->countriesOwned[i];
				break;
			}
		}

		if (attack != NULL) {
			// Always attack first adjacent country in the list
			defend = attack->adjacentCountries[0]; 
			handle->print("Attacking " + defend->getName() + " from " + attack->getName() + "\n", player->getColor());

			// INCOMPLETE
		}
		else
			break; // No countries to attack, end turn
	}

	handle->print("No more countries to attack. End of attack phase", player->getColor());

}

void RandomStrategy::attack(Player* player)
{
	//To do 
}