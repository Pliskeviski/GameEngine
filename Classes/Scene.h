#pragma once
#include <vector>

#include <glm\\glm.hpp>

#include "Camera.h"

class Scene {
public:
	/*
		@ new scene
	*/
	Scene();

	/*
		@ new camera
		@ camera fov = 45.f (you can specify it)
		@ position = 0.0 (you can specify it)
	*/
	void newCamera(float fov, glm::vec3 position);

	/*
		@ get active camera in scene
	*/
	 Camera* getActiveCamera();

	 /*
		@ get all cameras in scene
		@ vector
	 */
	 std::vector<Camera*> getCameras();

private:
	std::vector<Camera*> s_cameras;
	Camera* active_camera;
};