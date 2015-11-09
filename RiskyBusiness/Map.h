#pragma once
//MODEL 
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Country {
public:
	friend class Player;
	Country(); //default ctor
	Country(string countryName, int x, int y, string continentName, string listOfAdjacencies); // edited parameter to pointer
	~Country(); //default dtor
	bool countryIsconnected();
	void addAdjCountry(Country* cName);
	int getArmyCount();
	void setArmyCount(int newCount);
	vector<Country*> adjacentCountries;
	Player* owner;

	//New 
	string getName() { return name; }
	int getX() { return x; }
	int getY() { return y; }
	vector<string> tempAdjCountryNames;
	string getParentContinentName() { return parentContinentName; }
	bool isConnected() { return connected; }
	void connect() { connected = true; }
	void disconnect() { connected = false; }
private:
	string parentContinentName;
	string name;
	int x;
	int y;
	int numOfArmies;

	//new
	bool connected;
};


class Continent {
public:
	friend class Country;
	Continent(); //default ctor
	Continent(string continentName, int continentValue);
	~Continent(); //default dtor
	bool continentIsConnected();
	void addCountry(Country* cName);
	vector<Country*> subCountries;

	//New 
	string getName() { return name; };
	int getBonusValue() { return bonusValue; };
private:
	string name;
	int bonusValue;
};


class Map {
public:
	friend class Continent;
	friend class Country;
	Map(); //default ctor
	Map(string name, string author, string imageFile, string wrap, string scroll, string warn); //ctor for loading from file
	~Map(); //default dtor
	Country* getCountryPointerByName(string name);
	bool mapIsConnected();
	void addContinent(Continent* cName);
	vector<Continent*> allContinents;
	vector<Country*> allCountries;


	// new
	Map(string name, string author);
	void addCountry(Country* cName);
	Continent* getContinentPointerByName(string name);
	string getName() { return name; }
	string getAuthor() { return author; }
	string getImage() { return imageFile; }
	string getWrap() { return wrap; }
	string getScroll() { return scroll; }
	string getWarn() { return warn; }
private:
	string name;
	string author;
	string imageFile; // in the input file
	string wrap; //in the input file
	string scroll; //in the input file
	string warn; // in the input file
};
