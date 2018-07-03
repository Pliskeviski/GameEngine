#pragma once
#include <vector>
#include <glm\\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GL\\glew.h>

#include "..\\Classes\Shader\Shader.h"
#include "..\\Classes\Camera.h"

class Grid {
public:
	Grid(size_t size_x, size_t size_z);
	void setGridSize(size_t size_x, size_t size_z);
	void setGridSizeX(size_t size_x);
	void setGridSizeY(size_t size_z);
	void Draw(Camera* camera, glm::vec2 res);
	void setActive(bool active);
	void flipActive();
	bool isActive();
private:
	void Create();

	std::vector<glm::vec3> point;

	unsigned int t_VAO;
	unsigned int t_VBO;

	int gridSize_x;
	int gridSize_z;
	Shader* shader;

	bool Active;
};