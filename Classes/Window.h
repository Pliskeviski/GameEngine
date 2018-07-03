#pragma once
#include <assert.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Input.h"

class Window {
public:
	/*
		@ Creates a new GLFWwindow 
		@ screen_w defines the screen width
		@ screen_h defines the screen height
		@ name will be the window title
	*/
	Window(int screen_w, int screen_h, const char* name);
	/*
		@ Creates a new GLFWwindow
		@ screen_w defines the screen width
		@ screen_h defines the screen height
		@ name will be the window title
		@ MSAA sets the MSAA value for the new window
	*/
	Window(int screen_w, int screen_h, const char* name, unsigned int MSAA);
	/*
		@ set this window as current context
	*/
	void MakeContextCurrent();

	/*
		@ return this window width
	*/
	int getWidth(); 
	/*
		@ return this window height
	*/
	int getHeight();
	
	/*
		@ return this GLFWwindow pointer
	*/
	GLFWwindow* getWindow();

	/*
		@ enable mouse cursor
	*/
	void EnableCursor();

	/*
		@ disable mouse cursor
	*/
	void DisableCursor();

	/*
		@ return the current cursor state
	*/
	bool isCursor();

	/*
		@ chage the cursor boolean
		@ true to false
		@ false to true
	*/
	void changeCursor();

	~Window();
private:
	void CreateWindow();
	GLFWwindow* window;
	
	int screen_w;
	int screen_h;

	bool cursor;

	const char* name;
	unsigned int MSAA;
	unsigned int w_ID;
};

