#include "Object.h"

Object::Object() {
	components.push_back(new Transform);
}

Object::Object(glm::vec3 position) {
	components.push_back(new Transform(position));
}

void Object::setActive(bool active) {
	this->Active = active;
}

void Object::flipActive() {
	this->Active ^= true;
}

bool Object::isActive() {
	return this->Active;
}


