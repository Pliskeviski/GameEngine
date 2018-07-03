#include "subMesh.h"

subMesh::subMesh() {
}

void subMesh::Draw(Core::Director* director, Object* obj) {
	director->getShader()->Use();

	glBindVertexArray(this->VAO);
	for (unsigned int j = 0; j < this->VBOs.size(); j++) {
		glEnableVertexAttribArray(j);
	}

	GLuint ViewID = glGetUniformLocation(director->getShader()->getID(), "view");
	GLuint ProjectionID = glGetUniformLocation(director->getShader()->getID(), "projection");
	GLuint ModelID = glGetUniformLocation(director->getShader()->getID(), "model");

	glm::mat4 ProjectionMatrix = glm::perspective(45.f, (GLfloat)director->getScreenWidth() / (GLfloat)director->getScreenHeight(), 0.1f, 1000.0f);
	glm::mat4 ViewMatrix = director->getCamera()->getViewMatrix();
	glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.f), obj->getComponent<Transform*>()->getPosition());
	glm::mat4 ModelRX = glm::rotate(glm::mat4(1.f), obj->getComponent<Transform*>()->getRotationX(), glm::vec3(1.0f, .0f, .0f));
	glm::mat4 ModelRY = glm::rotate(glm::mat4(1.f), obj->getComponent<Transform*>()->getRotationY(), glm::vec3(.0f, 1.0f, .0f));
	glm::mat4 ModelRZ = glm::rotate(glm::mat4(1.f), obj->getComponent<Transform*>()->getRotationZ(), glm::vec3(.0f, .0f, 1.0f));
	glm::mat4 Model3 = glm::scale(glm::mat4(1.f), obj->getComponent<Transform*>()->getScale());
	glm::mat4 ModelRotation = ModelRX * ModelRY * ModelRZ;
	ModelMatrix *= ModelRotation * Model3;
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

	
	//glDrawElements(GL_TRIANGLES, this->drawSize, GL_UNSIGNED_SHORT, &Indices[0]);
	glDrawElements(GL_TRIANGLES, this->drawSize, GL_UNSIGNED_SHORT, (void*)0);
	for (int j = 0; j < this->VBOs.size(); j++) {
		glDisableVertexAttribArray(j);
	}
}
