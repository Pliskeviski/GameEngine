#pragma once
#include <vector>
#include <cassert>

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "Director.h"
#include "subMesh.h"
#include "Object.h"
#include "Transform.h"

class subMesh;
class Object;

class Mesh : public Component {
public:
	Mesh(const char* filename);
	void Draw(Core::Director* director, Transform* parent);
	void CreateBuffers(subMesh* s_mesh);

	/*
		@ Returns submesh for index
	*/
	subMesh* operator[](unsigned int index);
private:
	GLuint genVBO(subMesh* m_mesh, GLsizeiptr size, GLint dataSize, const void* data, GLenum usage);
	std::vector<subMesh*> meshes;
	void fileLoader(const char* filename, std::vector<subMesh*>& meshes);
};