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


void GameController::runGame() {
	PC->addPlayerToGame(this->getNumOfPlayers());
	startUpPhase();

	Player* currentPlayer;
	char quitInput;

	while(true)
	{
		currentPlayer = PC->getTurn();
		reinforcementPhase(currentPlayer);
		battlePhase(currentPlayer);
		fortificationPhase(currentPlayer);

		cout << "\nQuit game? (y/n)";
		cin >> quitInput;

		if (quitInput == 'y' || quitInput == 'Y')
		{
			break;
		}
		PC->nextTurn();
	} 
	cout << "\nThanks for playing!" << endl << endl;
	system("pause");
}

/** This is the start-up phase of the game
*   It will prompt the user for a user-saved map file
*	and then load the map as a connected graph.
*	It will also prompt the user for the number of players
*	and randomly assign the countries to the players.
*/
void GameController::startUpPhase() {
	this->assignCountries();

	//START OF STARTUP TROOPS PLACEMENT
	Player* currentPlayer;
	int numOfPlayers = PC->getPlayerList().size();
	MC->getMap()->notify();
	for (int i = 0; i < numOfPlayers; i++)
	{
		currentPlayer = PC->getPlayerList().at(i);
		int remainingStartupTroops = this->getStartingArmies(currentPlayer->countriesOwned);
		addTroopsToCountry(currentPlayer, remainingStartupTroops, "remaining");

		PC->nextTurn();
	}
}

/** Reinforcements are distributed as follows:
*	- The total number of countries owned by a player is divided by 3 and rounded down. If this is less than 3, then it is rounded up to 3 armies
*	- If the player owned an entire continent, they get a bonus depending on the bonus of that continent
*/
void GameController::reinforcementPhase(Player* player) {
	

	/**
	*	While there are still reinforcements to place, will display contents of the contriesOwned vector of the player and
	*	will ask for a country name.
	*	Will check to see if this country name is in the vector. If found will ask for reinforcements to add.
	*	If value is valid (not more than reinforcements allowed) will add this value to current armies existing on the country.
	*/
	
	addTroopsToCountry(player, this->getReinforcmentTroops(player), "reinforments");	
	
}

/**
*
*/
void GameController::battlePhase(Player* player) 
{
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
			cout << "\nFortification phase for player \""; 
			handle->print(player->getPlayerName(), player->getColor());
			cout << "\"," << endl << endl;
			cout << "Select a country to move troops from: " << endl << endl;

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
				cout << "\nYou have " << player->countriesOwned.at(fortCountryIndex)->getArmyCount() << " troops, " << player->countriesOwned.at(fortCountryIndex)->getArmyCount() - 1 << " are available to move. How many troops would you like to move? " << endl << endl;
				cin >> troopsToMove;

				//If troopsToMove is less than one or more than the armies on the country -1 (must leave at least 1 army),
				//asks for another input.
				while (troopsToMove >= player->countriesOwned.at(fortCountryIndex)->getArmyCount() || troopsToMove < 1)
				{
					cout << "\nInvalid input! Must select a value less than " << player->countriesOwned.at(fortCountryIndex)->getArmyCount() << endl << endl;
					cin >> troopsToMove;
				}

				MC->getMap()->notify();

				cout << "Select an adjacent country to complete the move:" << endl << endl;

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
				cout << "\nInvalid country input! For a country to be valid you must own it, own an adjacent country next to it and have more than 1 army on it! " << endl << endl;
				system("pause");
			}
		}
		else
		{
			break;
		}
	}
}

