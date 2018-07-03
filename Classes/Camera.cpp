#include "Camera.h"

const GLfloat YAW = 0.0f;
const GLfloat PITCH = 0.0f;
const GLfloat FOV = 45.0f;

const glm::vec3 WorldUp = glm::vec3(.0f, 1.f, .0f); // Y is up

Camera::Camera() : c_Yaw(YAW), c_Pitch(PITCH), c_Fov(FOV) { 
	Transform* transform = new Transform;
	c_transform = transform;
	c_components.push_back(transform);
	Update();
	c_components.push_back(new Component);
}
Camera::Camera(glm::vec3 pos) : c_Yaw(YAW), c_Pitch(PITCH), c_Fov(FOV) { 
	Transform* transform = new Transform(pos);
	c_transform = transform;
	c_components.push_back(transform);
	Update();
	c_components.push_back(new Component);
}
Camera::Camera(glm::vec3 pos, float fov) : c_Yaw(YAW), c_Pitch(PITCH), c_Fov(fov) {
	Transform* transform = new Transform(pos);
	c_transform = transform;
	c_components.push_back(transform);
	Update();
	c_components.push_back(new Component);
}

void Camera::Update() {
	glm::vec3 front;
	front.x = cos(glm::radians(this->c_Yaw)) * cos(glm::radians(this->c_Pitch));
	front.y = sin(glm::radians(this->c_Pitch));
	front.z = sin(glm::radians(this->c_Yaw)) * cos(glm::radians(c_Pitch));
	this->c_Front = glm::normalize(front);
	this->c_Right = glm::normalize(glm::cross(this->c_Front, WorldUp));
	this->c_Up = glm::normalize(glm::cross(this->c_Right, this->c_Front));
}

glm::vec3 Camera::getPosition() { return this->c_transform->getPosition(); }

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(this->c_transform->getPosition(), this->c_transform->getPosition() + this->c_Front, this->c_Up);
}

void Camera::setPosition(glm::vec3 position) {
	this->c_transform->setPosition(position);
	Update();
}

void Camera::setPositionX(float x) {
	this->c_transform->setPositionX(x);
	Update();
}

void Camera::setPositionY(float y) {
	this->c_transform->setPositionY(y);
	Update();
}

void Camera::setPositionZ(float z) {
	this->c_transform->setPositionZ(z);
	Update();
}

void Camera::Forward(float v) {
	this->c_transform->setPosition(this->c_transform->getPosition() + this->c_Front * v);
	Update();
}

void Camera::Backwards(float v) {
	this->c_transform->setPosition(this->c_transform->getPosition() - this->c_Front * v);
	Update();
}

void Camera::Right(float v) {
	this->c_transform->setPosition(this->c_transform->getPosition() + this->c_Right * v);
	Update();
}

void Camera::Left(float v) {
	this->c_transform->setPosition(this->c_transform->getPosition() - this->c_Right * v);
	Update();
}

void Camera::addPosX(float v) {
	this->c_transform->setPositionX(this->c_transform->getPositionX() + v);
	Update();
}

void Camera::addPosY(float v) {
	this->c_transform->setPositionY(this->c_transform->getPositionY() + v);
	Update();
}
void Camera::addPosZ(float v) {
	this->c_transform->setPositionZ(this->c_transform->getPositionZ() + v);
	Update();
}

void Camera::addPitch(double v) {
	this->c_Pitch += v;
	if (this->c_Pitch > 89.f)
		this->c_Pitch = 89.f;
	if (this->c_Pitch < -89.f)
		this->c_Pitch = -89.f;
	Update();
}

void Camera::addYaw(double v) {
	this->c_Yaw += v;
	Update();
}

void Camera::setFov(float fov) {
	this->c_Fov = fov;
	Update();
}

float Camera::getFov() {
	return this->c_Fov;
}

float Camera::getYaw() {
	return this->c_Yaw;
}

float Camera::getPitch() {
	return this->c_Pitch;
}

void Camera::setYaw(float yaw) {
	this->c_Yaw = yaw;
}

void Camera::setPitch(float pitch) {
	this->c_Pitch = pitch;
}
