#include <iostream>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <Imgui\imgui.h>
#include "Deps\Include\Imgui\glfw\imgui_impl_glfw_gl3.h"

#include "Editor\FrameBuffer.h"
#include "Editor\GridFloor.h"

#include "Classes\Shader\Shader.h"
#include "Classes\Director.h"
#include "Classes\Camera.h"
#include "Classes\Input.h"

#include "Classes\Component.h"
#include "Classes\Transform.h"

#include "Classes\Mesh.h"
#include "Classes\Object.h"

#include ".\Classes\Pliskeviski\String.h"

int main() {
	Core::Director* director = new Core::Director; // Creates a "Director", will manage everything
	director->CreateWindow(1920, 920, "Pliskeviski Editor");
	// ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(director->getWindow(), true);

	pl::string vertexPath = "Shaders\\TransformVertexShader.vertexshader";
	pl::string fragmentPath = "Shaders\\ColorFragmentShader.fragmentshader";
	Shader* shader = new Shader(vertexPath, fragmentPath);
	director->setShader(shader);

	glClearColor(.4f, .4f, .4f, 1.f);
	
	FrameBuffer framebuffer(director);

	// editor default camera
	
	Camera* camera; // 

	Camera* camera_1 = new Camera;
	Camera* camera_2 = new Camera;

	camera = camera_1;
	director->setCamera(camera);

	bool firstMouse = true;

	bool isMoving = false; 

	bool focus_scene = false;

	bool camera_inScene = false;

	float sens = .12f;

	unsigned int mouse2_clicks = 0;

	// getting components example
	Transform* t = camera->getComponent<Transform*>();
	
	pl::string vertexP = "Shaders\\shader.vertexshader";
	pl::string fragmentP = "Shaders\\shader.fragmentshader";
	Shader* g_shader = new Shader(vertexP, fragmentP);
	//director->setShader(g_shader);

	unsigned int g_size = 10;
	Grid grid_floor(10, 10);

	Object* obj = new Object;
	//Mesh* mesh = new Mesh("Models\\Misc\\cubies.ple");
	Mesh* mesh = new Mesh("Models\\Revolver\\Colt_Python.ple");
	(*mesh)[0]->addTexture("Models\\Revolver\\diffuse.tga", TYPE_DIFFUSE);
	//Mesh* mesh = new Mesh("Models\\Coffe\\cup_low_poly.ple");
	//(*mesh)[0]->addTexture("Models\\Coffe\\cup_BaseColor.tga", TYPE_DIFFUSE);
	obj->addComponent(mesh);

	Object* cup = new Object;
	Mesh* meshCup = new Mesh("Models\\Coffe\\cup_low_poly.ple");
	(*meshCup)[0]->addTexture("Models\\Coffe\\cup_BaseColor.tga", TYPE_DIFFUSE);
	cup->addComponent(meshCup);

	obj->getComponent<Transform*>()->setPosition(glm::vec3(2.f, 1.f, 1.f));
	cup->getComponent<Transform*>()->setPosition(glm::vec3(1.f, 2.f, 0.f));

	//tmp
	obj->getComponent<Transform*>()->setScale(0.08f);
	cup->getComponent<Transform*>()->setScale(0.08f);
	subMesh* m = (*mesh)[0];

	Object* cubies = new Object;
	Mesh* meshCubies = new Mesh("Models\\Misc\\cubies.ple");
	cubies->addComponent(meshCubies);
	cubies->getComponent<Transform*>()->setPositionX(-10.f);

	director->getCamera()->setPositionY(4.f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	float zz = 0;
	while (glfwGetKey(director->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(director->getWindow()) == 0) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();
		
		glClearColor(.4f, .4f, .4f, 1.f);

		framebuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->Use();

		if (Input::isKeyDown(GLFW_KEY_1))
			camera = camera_1;
		if (Input::isKeyDown(GLFW_KEY_2))
			camera = camera_2;

		if (Input::isKeyDown(GLFW_KEY_KP_ADD))
			grid_floor.setGridSize(++g_size, g_size);

		if (Input::isKeyDown(GLFW_KEY_KP_SUBTRACT))
			grid_floor.setGridSize(--g_size, g_size);

		if (Input::isKeyDown(GLFW_KEY_KP_0))
			grid_floor.setActive(false);

		if (Input::isKeyDown(GLFW_KEY_KP_1))
			grid_floor.setActive(true);

		{ // Input and render

			if (Input::isButtonReleased(GLFW_MOUSE_BUTTON_2))
				mouse2_clicks = 0;

			if (Input::isButtonDown(GLFW_MOUSE_BUTTON_2)) {
				mouse2_clicks++;
			}
			
			if (focus_scene && mouse2_clicks == 1 || mouse2_clicks == 1 && camera_inScene) { // Right mouse button
				camera_inScene ^= true;
				if (!camera_inScene) {
					firstMouse = true;
				}
			}
			
			if (camera_inScene) {
				director->getCurrentWindow()->DisableCursor();

				if (Input::isKeyDown(GLFW_KEY_W))
					camera->Forward(.1f);
				if (Input::isKeyDown(GLFW_KEY_S))
					camera->Backwards(.1f);
				if (Input::isKeyDown(GLFW_KEY_D))
					camera->Right(.1f);
				if (Input::isKeyDown(GLFW_KEY_A))
					camera->Left(.1f);
				if (Input::isKeyDown(GLFW_KEY_E))
					camera->addPosY(.1f);
				if (Input::isKeyDown(GLFW_KEY_Q))
					camera->addPosY(-.1f);
				if (Input::isKeyDown(GLFW_KEY_UP))
					camera->addPitch(.7f);
				if (Input::isKeyDown(GLFW_KEY_DOWN))
					camera->addPitch(-.7f);
				if (Input::isKeyDown(GLFW_KEY_LEFT))
					camera->addYaw(-.7f);
				if (Input::isKeyDown(GLFW_KEY_RIGHT))
					camera->addYaw(.7f);

				{ // Camera scripting
					double cursorX;
					double cursorY;
					if (firstMouse == true) {
						cursorX = (director->getScreenWidth() / 2);
						cursorY = (director->getScreenHeight() / 2);
						firstMouse = false;
					}
					else {
						cursorX = ImGui::GetMousePos().x;
						cursorY = ImGui::GetMousePos().y;
					}
					double mouseX = cursorX - (director->getScreenWidth() / 2);
					double mouseY = (director->getScreenHeight() / 2) - cursorY;

					mouseX *= sens;
					mouseY *= sens;

					camera->addYaw(mouseX);
					camera->addPitch(mouseY);
				}
			}
			director->getCamera()->c_Width = ImGui::GetWindowWidth();
			director->getCamera()->c_Height = ImGui::GetWindowHeight() * .93f;

			glEnable(GL_DEPTH_TEST);

			grid_floor.Draw(camera, glm::vec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * .93f));
		}
		obj->getComponent<Transform*>()->setRotationY(sin(zz+=0.05f));
		//(*mesh)[0]->s_transform->setRotation(glm::vec3(zz += 0.1f));
		obj->draw(director);
		cup->draw(director);
		cubies->draw(director);
		cubies->getComponent<Transform*>()->setPositionX((zz += 0.05f));
		(*meshCubies)[1]->s_transform->setPositionX(sin(zz += 0.1f));

		{
			// OpenGL view
			// Render to the frame buffer
			ImGui::Image((void*)framebuffer.getBuffer(), ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * .93f), ImVec2(0, 1), ImVec2(1, 0));
			focus_scene = io.WantCaptureMouse;

			
			framebuffer.Unbind();
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(director->getWindow());
	}

	framebuffer.Delete();

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	director->Destroy();
	delete director;

	return 0;
}
