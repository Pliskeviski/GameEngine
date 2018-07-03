#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(Core::Director* director) : director(director) {
	// Render to texture
	GLuint framebuffername = 0;
	glGenFramebuffers(1, &framebuffername);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffername);

	// the texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);

	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	// empty image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->director->getScreenWidth(), this->director->getScreenHeight(), 0, GL_RGB, GL_UNSIGNED_INT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// The depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->director->getScreenWidth(), this->director->getScreenHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	this->framebuffername = framebuffername;
	this->renderTexture = renderedTexture;

	//assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE);
}

void FrameBuffer::Bind() {
	glBindTexture(GL_TEXTURE_2D, this->renderTexture);
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffername);
}

void FrameBuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Delete() {
	glDeleteFramebuffers(1, &framebuffername);
}

GLuint FrameBuffer::getBuffer()
{
	return this->framebuffername;
}
