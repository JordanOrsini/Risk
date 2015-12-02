#include "Player.h"
using namespace std; 
using std::cout; 

vector<int> Strategy::rolldice(int attackAmount, int defendAmount, Player* attackingPlayer, Player* defendingPlayer)
{
	int attackerFirstBest = 0;
	int attackerSecondBest = 0;
	int defenderFirstBest = 0;
	int defenderSecondBest = 0;
	vector<int> diceRolls;
	vector<int> results(2, 0);	//stores the result of the battle. Index 0 stores the # troops the attacker lost. Index 1 stores the # troops the defender lost
								//initilizes 2 ints with the value 0

								//--------------------------------------------------------ATTACKER--------------------------------------------------------
	cout << "Player \"";
	handle->print(attackingPlayer->getPlayerName(), attackingPlayer->getColor());
	cout << "\", rolled:\n";

	for (int i = 0; i < attackAmount; i++)
	{
		diceRolls.push_back(rand() % 6 + 1);
		handle->print(to_string(diceRolls.at(i)), attackingPlayer->getColor());
		cout << endl;
	}

	sort(diceRolls.begin(), diceRolls.end()); //sorts the dice rolls from lowest to highest
	reverse(diceRolls.begin(), diceRolls.end()); //sorts the dice rolls from highest to lowest so as not to get out of bounds error

	if (attackAmount >= 2)
	{
		attackerFirstBest = diceRolls.at(0);
		attackerSecondBest = diceRolls.at(1);
	}

	else
		attackerFirstBest = diceRolls.at(0);

	diceRolls.clear();

	//--------------------------------------------------------DEFENDER--------------------------------------------------------
	cout << "\nPlayer \"";
	handle->print(defendingPlayer->getPlayerName(), defendingPlayer->getColor());
	cout << "\", rolled:\n";

	for (int i = 0; i < defendAmount; i++)
	{
		diceRolls.push_back(rand() % 6 + 1);
		handle->print(to_string(diceRolls.at(i)), defendingPlayer->getColor());
		cout << endl;
	}

	sort(diceRolls.begin(), diceRolls.end()); //sorts the dice rolls from lowest to highest
	reverse(diceRolls.begin(), diceRolls.end()); //sorts the dice rolls from highest to lowest so as not to get out of bounds error

	if (attackAmount == 2)
	{
		defenderFirstBest = diceRolls.at(0);
		defenderSecondBest = diceRolls.at(1);
	}

	else
		defenderFirstBest = diceRolls.at(0);


	if (attackerFirstBest > defenderFirstBest)
	{
		results.at(1) += 1; //defender loses 1
		cout << "Player \"";
		handle->print(defendingPlayer->getPlayerName(), defendingPlayer->getColor());
		cout << "\", lost 1 army!\n";
	}
	else
	{
		results.at(0) += 1; //attacker loses 1
		cout << "Player \"";
		handle->print(attackingPlayer->getPlayerName(), attackingPlayer->getColor());
		cout << "\", lost 1 army!\n";
	}

	if (defendAmount == 2)
	{
		if (attackerSecondBest > defenderSecondBest)
		{
			results.at(1) += 1; //defender loses 1
			cout << "Player \"";
			handle->print(defendingPlayer->getPlayerName(), defendingPlayer->getColor());
			cout << "\", lost 1 army!\n";
		}
		else
		{
			results.at(0) += 1; //attacker loses 1
			cout << "Player \"";
			handle->print(attackingPlayer->getPlayerName(), attackingPlayer->getColor());
			cout << "\", lost 1 army!\n";
		}

		cout << endl;
	}

	return results;
}