int GameController::getNumOfPlayers() {
	int numOfPlayers;
	while (true)
	{
		cout << "\n\nHow many players will be playing?" << endl;
		cin >> numOfPlayers;
		if (numOfPlayers > 5 || cin.fail() || numOfPlayers <= 1)
		{
			cout << "Invalid number of players" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else
		{
			return numOfPlayers;
		}
	}
}

void GameController::assignCountries() {
	vector<Player*> players = PC->getPlayerList();
	vector<Country*> countriesRemaining = MC->getMap()->allCountries;
	int maxCountriesPerPlayer = (countriesRemaining.size() / players.size());
	int randomNumber;
	for (int i = 0; i < players.size(); i++) {
		for (int j = 0; j < maxCountriesPerPlayer; j++) {
			// random number between 0 and countriesRemaing - 1
			randomNumber = (rand() % (int)(countriesRemaining.size()));
			players.at(i)->setOwnsCountry(countriesRemaining.at(randomNumber));
			countriesRemaining.at(randomNumber)->setArmyCount(1);
			countriesRemaining.erase(countriesRemaining.begin() + randomNumber);
		}
	}

	int i = 0;
	while (countriesRemaining.size() != 0) {
		if (i == players.size())
			i = 0;
		randomNumber = (rand() % (int)(countriesRemaining.size()));
		players.at(i)->setOwnsCountry(countriesRemaining.at(randomNumber));
		countriesRemaining.at(randomNumber)->setArmyCount(1);
		countriesRemaining.erase(countriesRemaining.begin() + randomNumber);
		++i;
	}
}

void GameController::addTroopsToCountry(Player* player, int numOfTroops, string str) {
	while (numOfTroops != 0)
	{

		handle->print("\nPlayer \"" + player->getPlayerName() + "\", \n", player->getColor());
		handle->print("Select country to add " + str + " troops to: (" + to_string(numOfTroops) + " troops to be placed.)\n\n");

		if (cin.peek() == '\n') {
			cin.ignore(1, '\n');
		}
		string strCountry = "";
		getline(cin, strCountry);
		cout.flush();

		Country* selectedCountry = this->findCountry(strCountry, player->countriesOwned);

		if (selectedCountry == nullptr) {
			cout << "\nInvalid country input! No changes will be made." << endl << endl;
			continue;
		}

		cout << "\nHow many troops would you like to add? " << numOfTroops << " troops remaining to be placed." << endl << endl;
		int troopsToAdd;
		cin >> troopsToAdd;

		//If troopstoAdd are greater than reinforcements allowed, asks user to reinput.
		while (troopsToAdd > numOfTroops || troopsToAdd < 1)
		{
			cout << "\nInvalid input! Must select a value less than or equal to " << numOfTroops << endl << endl;
			cin >> troopsToAdd;
		}

		//Decrements reinforcements by troopsToAdd inputed by player.
		numOfTroops -= troopsToAdd;

		//Modifies armies located on selected country according to reinforcements to be placed.
		selectedCountry->setArmyCount(selectedCountry->getArmyCount() + troopsToAdd);

		MC->getMap()->notify();
		/* ILog* logger = new LogStartup(new Logger());
		logger->setCountry(PC->getPlayerList().at(i)->countriesOwned.at(startupCountryIndex)->getName());
		logger->setStartupTroopsAdded(startupTroopsToAdd)
		PC->getPlayerList().at(i)->getLogSubject()->attach(logger); */

		cout << troopsToAdd << " troops were added successfully to " << selectedCountry->getName() << "." << endl << endl;
	}
}

int GameController::getStartingArmies(vector<Country*> ownedCountries) {
	const double ARMY_MULTIPLIER = 1.5;
	vector<Country*> allCountries = MC->getMap()->allCountries;
	int numOfPlayers = PC->getPlayerList().size();
	int startingArmies = (int)((allCountries.size() / numOfPlayers) * ARMY_MULTIPLIER);

	return startingArmies - ownedCountries.size();
}

int GameController::getReinforcmentTroops(Player* player) {
	int numberOfCountriesOwned = player->countriesOwned.size();

	int reinforcements = numberOfCountriesOwned / 3;

	if (reinforcements < 3) {
		reinforcements = 3;
	}
	reinforcements += player->getContinentBonus(MC->getMap());

	return reinforcements;
}

Country* GameController::findCountry(string country, vector<Country*> countries) {
	for (int i = 0; i < countries.size(); i++) {
		if (countries.at(i)->getName() == country) {
			return countries.at(i);
		}
	}

	return nullptr;
}