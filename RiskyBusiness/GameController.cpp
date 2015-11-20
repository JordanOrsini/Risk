#include "GameController.h"

/// Default constructor
GameController::GameController() {
	this->MC = new MapController();
	this->PC = new PlayerController();
}

/// Destructor 
GameController::~GameController() {
	delete MC;
	MC = NULL;
	delete PC;
	PC = NULL;
}

/** This is the start-up phase of the game
*   It will prompt the user for a user-saved map file
*	and then load the map as a connected graph.
*	It will also prompt the user for the number of players
*	and randomly assign the countries to the players.
*/
void GameController::startUpPhase() {
	const double ARMY_MULTIPLIER = 1.5;
	int numOfPlayers;
	int maxCountriesPerPlayer;
	int randomNumber;
	int countryPerPlayerRemaining;
	int startingArmies;
	string startupCountrySelected;
	bool startupCountryFound = false;
	int startupCountryIndex;
	int startupTroopsToAdd;
	int remainingStartupTroops;

	// TO-DO: ask for user-saved file and load

	while (true)
	{
		cout << "\n\nHow many players will be playing?" << endl;
		cin >> numOfPlayers;
		if (numOfPlayers > MC->getMap()->allCountries.size() || cin.fail() || numOfPlayers == 0)
		{
			cout << "Invalid number of players" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else
		{
			break;
		}
	}
	
	PC->addPlayerToGame(numOfPlayers);

	maxCountriesPerPlayer = (MC->getMap()->allCountries.size() / numOfPlayers);
	countryPerPlayerRemaining = MC->getMap()->allCountries.size() % numOfPlayers;
	
	startingArmies = (int)((MC->getMap()->allCountries.size() / numOfPlayers) * ARMY_MULTIPLIER);

	for (int i = 0; i < MC->getMap()->allCountries.size() - countryPerPlayerRemaining; i++)
	{
		randomNumber = rand() % numOfPlayers;
		while (PC->getPlayerList().at(randomNumber)->countriesOwned.size() == maxCountriesPerPlayer)
		{
			randomNumber = rand() % numOfPlayers;
		}
		PC->getPlayerList().at(randomNumber)->setOwnsCountry(MC->getMap()->allCountries.at(i));
		MC->getMap()->allCountries.at(i)->setArmyCount(1);
	}

	for (int i = (MC->getMap()->allCountries.size() - countryPerPlayerRemaining); i < MC->getMap()->allCountries.size(); i++)
	{
		randomNumber = rand() % numOfPlayers;
		PC->getPlayerList().at(randomNumber)->setOwnsCountry(MC->getMap()->allCountries.at(i));
		MC->getMap()->allCountries.at(i)->setArmyCount(1);
	}

	//START OF STARTUP TROOPS PLACEMENT
	for (int i = 0; i < numOfPlayers; i++)
	{
		remainingStartupTroops = startingArmies - PC->getPlayerList().at(i)->countriesOwned.size();

		while (remainingStartupTroops != 0)
		{
			MC->getMap()->notify();
			cout << "\nPlayer \"" << PC->getPlayerList().at(i)->getPlayerName() << "\", \n\nSelect country to add remaining troops to: (" << remainingStartupTroops << " troops to be placed.)" << endl << endl;
			if (cin.peek() == '\n') {
				cin.ignore(1, '\n');
			}
			getline(cin, startupCountrySelected);
			cout.flush();
			//Iterates through vector looking for country name inputted by user.
			for (int j = 0; j < PC->getPlayerList().at(i)->countriesOwned.size(); j++)
			{
				//If found will ask how many troops to place.
				if (startupCountrySelected == PC->getPlayerList().at(i)->countriesOwned.at(j)->getName())
				{
					startupCountryFound = true;
					startupCountryIndex = j;
				
					cout << "\nHow many troops would you like to add? " << remainingStartupTroops << " troops remaining to be placed." << endl;
					cin >> startupTroopsToAdd;

					//If troopstoAdd are greater than reinforcements allowed, asks user to reinput.
					while (startupTroopsToAdd > remainingStartupTroops || startupTroopsToAdd < 1)
					{
						cout << "Invalid input! Must select a value less than or equal to " << remainingStartupTroops << endl;
						cin >> startupTroopsToAdd;
					}
				
					//Decrements reinforcements by troopsToAdd inputed by player.
					remainingStartupTroops -= startupTroopsToAdd;

					//Modifies armies located on selected country according to reinforcements to be placed.
					PC->getPlayerList().at(i)->countriesOwned.at(startupCountryIndex)->setArmyCount(PC->getPlayerList().at(i)->countriesOwned.at(startupCountryIndex)->getArmyCount() + startupTroopsToAdd);
					
					MC->getMap()->notify();
					cout << startupTroopsToAdd << " troops were added successfully to " << PC->getPlayerList().at(i)->countriesOwned.at(startupCountryIndex)->getName() << "." << endl;
					system("pause");
				}

			}
		
			if (startupCountryFound == false)
			{
				cout << "\nInvalid country input! No changes will be made." << endl;
				system("pause");
			}
		
		}
		PC->nextTurn();
	}
	//END OF STARTUP TROOPS PLACEMENT
}

void GameController::runGame() {
	Player* currentPlayer = new Player();
	char quitInput;

	while(true)
	{
		currentPlayer = PC->getTurn();
		reinforcementPhase(currentPlayer); 
		fortificationPhase(currentPlayer);

		cout << "Quit game? (y/n)";
		cin >> quitInput;

		if (quitInput == 'y' || quitInput == 'Y')
		{
			break;
		}
		PC->nextTurn();
	} 
	cout << "Thanks for playing!" << endl;
	system("pause");
}

/** Reinforcements are distributed as follows:
*	- The total number of countries owned by a player is divided by 3 and rounded down. If this is less than 3, then it is rounded up to 3 armies
*	- If the player owned an entire continent, they get a bonus depending on the bonus of that continent
*/
void GameController::reinforcementPhase(Player* player) {
	int numberOfCountriesOwned;
	int reinforcements = 0;
	string countrySelected;
	int troopsToAdd = 0;
	bool countryFound = false;
	int countryIndex = 0;

	numberOfCountriesOwned = player->countriesOwned.size();

	reinforcements = numberOfCountriesOwned / 3;

	if (reinforcements < 3) {
		reinforcements = 3;
	}

	reinforcements += player->getContinentBonus(MC->getMap());

	/**
	*	While there are still reinforcements to place, will display contents of the contriesOwned vector of the player and
	*	will ask for a country name.
	*	Will check to see if this country name is in the vector. If found will ask for reinforcements to add.
	*	If value is valid (not more than reinforcements allowed) will add this value to current armies existing on the country.
	*/
	
	while (reinforcements != 0)
	{
		MC->getMap()->notify();

		cout << "\nReinforcment phase for player \"" << player->getPlayerName() << "\"" << endl;
		cout << "\nSelect country to add reinforcements to: (" << reinforcements << " troops left to add.)" << endl << endl;
		if (cin.peek() == '\n') {
			cin.ignore(1, '\n');
		}
		getline(cin, countrySelected);
		
		//Iterates through vector looking for country name inputted by user.
		for (int i = 0; i < player->countriesOwned.size(); i++)
		{
			//If found will ask how many troops to place.
			if (countrySelected == player->countriesOwned.at(i)->getName())
			{
				countryFound = true;
				countryIndex = i;
				cout << "\nYou have " << reinforcements << " reinforcements. How many troops would you like to place?" << endl;
				cin >> troopsToAdd;

				//If troopstoAdd are greater than reinforcements allowed, asks user to reinput.
				while (troopsToAdd > reinforcements || troopsToAdd < 1)
				{
					cout << "Invalid input! Must select a value less than or equal to " << reinforcements << endl;
					cin >> troopsToAdd;
				}
				
				//Decrements reinforcements by troopsToAdd inputed by player.
				reinforcements -= troopsToAdd;

				//Modifies armies located on selected country according to reinforcements to be placed.
				player->countriesOwned.at(countryIndex)->setArmyCount(player->countriesOwned.at(countryIndex)->getArmyCount() + troopsToAdd);
			
				MC->getMap()->notify();

				cout << troopsToAdd << " troops were added successfully to " << player->countriesOwned.at(countryIndex)->getName() << "." << endl;
				break;
			}
		}
		
		if (countryFound == false)
		{
			cout << "Invalid country input! No changes will be made." << endl;
			system("pause");
		}
		
	}
	
}

//void GameController::battlePhase() {}

/**
*	Fortification phase. Will give user option to enter the phase.
*	Will ask user to select a country he owns.
*	Will ask user how many troops he would like to move. (Must leave at least 1 army on country.
*	Will ask user to select an adjacent country to complete the move.
*	Will decrement troops on initial country selected accordingly.
*	Will increment troops on adjacent country selected if owned by player accordingly.
*/
void GameController::fortificationPhase(Player* player) 
{
	char yesNo;
	string fortificationCountry;
	bool fortCountryFound = false;
	bool fortTroopsEnough = false;
	bool fortOwnNeighboor = false;
	bool fortifySuccess = false;
	int fortCountryIndex = 0;
	int troopsToMove = 0;
	bool fortMoveFound = false;
	
	while (fortifySuccess == false)
	{
		fortCountryFound = false;
		fortTroopsEnough = false;
		fortOwnNeighboor = false;
		
		//Asks user to enter fortification phase.
		cout << "\nWould you like to enter fortification phase? (y/n) ";
		cin >> yesNo;

		//Input validation on user input. 'Y' or 'y' will begin performing a fortification.
		if (yesNo == 'Y' || yesNo == 'y')
		{

			MC->getMap()->notify();
			cout << "\nFortification phase for player \"" << player->getPlayerName() << "\"" << endl << endl;
			cout << "Select a country to move troops from: " << endl;

			if (cin.peek() == '\n') {
				cin.ignore(1, '\n');
			}
			getline(cin, fortificationCountry);

			//CHECK 1
			for (int i = 0; i < player->countriesOwned.size(); i++)
			{
				if (fortificationCountry == player->countriesOwned.at(i)->getName())
				{
					fortCountryFound = true;
					fortCountryIndex = i;
				}
			}

			//CHECK 2
			if (player->countriesOwned.at(fortCountryIndex)->getArmyCount() > 1)
			{
				fortTroopsEnough = true;
			}

			//CHECK 3
			fortOwnNeighboor = player->checkCountryHasNeighborsUOwn(player->countriesOwned.at(fortCountryIndex));

			if (fortCountryFound && fortTroopsEnough && fortOwnNeighboor)
			{
				//Asks user how many troops to move.
				cout << "You have " << player->countriesOwned.at(fortCountryIndex)->getArmyCount() << " troops, " << player->countriesOwned.at(fortCountryIndex)->getArmyCount() - 1 << " are available to move. How many troops would you like to move? " << endl;
				cin >> troopsToMove;

				//If troopsToMove is less than one or more than the armies on the country -1 (must leave at least 1 army),
				//asks for another input.
				while (troopsToMove >= player->countriesOwned.at(fortCountryIndex)->getArmyCount() || troopsToMove < 1)
				{
					cout << "Invalid input! Must select a value less than " << player->countriesOwned.at(fortCountryIndex)->getArmyCount() << endl;
					cin >> troopsToMove;
				}

				MC->getMap()->notify();

				cout << "Select an adjacent country to complete the move: ";

				if (cin.peek() == '\n')
				{
					cin.ignore(1, '\n');
				}
				getline(cin, fortificationCountry);

				//Will search player's contries owned to see if player owns the adjacent country selected.
				for (int i = 0; i < player->countriesOwned.size(); i++)
				{
					//If adjacent country selected is owned by the player (fortification is valid)
					if (fortificationCountry == player->countriesOwned.at(i)->getName())
					{
						fortMoveFound = true;

						//Decrements number of troops on first selected country.
						player->countriesOwned.at(fortCountryIndex)->setArmyCount(player->countriesOwned.at(fortCountryIndex)->getArmyCount() - troopsToMove);

						//Increments number of troops on selected player owned adjacent country.
						player->countriesOwned.at(i)->setArmyCount(player->countriesOwned.at(i)->getArmyCount() + troopsToMove);

						MC->getMap()->notify();

						cout << troopsToMove << " troops successfully moved from the country of " << player->countriesOwned.at(fortCountryIndex)->getName() << " to the country of " << player->countriesOwned.at(i)->getName() << "." << endl;
						fortifySuccess = true;
					}
				}	
			}

			//If the adjacent country entered by user is not found in the countriesOwned vector.
			if (fortMoveFound == false)
			{
				cout << "Invalid country move. Fortification phase will now end." << endl;
				system("pause");
			}

			//If the initial country selected to move troops from is not found in the player's countriesOwned vector.
			if (fortCountryFound == false)
			{
				cout << "Invalid country input! No changes will be made. Fortification phase will now end." << endl;
				system("pause");
			}

		}
		else
		{
			break;
		}
	}
}