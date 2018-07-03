#pragma once
#include <vector>

#include "Window.h"
#include "Shader\Shader.h"
#include "Camera.h"

namespace Core {

	class Director {
	public:
		Director();
		~Director();
		
		/*
			@ Create a new GLFW window
			@ screen_x = Screen Width
			@ screen_y = Screen Height
			@ name = Screen title
		*/
		void CreateWindow(int screen_x, int screen_y, const char* name);

		/*
			@ this window will be the current context window
		*/
		void setContexWindow(Window* window);
		void Destroy();

		/*
			@ returns the current GLFWwindow* being used
			
		*/
		GLFWwindow* getWindow();

		/*
			@ get current screen width resolution
		*/
		int getScreenWidth();
		
		/*
			@ get current screen height resolution
		*/
		int getScreenHeight();

		/*
			@ returns the current Window*
		*/
		Window* getCurrentWindow();

		/*
			@ define the current shader
		*/
		void setShader(Shader* shader);

		/*
			@ get the current shader
		*/
		Shader* getShader();

		/*
			@ set the current camera
		*/
		void setCamera(Camera* camera);

		/*
			@ get the current camera
		*/
		Camera* getCamera();

	private:
		std::vector<Window*> vec_windows;
		Window* currentContext;
		Shader* shader;
		Camera* camera;
		void windowResizeCallback(GLFWwindow* window, int , int);
	};

}

