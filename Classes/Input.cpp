#include "Input.h"

GLFWwindow* active_window;

void Input::setWindow(GLFWwindow* window) {
	active_window = window;
}

bool Input::isKeyDown(int key) {
	assert(active_window != NULL);
	return glfwGetKey(active_window, key);
}

bool Input::isKeyReleased(int key) {
	assert(active_window != NULL);
	return glfwGetKey(active_window, key) == GLFW_RELEASE;
}

bool Input::isButtonDown(int key) {
	assert(active_window != NULL);
	return glfwGetMouseButton(active_window, key) == GLFW_PRESS;
}

bool Input::isButtonReleased(int key) {
	assert(active_window != NULL);
	return glfwGetMouseButton(active_window, key) == GLFW_RELEASE;
}


