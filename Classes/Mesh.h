#pragma once
#include <vector>
#include <cassert>

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "Director.h"
#include "subMesh.h"
#include "Object.h"

class subMesh;
class Object;

class Mesh : public Component {
public:
	Mesh(const char* filename);
	void Draw(Core::Director* director);
	void setObject(Object* obj);
	void CreateBuffers(subMesh* s_mesh);
private:
	GLuint genVBO(subMesh* m_mesh, GLsizeiptr size, GLint dataSize, const void* data, GLenum usage);
	std::vector<subMesh*> meshes;
	void fileLoader(const char* filename, std::vector<subMesh*>& meshes);
	Object* obj;
};