#include "GameController.h"
#include <algorithm>

/// Default constructor
GameController::GameController() {
	this->MC = new MapController();
	this->PC = new PlayerController();
}

/// Destructor 
GameController::~GameController() {
	delete MC;
	delete PC;
	delete logger;
	delete logSubject;
}


void GameController::runGame() {
	PC->addPlayerToGame(this->getNumOfPlayers());
	for (int i = 0; i < PC->getPlayerList().size(); i++)
	{
		PC->getPlayerList().at(i)->setStrategy(new UserStrategy(MC));
		PC->getPlayerList().at(i)->setMap(MC->getMap());
	}
	startUpPhase();

	Player* currentPlayer;
	char quitInput;

	while(true)
	{
		PC->checkForWin();
		currentPlayer = PC->getTurn();
		reinforcementPhase(currentPlayer);
		battlePhase(currentPlayer);
		fortificationPhase(currentPlayer);
		this->notify(); // update stats
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
		this->setLogger(currentPlayer);
		this->setGameStats(currentPlayer);
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
	char input; 
	int input2; 

	// Check that this phase can be entered, ie. can does the player have country with >1 army adjacent to another player? 
	bool check = false;

	for (int i = 0; i < player->countriesOwned.size(); i++)
	{
		if ((player->countriesOwned[i])->getArmyCount() > 1)
		{
			for (int j = 0; j < player->countriesOwned[i]->adjacentCountries.size(); j++)
			{
				if (player->countriesOwned[i]->adjacentCountries[j]->owner->getPlayerName() != player->getPlayerName())
				{
					check = true;
					break;
				}
			}
		}
	}

	if (check) {
		// Get the current strategy: 
		handle->print("Current attack strategy is: " + player->getStrategy() + "\nWould you like to change this strategy? Enter 'y' for yes anything else for no:", player->getColor());
		cin >> input; 

		if (input == 'y' || input == 'Y')
		{
			while (1) {
				handle->print("The strategies are:\n\t1) User defined actions\n\t2) Aggressive AI\n\t3) Random AI\nEnter 1,2, or 3:", player->getColor());
				cin >> input2; 

				if (input2 == 1 || input2 == 2 || input2 == 3)
					break; 
			}

			switch (input2)
			{
			case 1:	player->setStrategy(new UserStrategy(MC)); break; 
			case 2:	player->setStrategy(new AggressiveStrategy(MC)); break;
			case 3:	player->setStrategy(new RandomStrategy(MC)); break;
			}
		}

		// Now attack
		player->attack();
	}	
	else
	{
		handle->print(player->getPlayerName() + " does not have a country that it can attack from. Skipping attack phase...\n", player->getColor());
	}
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
			cout << "\nFortification phase for "; 
			handle->print("player \"" + player->getPlayerName() + "\"", player->getColor());
			cout << "\nSelect a country to move troops from: " << endl << endl;

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

						//cout << troopsToMove << " troops successfully moved from the country of " << player->countriesOwned.at(fortCountryIndex)->getName() << " to the country of " << player->countriesOwned.at(i)->getName() << "." << endl;
						player->setLogMessage(player->getPlayerName() + " successfully moved " + to_string(troopsToMove) + " troops from " + player->countriesOwned.at(fortCountryIndex)->getName() + " to " + player->countriesOwned.at(i)->getName()); 
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
		cout << "\n\nHow many players will be playing? (2 to 5)" << endl;
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
			player->setLogMessage( "Invalid country input! No changes will be made");
			continue;
		}

		cout << "\nHow many troops would you like to add? " << numOfTroops << " troops remaining to be placed." << endl << endl;
		int troopsToAdd;
		cin >> troopsToAdd;

		//If troopstoAdd are greater than reinforcements allowed, asks user to reinput.
		while (troopsToAdd > numOfTroops || troopsToAdd < 1)
		{
			player->setLogMessage("Invalid input! Must select a value less than or equal to " + to_string(numOfTroops));
			cin >> troopsToAdd;
		}

		//Decrements reinforcements by troopsToAdd inputed by player.
		numOfTroops -= troopsToAdd;

		//Modifies armies located on selected country according to reinforcements to be placed.
		selectedCountry->setArmyCount(selectedCountry->getArmyCount() + troopsToAdd);

		MC->getMap()->notify();

		player->setLogMessage(to_string(troopsToAdd) + " troops were added successfully to " + selectedCountry->getName());
	}
}