/*
void UserStrategy::attack(Player* player)
{
	Deck* myDeck = new Deck(); //maybe move initialization of this (but where???)

	Player* defendingPlayer;

	bool countryTakeover;

	while (true)
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
		countryTakeover = false;
		int attackerTroopsLost = 0;
		int defenderTroopsLost = 0;
		int countryIndexToErase = 0;
		int countryTakeOverMoveAmount = 0;
		
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

					defendingPlayer = player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->owner;


					//insert dice roll section here
					//
					//
					//
					//

					//need method to decrement attacker troops lost from battle
					player->countriesOwned.at(battleCountryIndex)->setArmyCount(player->countriesOwned.at(battleCountryIndex)->getArmyCount() - attackerTroopsLost);
					
					
					//need method to decrement defender troops lost from battle
					player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->setArmyCount(player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount() - defenderTroopsLost);
					
					//checks to see if country is taken over by the attack
					if (player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount() == 0)
					{
						countryTakeover = true;
					}

					//if player successfully takes over country
					if (countryTakeover) // set to true if country was taken over (no more defenders remaining)
					{
						for (int i = 0; i < defendingPlayer->countriesOwned.size(); i++)
						{
							if (attackTo == defendingPlayer->countriesOwned.at(i)->getName())
							{
								countryIndexToErase = i;
							}
						}
						//erases country from defending player's countriesOwned vector
						defendingPlayer->countriesOwned.erase(defendingPlayer->countriesOwned.begin()+countryIndexToErase);
					
						//adds country to attacking player's countriesOwned vector
						player->countriesOwned.push_back(player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex));

						//changes owner of country to be the attacking player
						player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->owner = player;
						
						cout << "Player \"";
						handle->print(player->getPlayerName(), player->getColor());
						cout << "\", how many armies would you like to move to your new country \"" << player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getName() << "\"? (" << player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount()-1 << " armies available to move. Must move at least " << attackAmount - attackerTroopsLost << ")" << endl << endl;

						cin >> countryTakeOverMoveAmount;

						while (countryTakeOverMoveAmount < (attackAmount - attackerTroopsLost) || countryTakeOverMoveAmount > player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount() - 1)
						{
							cout << "Invalid input! Enter amount between " << attackAmount - attackerTroopsLost << " and " << player->countriesOwned.at(battleCountryIndex)->adjacentCountries.at(attackTargetIndex)->getArmyCount()-1 << ":" << endl << endl;
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
		else
		{
			break;
		}
	}

	//if at least one country was taken over by the player this turn a card is awarded to his hand.
	if (countryTakeover)
	{
		player->getCard(myDeck->getCard());
	}


	delete myDeck; //remove this line if myDeck initialisation location has changed.

	myDeck = NULL;//remove this line if myDeck initialisation location has changed.

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
*/

