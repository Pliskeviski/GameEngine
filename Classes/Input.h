#pragma once
#include <assert.h>
#include <GLFW\glfw3.h>

class Input {
public:
	/*
		@ internal usage
	*/
	static void setWindow(GLFWwindow* window);
	
	/*
		@ returns if the key is pressed
		@ use glfw keys
		@ example: isKeyDown(GLFW_KEY_SPACE)
	*/
	static bool isKeyDown(int key);
	
	/*
		@ returns if the key was released
	*/
	static bool isKeyReleased(int key);

	/*
		@ returns if the mouse button is pressed
		@ use glfw keys
		@ example: isButtonDown(GLFW_MOUSE_BUTTON_0)
	*/
	static bool isButtonDown(int key); 

	/*
		@ returns if the button was released
	*/
	static bool isButtonReleased(int key);
};

