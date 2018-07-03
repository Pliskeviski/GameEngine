#include "GridFloor.h"

Grid::Grid(size_t size_x, size_t size_z) : gridSize_x(size_x), gridSize_z(size_z), Active(true) {

	pl::string vertex("Shaders\\grid.vertexshader");
	pl::string fragment("Shaders\\grid.fragmentshader");
	shader = new Shader(vertex, fragment);
	Create();
}

void Grid::Create() {
	
	point.clear(); // clear the point vector

	if (gridSize_x < 1 || gridSize_z < 1)
		return;

	GLfloat spacing = 1.f;
	GLfloat x = this->gridSize_x;
	GLfloat z = this->gridSize_z;
	for (GLfloat i = -this->gridSize_z; i < this->gridSize_z + 1; i += spacing) {
		point.push_back(glm::vec3(x, 0.f, i));
		point.push_back(glm::vec3(x * -1, 0.f, i));
	}

	for (GLfloat i = -this->gridSize_x; i < this->gridSize_x + 1; i += spacing) {
		point.push_back(glm::vec3(i, 0.f, z));
		point.push_back(glm::vec3(i, 0.f, z * -1));
	}

	glDeleteBuffers(1, &t_VBO); // Delete before creating any new
	glDeleteVertexArrays(1, &t_VAO);
	glGenBuffers(1, &t_VBO);
	glGenVertexArrays(1, &t_VAO);
	glBindVertexArray(t_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, t_VBO);
	glBufferData(GL_ARRAY_BUFFER, this->point.size() * sizeof(glm::vec3), &this->point[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

}

void Grid::Draw(Camera* camera, glm::vec2 res) {
	if (!Active)
		return;
	this->shader->Use();
	glm::mat4 Projection = glm::perspective(camera->getFov(), res.x / res.y, 0.1f, 1000.0f);
	glm::mat4 View = camera->getViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(this->shader->getID(), "View"), 1, GL_FALSE, glm::value_ptr(View));
	glUniformMatrix4fv(glGetUniformLocation(this->shader->getID(), "Projection"), 1, GL_FALSE, glm::value_ptr(Projection));
	glBindVertexArray(this->t_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->t_VBO);
	this->shader->setVec3("color", glm::vec3(0.2f));
	glDrawArrays(GL_LINES, 0, this->point.size());

	
	glBindVertexArray(0);
	this->shader->UnBind();
}

void Grid::setActive(bool active) { 
	this->Active = active;
}

bool Grid::isActive() {
	return this->Active;
}

void Grid::setGridSize(size_t size_x, size_t size_z) {
	this->gridSize_x = size_x;
	this->gridSize_z = size_z;
	Create();
}

void Grid::setGridSizeX(size_t size_x) {
	this->gridSize_x = size_x;
	Create();
}

void Grid::setGridSizeY(size_t size_z) {
	this->gridSize_z = size_z;
	Create();
}

void Grid::flipActive() {
	Active ^= true;
}