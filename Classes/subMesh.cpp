#include "subMesh.h"


subMesh::subMesh() {
}

subMesh::~subMesh() {
	free(this->Vertices);
	free(this->Indices);
}

void subMesh::Draw(Core::Director* director, Transform* dad) {
	director->getShader()->Use();

	glBindVertexArray(this->VAO);
	for (unsigned int j = 0; j < this->VBOs.size(); j++) {
		glEnableVertexAttribArray(j);
	}

	//GLuint MatrixID = glGetUniformLocation(director->getShader()->getID(), "MVP");

	GLuint ViewID = glGetUniformLocation(director->getShader()->getID(), "view");
	GLuint ProjectionID = glGetUniformLocation(director->getShader()->getID(), "projection");
	GLuint ModelID = glGetUniformLocation(director->getShader()->getID(), "model");

	glm::mat4 Projection = glm::perspective(director->getCamera()->getFov(), (GLfloat)director->getCamera()->c_Width / (GLfloat)director->getCamera()->c_Height, 0.1f, 1000.0f);
	glm::mat4 View    = director->getCamera()->getViewMatrix();
	glm::mat4 Model   = glm::translate(glm::mat4(1.f), dad->getPosition() + this->s_transform->getPosition());
	glm::mat4 ModelRX =    glm::rotate(glm::mat4(1.f), this->s_transform->getRotationX() + dad->getRotationX(), glm::vec3(1.0f, .0f, .0f));
	glm::mat4 ModelRY =    glm::rotate(glm::mat4(1.f), this->s_transform->getRotationY() + dad->getRotationY(), glm::vec3(.0f, 1.0f, .0f));
	glm::mat4 ModelRZ =    glm::rotate(glm::mat4(1.f), this->s_transform->getRotationZ() + dad->getRotationZ(), glm::vec3(.0f, .0f, 1.0f));
	glm::mat4 ModelScale = glm::scale(glm::mat4(1.f), dad->getScale() * this->s_transform->getScale());
	glm::mat4 ModelRotation = ModelRX * ModelRY * ModelRZ;
	Model *= ModelRotation * ModelScale;
	//glm::mat4 MVP = Projection * View * Model;

	glUniformMatrix4fv(ModelID, 1, GL_FALSE, glm::value_ptr(Model));
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, glm::value_ptr(View));
	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, glm::value_ptr(Projection));

	// TODO mat4 Scale, rotation

	//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind all textures
	// TODO add more properties like vec3 for each texture type and merge them in shader
	if (!this->s_textures.empty()) {
		for (unsigned int i = 0; i < s_textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			std::string name;
			if (s_textures[i]->getType() == TYPE_DIFFUSE)
				name = "albedoMap";
			if (s_textures[i]->getType() == TYPE_NORMAL)
				name = "normalMap";
			if (s_textures[i]->getType() == TYPE_METALLIC)
				name = "metallicMap";
			if (s_textures[i]->getType() == TYPE_ROUGHNESS)
				name = "roughnessMap";
			if (s_textures[i]->getType() == TYPE_AO)
				name = "aoMap";

			glUniform1i(glGetUniformLocation(director->getShader()->getID(), name.c_str()), i);
			glBindTexture(GL_TEXTURE_2D, s_textures[i]->getID());
		}
	}

	glDrawElements(GL_TRIANGLES, this->drawSize, GL_UNSIGNED_SHORT, (void*)Indices[0]);
	for (int j = 0; j < this->VBOs.size(); j++) {
		glDisableVertexAttribArray(j);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void subMesh::addTexture(std::string path, TextureType type) {
	Texture* t = new Texture(path, type);
	this->s_textures.push_back(t);
}
