#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Colors
{
public:
	Colors();
	int assignNewColor();
	~Colors();
private:
	vector<int> colors{11, 12, 13, 14, 15}; //Aqua, Red, Purple, Yellow, White
	int pointer = 0;
};

