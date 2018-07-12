#pragma once

#include <GL\glew.h>

#include <memory>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Component.h"
#include "Transform.h"

class Camera {
public:
	/*
		@ default constructor
		@ position at (0,0,0)
	*/
	Camera();
	/*
		@ new camera at location "pos"
	*/
	Camera(glm::vec3 pos);
	
	/*
	@ new camera at location "pos"
	@ and field of view "fov"
	*/
	Camera(glm::vec3 pos, float fov);

	/*
		@ set the camera to a new position
	*/
	void setPosition(glm::vec3 position);

	/*
		@ set the camera position in X
	*/
	void setPositionX(float x);

	/*
		@ set the camera position in Y
	*/
	void setPositionY(float y);

	/*
		@ set the camera position in Z
	*/
	void setPositionZ(float z);

	/*
		@ set the camera's field of view
	*/
	void setFov(float fov);

	/*
		@ Add 'v' to the current X position
		@ position.x += v;
	*/
	void addPosX(float v);

	/*
		@ Add 'v' to the current Y position
		@ position.y += v;
	*/
	void addPosY(float v);

	/*
		@ Add 'v' to the current Z position
		@ position.z += v;
	*/
	void addPosZ(float v);

	/*
		@ Add 'v' to the current Yaw value
		@ yaw += v;
	*/
	void addYaw(double v);

	/*
		@ Add 'v' to the current Pitch value
		@ pitch += v;
	*/
	void addPitch(double v);

	/*
		@ return the camera position
	*/
	glm::vec3 getPosition();

	/*
		@ get the view matrix
		@ glm::lookAt(this->c_pos, this->c_pos + this->c_Front, this->c_Up);
	*/
	glm::mat4 getViewMatrix();

	/*
		@ get the camera's field of view
	*/
	float getFov();

	/*
		@ return yaw value
	*/
	float getYaw();

	/*
		@ return pitch value
	*/
	float getPitch();

	/*
		@ set the yaw value
	*/
	void setYaw(float yaw);

	/*
		@ set the pitch value
	*/
	void setPitch(float pitch);

	/*
		@ get any component
		@ usage example:
		@ Transform* example = camera->getComponent<Tranform*>();
		@ Transform* example = object->getComponent<Tranform*>();
	*/
	template<typename T>
	T getComponent();

	// Some pre-defined functions

	void Forward(float v);
	void Backwards(float v);
	void Right(float v);
	void Left(float v);


	float c_Width;
	float c_Height;
private:
	void Update();

	glm::vec3 c_Front;
	glm::vec3 c_Up;
	glm::vec3 c_Right;

	double c_Yaw;
	double c_Pitch;
	GLfloat c_Fov;


	std::vector<Component*> c_components;
	Transform* c_transform;
};


template<typename T>
inline T Camera::getComponent() {
	for (unsigned int i = 0; i < c_components.size(); i++) {
		if(typeid(T) == typeid(Transform*) && c_components[i]->type == TRANSFORM)
			return (T)c_components[i];
	}
}