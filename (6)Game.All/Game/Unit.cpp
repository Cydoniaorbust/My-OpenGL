#include "Unit.h"

Unit::~Unit() {
	cout << Name << " has left the arena!" << endl;
}
void Unit::Spawn() {
	HP_current = HP_max;
	cout << Name << " has entered the arena!" << endl;
}
bool Unit::isDead() {
	if (HP_current <= 0) {
		delete this;
		return true;
	}
	else return false;
}

string Unit::MyNameIs() {
	return Name;
}
void Unit::NowIam(string name) {
	Name = name;
}