int GameController::getStartingArmies(vector<Country*> ownedCountries) {
	const double ARMY_MULTIPLIER = 1.5;
	vector<Country*> allCountries = MC->getMap()->allCountries;
	int numOfPlayers = PC->getPlayerList().size();
	int startingArmies = (int)((allCountries.size() / numOfPlayers) * ARMY_MULTIPLIER);

	startingArmies -= ownedCountries.size(); 

	if (startingArmies < 1)
		startingArmies = 1; 

	return startingArmies;
}

int GameController::getReinforcmentTroops(Player* player) {
	int numberOfCountriesOwned = player->countriesOwned.size();

	int reinforcements = numberOfCountriesOwned / 3;

	if (reinforcements < 3) {
		reinforcements = 3;
	}
	reinforcements += player->getContinentBonus(MC->getMap());

	// Get reinforcements from victory cards, if any
	reinforcements += getVictoryCardReinforcements(player); 

	return reinforcements;
}

int GameController::getVictoryCardReinforcements(Player* player) {

	// Variables for user input
	char Input;
	int card1, card2, card3;

	// Variables to store card type
	int cardType1, cardType2, cardType3;

	// Don't even bother if player has less than three cards
	if (player->hand.size() < 3) {
		handle->print(player->getPlayerName() + " does not have enough victory cards to exchange for reinforcements (Only " + to_string(player->hand.size()) + " cards). Victory card bonus = 0\n", player->getColor());
		return 0;
	}
		

	// Print out list of player's victory cards
	handle->print(player->getPlayerName() + " has the following cards:\n\t", player->getColor());
	for (int i = 0; i < player->hand.size(); i++)
	{
		handle->print(to_string(i) + ":" + player->hand[i]->getTypeName() + " ", player->getColor());
	}
	cout << endl;

	// Ask player if they want to use cards
	handle->print("\nWould you like to exchange victory cards for reinforcements?\nEnter 'y' for yes and anything else for no: ", player->getColor());

	cin >> Input;
	if (Input == 'y' || Input == 'Y')
	{
		while (1)
		{
			handle->print("Please enter each of the indexes (followed by enter) of the cards you wish to exchange: ", player->getColor());
			cin >> card1;
			cin >> card2;
			cin >> card3;

			// Use the cards
			//		-Check that they exist
			//		-No duplicates
			if (card1 >= 0 && card1 < player->hand.size()
				&& card2 >= 0 && card2 < player->hand.size()
				&& card3 >= 0 && card3 < player->hand.size()  // Cards are in bounds
				&& card1 != card2 && card1 != card3
				&& card2 != card3)							  // No duplicates
			{
				cardType1 = player->hand[card1]->getTypeIntValue();
				cardType2 = player->hand[card2]->getTypeIntValue();
				cardType3 = player->hand[card3]->getTypeIntValue();

				// Now check that the three are valid (three of a kind or 1 of each)
				if (cardType1 == cardType2 && cardType1 == cardType3)								// Three of a kind
				{
					// Delete three cards of cardType
					for (int j = 0; j < 3; j++)
					{
						for (int k = 0; k < player->hand.size(); k++)
						{
							if (player->hand[k]->getTypeIntValue() == cardType1)
							{
								player->disCard(k);
								break;
							}
						}
					}
					return 5;
				}
				else if (cardType1 != cardType2 && cardType1 != cardType3 && cardType2 != cardType3) // One of each
				{
					// Delete three cards of different cardTypes
					for (int k = 0; k < player->hand.size(); k++)
					{
						if (player->hand[k]->getTypeIntValue() == cardType1)
						{
							player->disCard(k);
							break;
						}
					}
					for (int k = 0; k < player->hand.size(); k++)
					{
						if (player->hand[k]->getTypeIntValue() == cardType2)
						{
							player->disCard(k);
							break;
						}
					}
					for (int k = 0; k < player->hand.size(); k++)
					{
						if (player->hand[k]->getTypeIntValue() == cardType3)
						{
							player->disCard(k);
							break;
						}
					}

					player->setLogMessage(player->getPlayerName() + " exchanged three victory cards for 5 extra reinforcements."); 
					return 5;
				}
				else
				{
					// Not valid
					handle->print("The selection was not valid. You must choose \"three of a kind\" or \"one of each\"\n", player->getColor());
					handle->print("\nTry again? Enter 'y' for yes and anything else for no", player->getColor());
					cin >> Input;
					if (Input == 'y' || Input == 'Y')
					{ // Will loop again
					}
					else
						break;
				}
			}
			else
				handle->print("There was an error with the selection, either indexes were duplicate or do not exist\n", player->getColor());


		}
	}
	return 0; 
}

