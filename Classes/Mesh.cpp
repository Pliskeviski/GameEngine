#include "Mesh.h"

#include <iostream>

Mesh::Mesh(const char* filename) {
	this->type = MESH;
	fileLoader(filename, meshes);
	for (subMesh* s : meshes)
		CreateBuffers(s);
}

void Mesh::setObject(Object* obj) {
	this->obj = obj;
}

void Mesh::Draw(Core::Director* director) {
	for (subMesh* m : meshes)
		m->Draw(director, this->obj);
}

void Mesh::fileLoader(const char* filename, std::vector<subMesh*>& meshes) {

	FILE* file = fopen(filename, "r+");
	
	assert(file);
	
	unsigned int n_meshes = 0;
	
	char line[128];
	
	fgets(NULL, NULL, file);
	fgets(line, sizeof(line), file);
	fscanf(file, "m %u", &n_meshes);
	
	std::cout << n_meshes << std::endl;

	meshes.reserve(n_meshes);
	for (unsigned int i = 0; i < n_meshes; i++) {
		subMesh* submesh = new subMesh;
	
		fgets(line, sizeof(line), file);
		unsigned int vertices_s, indices_s;
		fscanf(file, "v_ %u i_ %u", &vertices_s, &indices_s);
		std::cout << vertices_s << " " << indices_s << std::endl;

		submesh->Vertices.reserve(vertices_s);
		for (unsigned int i = 0; i < vertices_s; i++) {
			glm::vec3 vertices;
			fgets(line, sizeof(line), file);
			fscanf(file, "v %f %f %f", &vertices.x, &vertices.y, &vertices.z);
			submesh->Vertices.push_back(vertices);
			std::cout << vertices.x << " " << vertices.y << " " << vertices.z << std::endl;
		}
	
		submesh->UVs.reserve(vertices_s);
		for (unsigned int i = 0; i < vertices_s; i++) {
			fgets(line, sizeof(line), file);
			if (line[0] != 'u') break;
			glm::vec2 uvs;
			fscanf(file, "u %f %f", &uvs.x, &uvs.y);
			submesh->UVs.push_back(uvs);
		}
	
		submesh->Normals.reserve(vertices_s);
		for (unsigned int i = 0; i < vertices_s; i++) {
			fgets(line, sizeof(line), file);
			if (line[0] != 'n') break;
			glm::vec3 vertices;
			fscanf(file, "n %f %f %f", &vertices.x, &vertices.y, &vertices.z);
			std::cout << vertices.x << std::endl;
			submesh->Normals.push_back(vertices);
		}
	
		submesh->Indices.reserve(indices_s);
		for (unsigned int i = 0; i < indices_s; i++) {
			unsigned int indice;
			fgets(line, sizeof(line), file);
			fscanf(file, "i %u", &indice);
			submesh->Indices.push_back(indice + 1);
		}
	
		meshes.push_back(submesh);
	}
	fclose(file);
}


void Mesh::CreateBuffers(subMesh* s_mesh) {

	// Gen VAO
	glGenVertexArrays(1, &s_mesh->VAO);
	glBindVertexArray(s_mesh->VAO);

	// Add buffers 
	s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->Vertices.size() * sizeof(glm::vec3), 3, &s_mesh->Vertices[0], GL_STATIC_DRAW));

	if (!s_mesh->UVs.empty())
		s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->UVs.size() * sizeof(glm::vec2), 2, &s_mesh->UVs[0], GL_STATIC_DRAW));

	if (!s_mesh->Normals.empty())
		s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->Normals.size() * sizeof(glm::vec3), 3, &s_mesh->Normals[0], GL_STATIC_DRAW));

	if (!s_mesh->Tangents.empty())
		s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->Tangents.size() * sizeof(glm::vec3), 3, &s_mesh->Tangents[0], GL_STATIC_DRAW));

	if (!s_mesh->BiTangents.empty())
		s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->BiTangents.size() * sizeof(glm::vec3), 3, &s_mesh->BiTangents[0], GL_STATIC_DRAW));

	// Add element buffer
	if (!s_mesh->Indices.empty()) {
		glGenBuffers(1, &s_mesh->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_mesh->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_mesh->Indices.size() * sizeof(unsigned short), &s_mesh->Indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_mesh->EBO);
		s_mesh->drawSize = s_mesh->Indices.size();
	}
}

// Return a new VBO for each call
GLuint Mesh::genVBO(subMesh* m_mesh, GLsizeiptr size, GLint dataSize, const void* data, GLenum usage) {

	glBindVertexArray(m_mesh->VAO);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);

	glEnableVertexAttribArray(m_mesh->VBOs.size());
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(m_mesh->VBOs.size(), dataSize, GL_FLOAT, GL_FALSE, 0, 0);

	return buffer;
}