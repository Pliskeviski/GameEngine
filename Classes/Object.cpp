#include "Object.h"

Object::Object() {
	components.push_back(new Transform);
	this->o_name = "New Object";
	this->Active = true;
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

bool& Object::isActive() {
	return this->Active;
}

void Object::setName(const char * name) {
	this->o_name = (char*)name;
}

char* Object::getName() {
	return (char*)this->o_name.c_str();
}

void Object::draw(Core::Director* director) {
	if (!Active)
		return;
	Mesh* o_mesh = this->getComponent<Mesh*>();
	if(o_mesh != NULL)
		o_mesh->Draw(director, this->getComponent<Transform*>());
}


