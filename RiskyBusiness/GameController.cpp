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
	int numOfPlayers;
	int maxCountriesPerPlayer;
	int randomNumber;
	int countryPerPlayerRemaining;

	// TO-DO: ask for user-saved file and load

	cout << "\n\nHow many players will be playing?" << endl;
	cin >> numOfPlayers;

	while (true)
	{
		cout << "\n\nHow many players will be playing?" << endl;
		cin >> numOfPlayers;
		if (numOfPlayers > MC->getMap()->allCountries.size())
		{
			cout << "Invalid number of players" << endl;
		}
		else
		{
			break;
		}
	}
	
	PC->addPlayerToGame(numOfPlayers);

	maxCountriesPerPlayer = (MC->getMap()->allCountries.size() / numOfPlayers);
	countryPerPlayerRemaining = MC->getMap()->allCountries.size() % numOfPlayers;

	for (int i = 0; i < MC->getMap()->allCountries.size() - countryPerPlayerRemaining; i++)
	{
		randomNumber = rand() % numOfPlayers;
		while (PC->getPlayerList()[randomNumber]->countriesOwned.size() == maxCountriesPerPlayer);
		{
			randomNumber = rand() % numOfPlayers;
		}
		PC->getPlayerList()[randomNumber]->setOwnsCountry(MC->getMap()->allCountries[i]);
	}

	for (int i = (MC->getMap()->allCountries.size() - countryPerPlayerRemaining); i < MC->getMap()->allCountries.size(); i++)
	{
		randomNumber = rand() % numOfPlayers;
		PC->getPlayerList()[randomNumber]->setOwnsCountry(MC->getMap()->allCountries[i]);
	}
}

void GameController::runGame() {
	bool quitFlag = false;
	Player* currentPlayer = new Player();

	do {
	currentPlayer = PC->getWhoseTurn();
	//reinforcementPhase(currentPlayer); //uncomment once implemented
	//fortificationPhase(currentPlayer); //uncomment once implemented

	//ask if want to quit

	} while (!quitFlag);
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

	reinforcements += player->getContinentBonus();

	/**
	*	While there are still reinforcements to place, will display contents of the contriesOwned vector of the player and
	*	will ask for a country name.
	*	Will check to see if this country name is in the vector. If found will ask for reinforcements to add.
	*	If value is valid (not more than reinforcements allowed) will add this value to current armies existing on the country.
	*/
	while (reinforcements != 0)
	{
		cout << "Select country to add reinforcements to: ";
		
		//Prints out contents of player's countriedOwned vector.
		for (int i = 0; i < player->countriesOwned.size(); i++)
		{
			cout << player->countriesOwned[i]->getName() << " ";
		}
		cout << endl;
		
		cin >> countrySelected;
		
		//Iterates through vector looking for country name inputted by user.
		for (int i = 0; i < player->countriesOwned.size(); i++)
		{
			//If found will ask how many troops to place.
			if (countrySelected == player->countriesOwned[i]->getName())
			{
				countryFound = true;
				countryIndex = i;
				cout << "How many troops would you like to place?" << endl;
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
				player->countriesOwned[countryIndex]->setArmyCount(player->countriesOwned[countryIndex]->getArmyCount() + troopsToAdd);
			}
		}
		
		if (countryFound == false)
		{
			cout << "Invalid country input! No changes will be made." << endl;
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
	int fortCountryIndex = 0;
	int troopsToMove = 0;
	bool fortMoveFound = false;
	
	//Asks user to enter fortification phase.
	cout << "Would you like to enter fortification phase? (y/n)";
	cin >> yesNo;

	//Input validation on user input. 'Y' or 'y' will begin performing a fortification.
	if (yesNo == 'Y' || yesNo == 'y')
	{
		//Prints out countries owned by player.
		cout << "Select a country to move troops from: ";
		for (int i = 0; i < player->countriesOwned.size(); i++)
		{
			cout << player->countriesOwned[i]->getName() << " ";
		}
		cout << endl;

		cin >> fortificationCountry;

		//Iterates over countries owned to check if it contains user inputed country name.
		for (int i = 0; i < player->countriesOwned.size(); i++)
		{
			//If country is found.
			if (fortificationCountry == player->countriesOwned[i]->getName())
			{
				fortCountryFound = true;
				fortCountryIndex = i;
				
				//Asks user how many troops to move.
				cout << "How many troops would you like to move?" << endl;
				cin >> troopsToMove;

				//If troopsToMove is less than one or more than the armies on the country -1 (must leave at least 1 army),
				//asks for another input.
				while (troopsToMove >= player->countriesOwned[fortCountryIndex]->getArmyCount() || troopsToMove < 1)
				{
					cout << "Invalid input! Must select a value less than " << player->countriesOwned[fortCountryIndex]->getArmyCount() << endl;
					cin >> troopsToMove;
				}

				cout << "Select an adjacent country to complete the move: ";

				//Loops over all adjacent countries to user selected country above.
				for (int i = 0; i < player->countriesOwned[fortCountryIndex]->adjacentCountries.size(); i++)
				{
					//Will only print out the adjacent country if the user's player owns it.
					if (player->iOwnCountry(player->countriesOwned[fortCountryIndex]->adjacentCountries[i]))
					{
						cout << player->countriesOwned[fortCountryIndex]->adjacentCountries[i]->getName() << " ";
					}
					
				}

				cin >> fortificationCountry;

				//Will search player's contries owned to see if player owns the adjacent country selected.
				for (int i = 0; i < player->countriesOwned.size(); i++)
				{
					//If adjacent country selected is owned by the player (fortification is valid)
					if (fortificationCountry == player->countriesOwned[i]->getName())
					{
						fortMoveFound = true;
						
						//Decrements number of troops on first selected country.
						player->countriesOwned[fortCountryIndex]->setArmyCount(player->countriesOwned[fortCountryIndex]->getArmyCount() - troopsToMove);
						
						//Increments number of troops on selected player owned adjacent country.
						player->countriesOwned[fortCountryIndex]->adjacentCountries[i]->setArmyCount(player->countriesOwned[fortCountryIndex]->adjacentCountries[i]->getArmyCount() + troopsToMove);

					}
				}
			}
		}

		//If the adjacent country entered by user is not found in the countriesOwned vector.
		if (fortMoveFound == false)
		{
			cout << "Invalid country move. Fortification phase will now end.";
		}

		//If the initial country selected to move troops from is not found in the player's countriesOwned vector.
		if (fortCountryFound == false)
		{
			cout << "Invalid country input! No changes will be made. Fortification phase will now end.";
		}
		
	}
}

void GameController::cleanUp() {

}