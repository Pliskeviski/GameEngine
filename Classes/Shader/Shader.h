#pragma once
#include <vector>

#include <GL\glew.h>

#include <glm\glm.hpp>

#include "..\\Pliskeviski\String.h"

#include "stringLoader.hpp"


class Shader {
public:
	/*
		@ new Shader
	*/
	Shader(pl::string& vertexPath, pl::string& fragmentPath);

	/*
		@ set vector 3 in shader
	*/
	void setVec3(const char* name, float v1, float v2, float v3);

	/*
		@ set vector 3 in shader
	*/
	void setVec3(const char* name, glm::vec3 v);

	/*
		@ set float value in shader
	*/
	void setFloat(const char* name, float v);

	/*
		@ use this shader
	*/
	void Use();

	/*
		@ Unbind this shader
	*/
	void UnBind();

	/*
		@ get shader id
	*/
	GLuint getID();

private:
	GLuint id_shader;
};