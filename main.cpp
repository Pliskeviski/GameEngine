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

	/*
		ImGui list of objects
		TESTING ONLY
	*/
	std::vector<Object*> i_obj;
	Object* selected = NULL;
	subMesh* selected_sub = NULL;

	Object* obj = new Object;
	obj->setName("Plane");
	Mesh* mesh = new Mesh("C:\\Users\\Gustavo\\source\\repos\\Threads\\Models\\Biplano\\biplane_complete.ple");
	obj->addComponent(mesh);
	(*mesh)[0]->addTexture("C:\\Users\\Gustavo\\source\\repos\\Threads\\Models\\Biplano\\prop_biplane_last.jpg",   TYPE_DIFFUSE); 
	(*mesh)[1]->addTexture("C:\\Users\\Gustavo\\source\\repos\\Threads\\Models\\Biplano\\biplano_last.jpg",		   TYPE_DIFFUSE); 
	(*mesh)[2]->addTexture("C:\\Users\\Gustavo\\source\\repos\\Threads\\Models\\Biplano\\wheels_biplane_last.jpg", TYPE_DIFFUSE); 
	(*mesh)[3]->addTexture("C:\\Users\\Gustavo\\source\\repos\\Threads\\Models\\Biplano\\flaps_biplane_last.jpg",  TYPE_DIFFUSE); 
	(*mesh)[4]->addTexture("C:\\Users\\Gustavo\\source\\repos\\Threads\\Models\\Biplano\\prop_biplane_last.jpg",   TYPE_DIFFUSE); 
	obj->getComponent<Transform*>()->setScale(1.f);
	obj->getComponent<Transform*>()->setPositionX(10.f);

	Object* sniper = new Object;
	sniper->setName("Scania");
	Mesh* sniper_mesh = new Mesh("C:\\Users\\Gustavo\\source\\repos\\Threads\\Models\\Scania\\scania.ple");
	sniper->addComponent(sniper_mesh);
	(*sniper_mesh)[4]->addTexture("C:\\Users\\Gustavo\\source\\repos\\Threads\\Models\\Scania\\textures\\tex1.tga", TYPE_DIFFUSE);
	sniper->getComponent<Transform*>()->setScale(.01f);

	// ImGui vector
	i_obj.push_back(sniper);
	i_obj.push_back(obj);

	director->getCamera()->setPositionY(4.f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	float zz = 0;

	// ImGui
	static int listbox_item_current = -1;
	static int list_box_sub = -1;
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


			grid_floor.Draw(camera, glm::vec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * .93f));
		}

		{ // ImGui props
			ImGui::Begin("Options");

			std::vector<char*> t;

			for (int ind = 0; ind < i_obj.size(); ind++)
				t.push_back(i_obj[ind]->getName());

			unsigned int last = listbox_item_current;
			ImGui::ListBox("Objects", &listbox_item_current, &t[0], t.size());
			if (last != listbox_item_current) {
				selected = i_obj[listbox_item_current];
				list_box_sub = -1;
			}

			if (selected != NULL) {
				// Render object options
				
				ImGui::Checkbox("isActive", &selected->isActive());
				
				float* v3[3];
				v3[0] = &selected->getComponent<Transform*>()->getVec3Pos().x;
				v3[1] = &selected->getComponent<Transform*>()->getVec3Pos().y;
				v3[2] = &selected->getComponent<Transform*>()->getVec3Pos().z;

				float* s3[3];
				s3[0] = &selected->getComponent<Transform*>()->getVec3Scale().x;
				s3[1] = &selected->getComponent<Transform*>()->getVec3Scale().y;
				s3[2] = &selected->getComponent<Transform*>()->getVec3Scale().z;

				float* r3[3];
				r3[0] = &selected->getComponent<Transform*>()->getVec3Rot().x;
				r3[1] = &selected->getComponent<Transform*>()->getVec3Rot().y;
				r3[2] = &selected->getComponent<Transform*>()->getVec3Rot().z;

				ImGui::DragFloat3("Selected position", v3[0], .25f, -100000, 100000, "%.3f", 1.f);
				ImGui::DragFloat3("Selected rotation", r3[0], .25f, -100000, 100000, "%.3f", 1.f);
				ImGui::DragFloat3("Selected scale",    s3[0], .25f, -100000, 100000, "%.3f", 1.f);
				
				{ // submesh list
					std::vector<const char*> sub;
					for (int indd = 0; indd < selected->getComponent<Mesh*>()->getSubMeshCount(); indd++) {
						sub.push_back((*selected->getComponent<Mesh*>())[indd]->sMesh_name.c_str());
					}

					unsigned int lastt = list_box_sub;
					ImGui::ListBox("SubMeshes", &list_box_sub, &sub[0], sub.size());
					if (lastt != list_box_sub) {
						selected_sub = (*selected->getComponent<Mesh*>())[list_box_sub];
					}
					if (selected_sub != NULL) {
						// Submesh options
						ImGui::Checkbox("subMesh isActive", &selected_sub->isActive);
						float* vv3[3];
						vv3[0] = &selected_sub->s_transform->getVec3Pos().x;
						vv3[1] = &selected_sub->s_transform->getVec3Pos().y;
						vv3[2] = &selected_sub->s_transform->getVec3Pos().z;

						float* ss3[3];
						ss3[0] = &selected_sub->s_transform->getVec3Scale().x;
						ss3[1] = &selected_sub->s_transform->getVec3Scale().y;
						ss3[2] = &selected_sub->s_transform->getVec3Scale().z;

						float* rr3[3];
						rr3[0] = &selected_sub->s_transform->getVec3Rot().x;
						rr3[1] = &selected_sub->s_transform->getVec3Rot().y;
						rr3[2] = &selected_sub->s_transform->getVec3Rot().z;

						ImGui::DragFloat3("Selected-sub position", vv3[0], .1f, -100000, 100000, "%.3f", 1.f);
						ImGui::DragFloat3("Selected-sub rotation", rr3[0], .1f, -100000, 100000, "%.3f", 1.f);
						ImGui::DragFloat3("Selected-sub scale",    ss3[0], .1f, -100000, 100000, "%.3f", 1.f);
					}
				}
			}

			ImGui::End();
		}

		obj->draw(director);
		sniper->draw(director);

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
