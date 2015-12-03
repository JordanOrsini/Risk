#include "Deck.h"

string Card::getTypeName() {
	string name;

	switch (type) {
	case 1: name = "Artillary"; break;
	case 2: name = "Soldier"; break;
	case 3: name = "Cavalry"; break;
	default: cout << "No card value " << name << endl; exit(0);  // never happens but just in case
	}

	return name;
}

Card* Deck::getCard()
{
	// Randomly choose one of three card types
	srand(time(NULL));					// Initialize seed
	int randomNum = rand() % 3 + 1;	// Generate number between 1-3

									// Generate card
	Card * card;
	card = new Card(randomNum);

	// Give card
	return card;
}