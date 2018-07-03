#pragma once
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <GL\\glew.h>

#include "Director.h"
#include "Object.h"
#include "Component.h"
#include "Mesh.h"
#include "Transform.h"

class Object;

class subMesh {
public:
	subMesh();
	void Draw(Core::Director* director, Object* obj);

	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec3> Normals;
	std::vector<glm::vec3> Tangents;
	std::vector<glm::vec3> BiTangents;
	std::vector<glm::vec2> UVs;
	std::vector<unsigned int> Indices;
	std::vector<GLuint> VBOs;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	unsigned int drawSize;

	Transform* dad_transform;

};