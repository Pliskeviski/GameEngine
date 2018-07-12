#include "Transform.h"

Transform::Transform(glm::vec3 t_position, glm::vec3 t_rotation, glm::vec3 scale) {
	this->t_isChild = false;
	this->type = TRANSFORM;
	t_parent = NULL;
	this->t_position = t_position;
	this->t_rotation = t_rotation;
	this->t_scale = scale;
}

void Transform::setPosition(glm::vec3 t_position) {
	this->t_position = t_position; 
}

void Transform::setPositionX(float x) {
	this->t_position.x = x;
}

void Transform::setPositionY(float y) {
	this->t_position.y = y;
}

void Transform::setPositionZ(float z) {
	this->t_position.z = z;
}

void Transform::setRotation(glm::vec3 t_rotation) {
	this->t_rotation = t_rotation;
}

void Transform::setRotationX(float x) {
	t_rotation.x = x;
}

void Transform::setRotationY(float y) {
	t_rotation.y = y;
}

void Transform::setRotationZ(float z) { 
	t_rotation.z = z;
}

void Transform::setParent(Transform * parent) {
	this->t_parent = parent;
}

glm::vec3 Transform::getPosition() {
	return this->t_position;
}

float Transform::getPositionX() {
	return this->t_position.x;
}

float Transform::getPositionY() {
	return this->t_position.y;
}

float Transform::getPositionZ() {
	return this->t_position.z;
}

glm::vec3 Transform::getRotation() {
	return this->t_rotation;
}

float Transform::getRotationX() {
	return this->t_rotation.x;
}

float Transform::getRotationY() {
	return this->t_rotation.y;
}

float Transform::getRotationZ() {
	return this->t_rotation.z;
}

Transform * Transform::getParent() {
	return this->t_parent;
}

glm::vec3 Transform::getScale() {
	return this->t_scale;
}

void Transform::setScale(glm::vec3 scale) {
	this->t_scale = scale;
}

void Transform::setScale(float scale) {
	this->t_scale = glm::vec3(scale);
}

bool Transform::isChild() {
	return this->t_isChild;
}

