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
#include "Texture.h"

class Object;

class subMesh {
public:
	subMesh();
	~subMesh();
	void Draw(Core::Director* director, Transform* dad);

	/*
		@ Add new texture to the subMesh
	*/
	void addTexture(std::string path, TextureType type);

	glm::vec3* Vertices;
	glm::vec3* Normals;
	std::vector<glm::vec3> Tangents; // TODO
	std::vector<glm::vec3> BiTangents; // TODO
	glm::vec2* UVs;
	unsigned short* Indices;
	std::vector<GLuint> VBOs;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	unsigned int vertSize;
	unsigned int drawSize;
	bool hasNormals;
	bool hasUVs;
	Transform* s_transform;
	std::vector<Texture*> s_textures;
	std::string sMesh_name;
	bool isActive;
};