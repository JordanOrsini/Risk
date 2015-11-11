#include "Subject.h"

Subject::Subject() {
	observers = new list<Observer*>;
}
void Subject::notify() {
	list<Observer *>::iterator i = observers->begin();
	for (; i != observers->end(); i++) {
		(*i)->update();
	}
}

void Subject::attach(Observer* o) {
	observers->push_back(o);
	notify();
}

void Subject::detatch(Observer* o) {
	observers->remove(o);
}

Subject::~Subject() {
	delete observers;
	observers = nullptr;
}