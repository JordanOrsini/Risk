#include "Player.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
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

	if (defendAmount == 2)
	{
		defenderFirstBest = diceRolls.at(0);
		defenderSecondBest = diceRolls.at(1);
	}

	else
		defenderFirstBest = diceRolls.at(0);


	if (attackerFirstBest > defenderFirstBest)
		results.at(1) += 1; //defender loses 1
	else
		results.at(0) += 1; //attacker loses 1

	if (defendAmount == 2 && attackAmount >= 2)
	{
		if (attackerSecondBest > defenderSecondBest)
			results.at(1) += 1; //defender loses 1
		else
			results.at(0) += 1; //attacker loses 1
	}

	attackingPlayer->setLogMessage(attackingPlayer->getPlayerName() + " lost " + to_string(results[0]) + " armies");
	defendingPlayer->setLogMessage(defendingPlayer->getPlayerName() + " lost " + to_string(results[1]) + " armies");
	return results;
}

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
				cout << "\nPlayer \"";
				handle->print(player->getPlayerName(), player->getColor());
				cout << "\", select country to attack ";
				handle->print("from", player->getColor());
				cout << ": (country must have more than one army)" << endl << endl;
				
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
			cout << "\", select country ";
			handle->print("to", player->getColor());
			cout << " attack: (country must be adjacent to attacking country)" << endl << endl;

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
		while (1)
		{
			cout << "\nPlayer \"";
			handle->print(player->getPlayerName(), player->getColor());
			cout << "\", select 1-3 armies to attack with: (You have " << attack->getArmyCount() << " total armies, " << attack->getArmyCount() - 1 << " available to attack)" << endl << endl;
			cin >> attackAmount;

			//Error message if invalid armies is input for attacker(must be an integer 1-3, provided player has enough armies available(must leave at least one army behind))
			if (attackAmount > attack->getArmyCount() - 1 || attackAmount < 1 || attackAmount > 3)
				cout << "\nInvalid input" << endl;
			else
				break;
		}



		// STEP 4: GET NUMBER OF DICE TO DEFEND WITH
		while (1)
		{
			cout << "\nPlayer \"";
			handle->print(defend->owner->getPlayerName(), defend->owner->getColor());
			cout << "\", select 1-2 armies to attack with: (You have " << defend->getArmyCount() << " total armies)" << endl << endl;
			cin >> defendAmount;

			//Error message if invalid armies is input for defender(must be an integer 1-2, provided player has enough armies available)
			if (defendAmount > defend->getArmyCount() || defendAmount < 1 || defendAmount > 2)
				cout << "\nInvalid input" << endl;
			else
				break;
		}

		attack->owner->setLogMessage(attack->owner->getPlayerName() + " chose to attack " + defend->owner->getPlayerName() + " from " + attack->getName() + " with " + to_string(attackAmount) + " armies to " + defend->getName() + " with " + to_string(defendAmount) + " armies."); 

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
			system("PAUSE"); 
			MC->getMap()->notify();
			
			if (alreadyHasCard == false)
			{
				player->getCard();
				alreadyHasCard = true;
			}
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
	vector<int> resultsOfBattle; 


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
				if (player->countriesOwned[i]->adjacentCountries[j]->getArmyCount() < attack->getArmyCount() && attack->getArmyCount() >= 2 && attack->owner->getPlayerName() != player->countriesOwned[i]->adjacentCountries[j]->owner->getPlayerName())
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
			handle->print("\nAttacking " + defend->getName() + " from " + attack->getName() + "\n", player->getColor());
			
			// STEP 2.1: Get attacker army count (Attacker will always use highest number of dice available)
			attackAmount = attack->getArmyCount() - 1; 
			if (attackAmount > 3)
				attackAmount = 3; 
			cout << "\nPlayer ";
			cout << attack->owner->getPlayerName() << " chooses to attack with " << attackAmount << " armies.";
			// STEP 2.2: Get defender army count
			cout << "\nPlayer ";
			handle->print(defend->owner->getPlayerName(), defend->owner->getColor());
			while (1)
			{

				cout << " select 1-2 armies to attack with: (You have " << defend->getArmyCount() << " total armies)" << endl << endl;
				cin >> defendAmount;

				//Error message if invalid armies is input for defender(must be an integer 1-2, provided player has enough armies available)
				if (defendAmount > defend->getArmyCount() || defendAmount < 1 || defendAmount > 2)
					cout << "\nInvalid input" << endl;
				else
					break;
			}

			attack->owner->setLogMessage(attack->owner->getPlayerName() + " chose to attack " + defend->owner->getPlayerName() + " from " + attack->getName() + " with " + to_string(attackAmount) + " armies to " + defend->getName() + " with " + to_string(defendAmount) + " armies.");

			// STEP 2.3: Attack with dice roll
			//roll the dice
			resultsOfBattle.clear(); //initialize vector in case player wants to attack again
			resultsOfBattle = rolldice(attackAmount, defendAmount, player, defend->owner);
			attackerTroopsLost = resultsOfBattle.at(0);
			defenderTroopsLost = resultsOfBattle.at(1);
			
			attack->setArmyCount(attack->getArmyCount() - attackerTroopsLost);  // decrement troops
			defend->setArmyCount(defend->getArmyCount() - defenderTroopsLost);  // decrement troops

			system("PAUSE");
			MC->getMap()->notify();

			// STEP 2.4: If country has no more troops, take it over
			if (defend->getArmyCount() == 0)
			{
				player->takeOver(attack, defend, attackAmount, attackerTroopsLost);

				if (alreadyHasCard == false)
				{
					player->getCard();
					alreadyHasCard = true;
				}
				system("PAUSE");
				MC->getMap()->notify();
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
	vector<int> resultsOfBattle;

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


			for (int j = 0; j < temp->adjacentCountries.size(); j++) {
				if (temp->adjacentCountries[j]->getArmyCount() >= (int)(temp->getArmyCount() / 2) && player->getPlayerName() != temp->adjacentCountries[j]->owner->getPlayerName())
					result = false;
			}
			if (result = true)
			{
				//check that there at least exists a neighbor that is owned by a different player, if so set it as the defender
				for (int j = 0; j < player->countriesOwned[i]->adjacentCountries.size(); j++) {
					if (player->getPlayerName() != temp->adjacentCountries[j]->owner->getPlayerName())
					{
						attack = player->countriesOwned[i];
						defend = player->countriesOwned[i]->adjacentCountries[j]; 
					}
						
				}
				
				if(attack != NULL)
					break;
			}
		}

		// STEP 2: ALWAYS ATTACK FIRST COUNTRY IN ADJACENT LIST (ALL HAVE 1/2 THE ARMIES OR LESS)
		if (attack != NULL) {
		
			handle->print("\nAttacking " + defend->getName() + " from " + attack->getName() + "\n", player->getColor());

			// STEP 2.1: Get attacker army count (Attacker will always use highest number of dice available)
			attackAmount = attack->getArmyCount() - 1;
			if (attackAmount > 3)
				attackAmount = 3;
			cout << "\nPlayer ";
			cout << attack->owner->getPlayerName() << " chooses to attack with " << attackAmount << " armies.";

			// STEP 2.2: Get defender army count
			cout << "\nPlayer ";
			handle->print(defend->owner->getPlayerName(), defend->owner->getColor());
			while (1)
			{

				cout << " select 1-2 armies to attack with: (You have " << defend->getArmyCount() << " total armies)" << endl << endl;
				cin >> defendAmount;

				//Error message if invalid armies is input for defender(must be an integer 1-2, provided player has enough armies available)
				if (defendAmount > defend->getArmyCount() || defendAmount < 1 || defendAmount > 2)
					cout << "\nInvalid input" << endl;
				else
					break;
			}

			attack->owner->setLogMessage(attack->owner->getPlayerName() + " chose to attack " + defend->owner->getPlayerName() + " from " + attack->getName() + " with " + to_string(attackAmount) + " armies to " + defend->getName() + " with " + to_string(defendAmount) + " armies.");

			// STEP 2.3: Attack with dice roll
			resultsOfBattle.clear(); //initialize vector in case player wants to attack again
			resultsOfBattle = rolldice(attackAmount, defendAmount, player, defend->owner);
			attackerTroopsLost = resultsOfBattle.at(0);
			defenderTroopsLost = resultsOfBattle.at(1);

			attack->setArmyCount(attack->getArmyCount() - attackerTroopsLost);  // decrement troops
			defend->setArmyCount(defend->getArmyCount() - defenderTroopsLost);  // decrement troops

			system("PAUSE");
			MC->getMap()->notify();

			// STEP 2.4: If country has no more troops, take it over
			if (defend->getArmyCount() == 0)
			{
				player->takeOver(attack, defend, attackAmount, attackerTroopsLost);

				if (alreadyHasCard == false)
				{
					player->getCard();
					alreadyHasCard = true;
				}
				system("PAUSE");
				MC->getMap()->notify();
			}
		}
		else
			break; // No countries to attack, end turn
	}

	handle->print("No more countries to attack. End of attack phase", player->getColor());

}

