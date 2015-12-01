#pragma once
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std; 

class Card
{
public: 
	Card(int x) { type = x; }; 
	int getTypeIntValue() { return type; }
	string getTypeName(); 

private: 
	int type; 
};


string Card::getTypeName() {
	string name;

	switch (type) {
	case 1: name = "Artillary";
	case 2: name = "Soldier";
	case 3: name = "Cavalry";
	default: name = "Artillary"; // never happens but just in case
	}

	return name;
}

class Deck
{
public: 
	Card getCard()
	{
		// Randomly choose one of three card types
		srand(time(NULL));					// Initialize seed
		int randomNum = rand() % 3 + 1;	// Generate number between 1-3
		
		// Generate card
		Card card(randomNum); 

		// Give card
		return card; 
	}
};