void UserStrategy::attack(Player* player)
{
	Player* defendingPlayer;

	// Pointers
	Country* attack;
	Country* defend;


	// User input
	string enterBattle;
	string attackFrom;
	string attackTo;
	int attackAmount;
	int defendAmount;

	// Internal variables
	int attackerTroopsLost;
	int defenderTroopsLost;
	bool countryTakeOver;
	bool alreadyHasCard = false; 
	vector<int> resultsOfBattle;

	while (1)
	{
		
		countryTakeOver = false;

		// Ask player if they want to enter attack phase
		cout << "Player \"";
		handle->print(player->getPlayerName(), player->getColor());
		cout << "\", enter attack phase? (y/n) ";

		if (cin.peek() == '\n')
		{
			cin.ignore(1, '\n');
		}
		getline(cin, enterBattle);

		if (enterBattle != "y" && enterBattle != "Y")
			break;

		cout << "\nPlayer \"";
		handle->print(player->getPlayerName(), player->getColor());

		// Only break out of this loop when we have a country to attack from and a country to attack
		while (1)
		{
			//Initialize
			attack = NULL;
			defend = NULL;

			// STEP 1: GET COUNTRY TO ATTACK FROM 
			while (1)
			{
				// Ask user
				cout << "\", select country to attack from: (country must have more than one army)" << endl << endl;
				if (cin.peek() == '\n')
				{
					cin.ignore(1, '\n');
				}
				std::getline(cin, attackFrom);

				//Check 1 (player owns attackFrom & the country has enough troops)
				for (int i = 0; i < player->countriesOwned.size(); i++)
				{
					if (attackFrom == player->countriesOwned.at(i)->getName())
					{
						attack = player->countriesOwned.at(i);
						break;
					}
				}

				//Check 2 (country has enough troops)
				if (attack == NULL || attack->getArmyCount() <= 1)
					cout << "Error: Either you do not own this country or the country does not have enough armies to attack\n";
				else
					break;
			}

			// STEP 2: GET A COUNTRY TO ATTACK
			// Ask user
			cout << "\nPlayer \"";
			handle->print(player->getPlayerName(), player->getColor());
			cout << "\", select country to attack: (country must be adjacent to attacking country)" << endl << endl;

			if (cin.peek() == '\n')
			{
				cin.ignore(1, '\n');
			}
			std::getline(cin, attackTo);

			//Check 1: see if attackTo is adjacent to attackFrom (if yes, set "defend")
			for (int i = 0; i < attack->adjacentCountries.size(); i++)
			{
				//If attack target selected is adjacent to attacking country (attack is valid) 
				if (attackTo == attack->adjacentCountries.at(i)->getName())
				{
					defend = attack->adjacentCountries.at(i);
					break;
				}
			}

			//Check 2:make sure defending country isn't owned by attacker
			if (defend == NULL || defend->owner->getPlayerName() == player->getPlayerName())
				cout << "Error: Either you own this country or this country is not adjacent to " + attack->getName() + "\nTry again.\n";
			else
				break;
		}
	

		// STEP 3: GET NUMBER OF DICE TO ATTACK WITH
		cout << "\nPlayer \"";
		handle->print(player->getPlayerName(), player->getColor());
		while (1)
		{

			cout << "\", select 1-3 armies to attack with: (You have " << attack->getArmyCount() << " total armies, " << attack->getArmyCount() - 1 << " available to attack)" << endl << endl;
			cin >> attackAmount;

			//Error message if invalid armies is input for attacker(must be an integer 1-3, provided player has enough armies available(must leave at least one army behind))
			if (attackAmount > attack->getArmyCount() - 1 || attackAmount < 1 || attackAmount > 3)
				cout << "\nInvalid input" << endl;
			else
				break;
		}



		// STEP 4: GET NUMBER OF DICE TO DEFEND WITH
		cout << "\nPlayer \"";
		handle->print(defend->owner->getPlayerName(), defend->owner->getColor());
		while (1)
		{

			cout << "\", select 1-2 armies to attack with: (You have " << defend->getArmyCount() << " total armies)" << endl << endl;
			cin >> defendAmount;

			//Error message if invalid armies is input for defender(must be an integer 1-2, provided player has enough armies available)
			if (defendAmount > defend->getArmyCount() - 1 || defendAmount < 1 || defendAmount > 2)
				cout << "\nInvalid input" << endl;
			else
				break;
		}

		//roll the dice
		resultsOfBattle.clear(); //initialize vector in case player wants to attack again
		resultsOfBattle = rolldice(attackAmount, defendAmount, player, defend->owner);
		attackerTroopsLost = resultsOfBattle.at(0);
		defenderTroopsLost = resultsOfBattle.at(1);

		//need method to decrement attacker troops lost from battle
		attack->setArmyCount(attack->getArmyCount() - attackerTroopsLost);

		//need method to decrement defender troops lost from battle
		defend->setArmyCount(defend->getArmyCount() - defenderTroopsLost);

		system("PAUSE");
		MC->getMap()->notify();

		//checks to see if country is taken over by the attack
		if (defend->getArmyCount() == 0)
		{
			player->takeOver(attack, defend, attackAmount, attackerTroopsLost);
			player->getCard();
		}

			if (alreadyHasCard == false)
			{
				player->getCard();
				alreadyHasCard = true; 
			}	
		}
	}



