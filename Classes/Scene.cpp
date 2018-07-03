#include "Scene.h"

Scene::Scene() {
}

void Scene::newCamera(float fov = 45.f, glm::vec3 position = glm::vec3(0.f)) {
	s_cameras.push_back(new Camera(position, fov));
}

Camera* Scene::getActiveCamera() {
	return active_camera;
}

std::vector<Camera*> Scene::getCameras() {
	return s_cameras;
}
