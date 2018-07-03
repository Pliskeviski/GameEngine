#include "Window.h"

int w_count = 0;
unsigned int glew_init = 0;

Window::Window(int screen_w, int screen_h, const char* name) {
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	this->name = name;
	this->MSAA = 40;
	this->cursor = true;
	CreateWindow();
}

Window::Window(int screen_w, int screen_h, const char* name, unsigned int MSAA) {
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	this->name = name;
	this->MSAA = MSAA;
	this->cursor = true;
	CreateWindow();
}

void Window::CreateWindow() {
	if (w_count == 0) {		// Will be the first window so we
		assert(glfwInit()); // init GLFW
	}

	glfwWindowHint(GLFW_SAMPLES, MSAA);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	this->window = glfwCreateWindow(this->screen_w, this->screen_h, this->name, NULL, NULL);
	assert(this->window != NULL); // variable "window" must be a valid pointer

	this->screen_w = screen_w;
	this->screen_h = screen_h;
	this->w_ID = w_count++;
}

Window::~Window() {
}

void Window::MakeContextCurrent() {
	glfwMakeContextCurrent(this->window);
	Input::setWindow(this->window);

	if (!glew_init++) { //Init glew
		glewExperimental = true; 
		assert(glewInit() == GLEW_OK);
	}
}

void Window::EnableCursor() {
	assert(window != NULL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	cursor = true;
}

void Window::DisableCursor() {
	assert(window != NULL);
	glfwSetCursorPos(window, screen_w / 2, screen_h / 2); // TODO: check and update the resolution when the screen is resized
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	cursor = false;
}

bool Window::isCursor() { return this->cursor; }
int  Window::getWidth() { return this->screen_w; }
int  Window::getHeight() { return this->screen_h; }
void Window::changeCursor() { this->cursor ^= true; }
GLFWwindow* Window::getWindow() { return this->window; }