void RandomStrategy::attack(Player* player)
{

	// Placeholders
	Country* attack;
	Country* defend;
	int attackAmount = 0;
	int defendAmount = 0;
	int attackerTroopsLost = 0;
	int defenderTroopsLost = 0;
	bool alreadyHasCard = false;
	vector<int> resultsOfBattle;

	// 50% chance it will attack, 50% chance it will not
	srand(time(NULL));			// Initialize seed
	int randomNum = rand() % 2;	// Generate 0 or 1


	if (randomNum)
	{
		handle->print(player->getPlayerName() + " chose to randomly attack!!!", player->getColor());
		// Initialize
		attack = NULL;
		defend = NULL;

		// STEP 1: FIND FIRST COUNTRIES THAT FITS ATTACK DESCRIPTION (ATTACKER AND DEFENDER) 
		for (int i = 0; i < player->countriesOwned.size(); i++)
		{
			attack = player->countriesOwned[i];
			for (int j = 0; j < player->countriesOwned[i]->adjacentCountries.size(); j++) {
				if (player->countriesOwned[i]->adjacentCountries[j]->getArmyCount() < attack->getArmyCount() && attack->getArmyCount() >= 2 && attack->owner->getPlayerName() != player->countriesOwned[i]->adjacentCountries[j]->owner->getPlayerName())
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
			handle->print("\nAttacking " + defend->getName() + " from " + attack->getName() + "\n", player->getColor());

			// STEP 2.1: Get attacker army count (Attacker will always use highest number of dice available)
			attackAmount = attack->getArmyCount() - 1;
			if (attackAmount > 3)
				attackAmount = 3;
			cout << "\nPlayer \"";
			handle->print(attack->owner->getPlayerName(), attack->owner->getColor());
			cout << "\" chooses to attack with " << attackAmount << " armies.";
			
			// STEP 2.2: Get defender army count
			
			while (1)
			{
				cout << "\nPlayer \"";
				handle->print(defend->owner->getPlayerName(), defend->owner->getColor());
				cout << "\" select 1-2 armies to defend with: (You have " << defend->getArmyCount() << " total armies)" << endl << endl;
				cin >> defendAmount;

				//Error message if invalid armies is input for defender(must be an integer 1-2, provided player has enough armies available)
				if (defendAmount > defend->getArmyCount() || defendAmount < 1 || defendAmount > 2)
					cout << "\nInvalid input" << endl;
				else
					break;
			}

			attack->owner->setLogMessage(attack->owner->getPlayerName() + " chose to attack " + defend->owner->getPlayerName() + " from " + attack->getName() + " with " + to_string(attackAmount) + " armies to " + defend->getName() + " with " + to_string(defendAmount) + " armies.");

			// STEP 2.3: Attack with dice roll
			resultsOfBattle.clear(); //initialize vector in case player wants to attack again
			resultsOfBattle = rolldice(attackAmount, defendAmount, player, defend->owner);
			attackerTroopsLost = resultsOfBattle.at(0);
			defenderTroopsLost = resultsOfBattle.at(1);

			attack->setArmyCount(attack->getArmyCount() - attackerTroopsLost);  // decrement troops
			defend->setArmyCount(defend->getArmyCount() - defenderTroopsLost);  // decrement troops

			system("PAUSE");
			MC->getMap()->notify();

																				// STEP 2.4: If country has no more troops, take it over
			if (defend->getArmyCount() == 0)
			{
				player->takeOver(attack, defend, attackAmount, attackerTroopsLost);

				if (alreadyHasCard == false)
				{
					player->getCard();
					alreadyHasCard = true;
				}
				system("PAUSE");
				MC->getMap()->notify();
			}
		}
	}
	else
		handle->print(player->getPlayerName() + " chose to randomly not attack!!!", player->getColor());
}
