#pragma once
#include <list>
#include "Observer.h"

using namespace std;

class Subject {
public:
	Subject();
	virtual ~Subject();
	virtual void notify(); // notifies all observers of changes
	virtual void attach(Observer* o);
	virtual void detatch(Observer* o);
private:
	list<Observer*>* observers;
};

