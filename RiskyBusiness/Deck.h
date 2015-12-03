#pragma once
#include <string>
#include <iostream>
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


class Deck
{
public: 
	Card * getCard(); 
};