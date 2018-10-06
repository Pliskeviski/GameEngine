#include "Director.h"

namespace Core {

	Director::Director() {
		this->shader = NULL;
		this->currentContext = NULL;
	}

	Director::~Director() {

	}

	void Director::setContexWindow(Window* window) { // Set as glfw context current window
		this->currentContext = window;
		window->MakeContextCurrent();
	}

	void Director::CreateWindow(int screen_x, int screen_y, const char* name) {
		Window* window = new Window(screen_x, screen_y, name);
		setContexWindow(window); // Set as context window
		
		//glfwSetWindowSizeCallback(window->getWindow(), &windowResizeCallback); // TODO

		this->vec_windows.push_back(window);
	}

	void Director::Destroy() { // TODO: check to see if its working
		for (Window* w : vec_windows) {
			delete w->getWindow(); // Free the space used for GLFWwindow
			delete w; // Free the window itself
		}
		
	}

	GLFWwindow* Director::getWindow() { return this->currentContext->getWindow(); }

	Window* Director::getCurrentWindow() { return this->currentContext; }

	void Director::setShader(Shader* shader){
		this->shader = shader;
	}

	Shader* Director::getShader(){
		return this->shader;
	}

	void Director::setCamera(Camera* camera){
		this->camera = camera;
	}

	Camera* Director::getCamera() {
		return this->camera;
	}

	int Director::getScreenWidth() { return this->currentContext->getWidth(); }
	int Director::getScreenHeight() { return this->currentContext->getHeight(); }

	void windowResizeCallback(GLFWwindow* window, int width, int height) { // TODO
	}

}
