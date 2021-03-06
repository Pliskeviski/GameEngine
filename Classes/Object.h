#pragma once
#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Director.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"

class Object {
public:
	/*
		@ new object
		@ at pos (0, 0, 0)
	*/
	Object();
	
	/*
		@ new object at position
	*/
	Object(glm::vec3 position);

	/*
		@ set if this object
		@ is active
	*/
	void setActive(bool active);

	/*
		@ flip if this object
		@ is active value
	*/
	void flipActive();

	/*
		@ get current active state
	*/
	bool& isActive();

	/*
		@ set object name
	*/
	void setName(const char* name);

	/*
		@ get object name
	*/
	char* getName();

	/*
		@ get any component
		@ usage example:
		@ Transform* example = object->getComponent<Tranform*>();
	*/
	template<typename T>
	T getComponent();

	/*
		@ add a component to this object
		@ usage example:
		@ Mesh* mesh = new Mesh;
		@ object->addComponent(mesh);
	*/
	template<typename T>
	void addComponent(T component);

	/*
		@ Draw Object
		@ if has mesh component
	*/
	void draw(Core::Director* director);
private:
	std::vector<Component*> components;
	bool Active;
	std::string o_name;
};

template<typename T>
inline T Object::getComponent() {
	//for (unsigned int i = 0; i < components.size(); i++) {
	//	// Transform
	//	if (typeid(T) == typeid(Transform*) && components[i]->type == TRANSFORM)
	//		return (T)components[i];
	//	// Mesh
	//	if (typeid(T) == typeid(Mesh*) && components[i]->type == MESH)
	//		return (T)components[i];
	//}
	return NULL;
}

template<typename T>
inline void Object::addComponent(T component) {
	//if (component->type == MESH)
	//	static_cast<Mesh*>(component)->setObject(this);

	components.push_back(component);
}
