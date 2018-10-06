#pragma once
#include <glm\glm.hpp>
#include "Component.h"

class Transform : public Component {
public:
	/*
		@ new transform component
		@ optional parameters
		@ position and rotation
	*/
	Transform(glm::vec3 t_position = glm::vec3(0, 0, 0), glm::vec3 t_rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));

	/*
		@ set transform position
	*/
	void setPosition(glm::vec3 t_position);
	
	/*
		@ set tranform X position
	*/
	void setPositionX(float x);

	/*
		@ set transform Y position
	*/
	void setPositionY(float y);

	/*
		@ set transform Z position
	*/
	void setPositionZ(float z);

	/*
		@ set transform rotation
	*/
	void setRotation(glm::vec3 t_rotation);

	/*
		@ set transform X rotation
	*/
	void setRotationX(float x);

	/*
		@ set transform Y rotation
	*/
	void setRotationY(float y);

	/*
		@ set transform Z rotation
	*/
	void setRotationZ(float z);

	/*
		@ set transform parent
	*/
	void setParent(Transform* parent);

	/*
		@ get transform global location
	*/
	glm::vec3 getPosition();

	/*
		@ get transform global location in X
	*/
	float getPositionX();
	
	/*
		@ get transform global location in Y
	*/
	float getPositionY();

	/*
		@ get transform global location in Z
	*/
	float getPositionZ();

	/*
		@ get transform rotation
	*/
	glm::vec3 getRotation();

	/*
		@ get transform rotation in X
	*/
	float getRotationX();

	/*
		@ get transform rotation in Y
	*/
	float getRotationY();

	/*
		@ get transform rotation in Z
	*/
	float getRotationZ();

	/*
		@ return transform parent
		@ return NULL if none
	*/
	Transform* getParent();

	/*
		@ return transform scale
	*/
	glm::vec3 getScale();

	/*
		@ define transform scale (x, y, z)
	*/
	void setScale(glm::vec3 scale);
	/*
	@ define transform scale (same for x, y, z)
	*/
	void setScale(float scale);

	// Temp
	glm::vec3& getVec3Pos() {
		return this->t_position;
	}
	glm::vec3& getVec3Rot() {
		return this->t_rotation;
	}
	glm::vec3& getVec3Scale() {
		return this->t_scale;
	}

	/*
		@ return if is a child
	*/
	bool isChild();

private:
	bool t_isChild;
	glm::vec3 t_position;
	glm::vec3 t_rotation;
	glm::vec3 t_scale;
	Transform* t_parent;
};