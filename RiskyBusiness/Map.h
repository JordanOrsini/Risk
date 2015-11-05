#pragma once
//MODEL 
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Map {
public:
	Map(); //default ctor
	Map(string name, string author, string imageFile, string wrap, string scroll, string warn); //ctor for loading from file
	~Map(); //default dtor
	Country* getCountryPointerByName(string name);
	bool mapIsConnected();
	void addContinent(Continent* cName);
	vector<Continent*> allContinents;
	vector<Country*> allCountries;
private:
	string name;
	string author;
	string imageFile;
	string wrap; //in the file
	string scroll; //in the file
	string warn; // in the file
};

class Continent {
public:
	Continent(); //default ctor
	Continent(string continentName, int continentValue); 
	~Continent(); //default dtor
	bool continentIsConnected();
	void addCountry(Country* cName);
	vector<Country*> subCountries;
private:
	string name;
	int value;
};

class Country {
public:
	Country(); //default ctor
	Country(string countryName, int x, int y, string continentName, string listOfAdjacencies);
	~Country(); //default dtor
	bool countryIsconnected();
	void addAdjCountry(Country* cName);
	int getArmyCount();
	void setArmyCount(int newCount);
	vector<Country*> adjacentCountries;
	Player* owner;
private:
	Continent* parentContinent;
	string name;
	int x;
	int y;
	int numOfArmies;
};
