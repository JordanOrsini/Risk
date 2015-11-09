#include "GameController.h"

/// Default constructor
GameController::GameController() {
	MapController* MC = new MapController();
	PlayerController* PC = new PlayerController();
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

	// TO-DO: ask for user-saved file and load

	cout << "How many players will be playing?" << endl;
	cin >> numOfPlayers;

	// TO-DO: check if player number and number of countries make sense

	PC->addPlayerToGame(numOfPlayers);

	//TO-DO: randomly assign troops and set troops per person according to number of players
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
	While there are still reinforcements to place, will display contents of the contriesOwned vector of the player and
	will ask for a country name.
	Will check to see if this country name is in the vector. If found will ask for reinforcements to add.
	Will value is valid (not more than reinforcements allowed) will add this value to current armies existing on the country.
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
				while (troopsToAdd > reinforcements)
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
			cout << "Invalid country input! No changes will be made.";
		}
		
	}
	
}

//void GameController::battlePhase() {}

void GameController::fortificationPhase(Player* player) {

}

void GameController::cleanUp() {

}