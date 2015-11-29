#pragma once
#include "Map.h"
#include <string>
#include <fstream>

class AbstractSaveLoadAdapter{
public:
	virtual Map* load(string fileName) = 0; 
	virtual void save(Map* m) = 0; 
};

class LegacySaveLoadAdapter : public AbstractSaveLoadAdapter
{
public: 
	Map* load(string fileName);
	void save(Map* m); 
};

class NewSaveLoadAdapter : public AbstractSaveLoadAdapter
{
public:
	Map* load(string fileName);
	void save(Map* m);
};