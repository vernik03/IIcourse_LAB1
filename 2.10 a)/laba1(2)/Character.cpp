#include "Character.h"

unsigned int Character::GetId() {
	return id;
}

string Character::GetName() {
	return name;
}

void Character::SetId(string str) {
	id = stoi(str);
}

void Character::SetName(string str) {
	name = str;
}