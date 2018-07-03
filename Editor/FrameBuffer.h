#pragma once
#include <assert.h>
#include <GL\glew.h>

#include "..\\Classes\Director.h"

class FrameBuffer {
public:
	FrameBuffer(Core::Director* director);

	void Bind();
	void Unbind();
	void Delete();
	GLuint getBuffer();

private:
	Core::Director* director;
	GLuint renderTexture;
	GLuint framebuffername;
};