#include "Colors.h"



Colors::Colors()
{
}

int Colors::assignNewColor() {
	if (pointer >= this->colors.size()) {
		cout << "No more colors available for player." << endl;
		exit(EXIT_FAILURE);
	}

	int color = this->colors.at(this->pointer);
	this->pointer++;

	return color;
}


Colors::~Colors()
{
}