Country* GameController::findCountry(string country, vector<Country*> countries) {
	for (int i = 0; i < countries.size(); i++) {
		if (countries.at(i)->getName() == country) {
			return countries.at(i);
		}
	}

	return nullptr;
}

void GameController::setLogger(Player* player) {
	vector<int> choices;

	while (choices.size() < 2) {
		handle->print("\n" + player->getPlayerName(), player->getColor());
		cout << ", select logging options from the following list: \n";
		cout << "\t1. Timestamped logs\n";
		cout << "\t2. Player name\n";
		cout << "\t3. Done\n";

		int choice;
		cin >> choice;

		if (choice > 3 || choice < 1) {
			cout << "Invalid input. Try again.\n";
			continue;
		}

		if (find(choices.begin(), choices.end(), choice) != choices.end()) {
			cout << "Choice already considered.\n";
			continue;
		}

		if (choice == 3) {
			break;
		}
		choices.push_back(choice);
		cout << "Choice " << choice << " registerd.\n";
	}

	sort(choices.begin(), choices.end());

	ILog* log = new Logger(player);
	for (int i = 0; i < choices.size(); i++) {
		switch (choices.at(i)) {
		case 1:
			log = new LogTimestamp(log);
			break;
		case 2:
			log = new LogPlayerName(log);
			break;
		}
	}
	log = new LogNewLine(log);
	player->attach(log);
}

void GameController::setGameStats(Player* player) {
	vector<int> choices;

	while (choices.size() < 2) {
		handle->print("\n" + player->getPlayerName(), player->getColor());
		cout << ", select game stats options from the following list: \n";
		cout << "\t1. See percentage of world ownership\n";
		cout << "\t2. See number of battles won\n";
		cout << "\t3. Done\n";

		int choice;
		cin >> choice;

		if (choice > 3 || choice < 1) {
			player->setLogMessage("Invalid input. Try again.");
			continue;
		}

		if (find(choices.begin(), choices.end(), choice) != choices.end()) {
			player->setLogMessage("Choice already considered.");
			continue;
		}

		if (choice == 3) {
			break;
		}
		choices.push_back(choice);
		player->setLogMessage( "Choice " + to_string(choice) + " registerd.");
	}

	sort(choices.begin(), choices.end());

	IGameStats* stats = new GameStats(player);
	for (int i = 0; i < choices.size(); i++) {
		switch (choices.at(i)) {
		case 1:
			stats = new GameWorldPercentage(stats);
			break;
		case 2:
			stats = new GameBattles(stats);
			break;
		}
	}
	this->attach(stats);
}