// This strategy will always attack if the player controls a country that has one adjacent enemy country
// with less armies than it has
void AggressiveStrategy::attack(Player* player)
{
	// Placeholders
	Country* attack; 
	Country* defend;
	int attackAmount = 0; 
	int defendAmount = 0; 
	int attackerTroopsLost = 0;
	int defenderTroopsLost = 0; 
	bool alreadyHasCard = false;


	//loop until no more countries fit attack description
	while (1) {
		
		// Initialize
		attack = NULL; 
		defend = NULL; 

		// STEP 1: FIND FIRST COUNTRIES THAT FITS ATTACK DESCRIPTION (ATTACKER AND DEFENDER) 
		for (int i = 0; i < player->countriesOwned.size(); i++)
		{
			attack = player->countriesOwned[i];
			for (int j = 0; j < player->countriesOwned[i]->adjacentCountries.size(); j++) {
				if (player->countriesOwned[i]->adjacentCountries[j]->getArmyCount() < attack->getArmyCount() && attack->getArmyCount() >= 2)
				{
					defend = player->countriesOwned[i]->adjacentCountries[j]; // Found an adjacent country with less armies
					break; 
				}
			}
			if (defend != NULL)
				break; 
		}

		// STEP 2: IF WE HAVE A COUNTRY TO ATTACK FROM AND A COUNTRY TO ATTACK, THEN ATTACK
		if (defend != NULL) {
			handle->print("Attacking " + defend->getName() + " from " + attack->getName() + "\n", player->getColor());
			
			// STEP 2.1: Get attacker army count (Attacker will always use highest number of dice available)
			attackAmount = attack->getArmyCount() - 1; 
			if (attackAmount > 3)
				attackAmount = 3; 
			cout << "\nPlayer \"";
			cout << attack->owner->getPlayerName() << " chooses to attack with " << attackAmount << " armies.";
			// STEP 2.2: Get defender army count
			cout << "\nPlayer \"";
			handle->print(defend->owner->getPlayerName(), defend->owner->getColor());
			while (1)
			{

				cout << "\", select 1-2 armies to attack with: (You have " << defend->getArmyCount() << " total armies)" << endl << endl;
				cin >> defendAmount;

				//Error message if invalid armies is input for defender(must be an integer 1-2, provided player has enough armies available)
				if (defendAmount > defend->getArmyCount() - 1 || defendAmount < 1 || defendAmount > 2)
					cout << "\nInvalid input" << endl;
				else
					break;
			}
			
			// STEP 2.3: Attack with dice roll
			attackerTroopsLost = 0;		//TEMPORARY
			defenderTroopsLost = 0;		//TEMPORARY
			
			attack->setArmyCount(attack->getArmyCount() - attackerTroopsLost);  // decrement troops
			defend->setArmyCount(defend->getArmyCount() - defenderTroopsLost);  // decrement troops

			// STEP 2.4: If country has no more troops, take it over
			if (defend->getArmyCount() == 0)
			{
				player->takeOver(attack, defend, attackAmount, attackerTroopsLost);

				if (alreadyHasCard == false)
				{
					player->getCard();
					alreadyHasCard = true;
				}
			}
		}
		else
			break; // NO MORE COUNTRIES TO ATTACK
	}

	handle->print("No more countries to attack. End of attack phase", player->getColor());

}

// This strategy will never attack unless the player controls a country for which
// all adjacent enemy countries have significantly less armies ie. half or less
void DefensiveStrategy::attack(Player* player)
{
	// Placeholders
	Country* attack;
	Country* defend;
	Country* temp; 
	int attackAmount = 0;
	int defendAmount = 0;
	int attackerTroopsLost = 0;
	int defenderTroopsLost = 0;
	bool alreadyHasCard = false;
	bool result; 

	//loop until no more countries fit attack description
	while (1) {
		attack = NULL; // Placeholders
		defend = NULL;
		temp = NULL; 

		// STEP 1: FIND FIRST COUNTRY THAT FITS ATTACK DESCRIPTION (ATTACKER) 
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
			// STEP 2: ALWAYS ATTACK FIRST COUNTRY IN ADJACENT LIST (ALL HAVE 1/2 THE ARMIES OR LESS)
			defend = attack->adjacentCountries[0]; 
			handle->print("Attacking " + defend->getName() + " from " + attack->getName() + "\n", player->getColor());

			// STEP 2.1: Get attacker army count (Attacker will always use highest number of dice available)
			attackAmount = attack->getArmyCount() - 1;
			if (attackAmount > 3)
				attackAmount = 3;
			cout << "\nPlayer \"";
			cout << attack->owner->getPlayerName() << " chooses to attack with " << attackAmount << " armies.";

			// STEP 2.2: Get defender army count
			cout << "\nPlayer \"";
			handle->print(defend->owner->getPlayerName(), defend->owner->getColor());
			while (1)
			{

				cout << "\", select 1-2 armies to attack with: (You have " << defend->getArmyCount() << " total armies)" << endl << endl;
				cin >> defendAmount;

				//Error message if invalid armies is input for defender(must be an integer 1-2, provided player has enough armies available)
				if (defendAmount > defend->getArmyCount() - 1 || defendAmount < 1 || defendAmount > 2)
					cout << "\nInvalid input" << endl;
				else
					break;
			}

			// STEP 2.3: Attack with dice roll
			attackerTroopsLost = 0;		//TEMPORARY
			defenderTroopsLost = 0;		//TEMPORARY

			attack->setArmyCount(attack->getArmyCount() - attackerTroopsLost);  // decrement troops
			defend->setArmyCount(defend->getArmyCount() - defenderTroopsLost);  // decrement troops

			// STEP 2.4: If country has no more troops, take it over
			if (defend->getArmyCount() == 0)
			{
				player->takeOver(attack, defend, attackAmount, attackerTroopsLost);

				if (alreadyHasCard == false)
				{
					player->getCard();
					alreadyHasCard = true;
				}
			}
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