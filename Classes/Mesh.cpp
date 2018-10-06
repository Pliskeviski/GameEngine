#include "Mesh.h"

#include <fstream>
#include <iostream>

Mesh::Mesh(const char* filename) {
	this->type = MESH;
	fileLoader(filename, meshes);
	for (subMesh* s : meshes)
		CreateBuffers(s);
}

void Mesh::Draw(Core::Director* director, Transform* parent) {
	for (subMesh* m : meshes)
		m->Draw(director, parent);
}

void Mesh::fileLoader(const char* filename, std::vector<subMesh*>& meshes) {
	FILE* fileB = fopen(filename, "rb");
	std::cout << filename << std::endl;
	assert(fileB);



	unsigned int m_meshes;
	fread(&m_meshes, sizeof(int), 1, fileB);
	fclose(fileB);

	meshes.reserve(m_meshes);
	for (unsigned int i = 0; i < m_meshes; i++) {
		std::string f_name(filename);
		f_name.append(std::to_string(i));
		std::cout << f_name << std::endl;
		
		FILE* file = fopen(f_name.c_str(), "rb");
		if (!file) {
			std::cout << "File problem\n";
			break;
		}

		subMesh* submesh = new subMesh;
		this->sMesh_cout++;
		submesh->sMesh_name = std::string("SubMesh " + std::to_string(i)).c_str();
		// Read info about Vertices size and Indices size
		glm::vec3 info; 
		fread(&info, sizeof(glm::vec3), 1, file);
		submesh->vertSize = info.x;
		submesh->drawSize = info.y;

		// Read info to check if the mesh has normals and UVs
		glm::vec3 info2;
		fread(&info2, sizeof(glm::vec3), 1, file);
		submesh->hasNormals = bool(info2.x);
		submesh->hasUVs     = bool(info2.y);

		// Read position
		glm::vec3 pos;
		fread(&pos, sizeof(glm::vec3), 1, file);
		submesh->s_transform = new Transform({ pos.x, pos.y, pos.z });
		
		// Vertices
		submesh->Vertices = new glm::vec3[info.x];
		fread(&submesh->Vertices[0], sizeof(glm::vec3), info.x, file);
		std::cout << "Vertices loaded\n";

		// Normals
		submesh->Normals = new glm::vec3[info.x];
		fread(&submesh->Normals[0], sizeof(glm::vec3), info.x, file);
		std::cout << "Normals loaded\n";
		
		// UVs
		if (submesh->hasUVs) {
			submesh->hasUVs = true;
			submesh->UVs = new glm::vec2[info.x];
			fread(&submesh->UVs[0], sizeof(glm::vec2), info.x, file);
			std::cout << "UVs loaded\n";

			for (unsigned int g = 0; g < info.x; g++) {
				submesh->UVs[g].y *= -1;
			}
		}

		// Indices
		submesh->Indices = new unsigned short[info.y];
		fread(&submesh->Indices[0], sizeof(unsigned short), info.y, file);
		std::cout << "Indices loaded\n";

		meshes.push_back(submesh);
		fclose(file);
	}
}

void Mesh::CreateBuffers(subMesh* s_mesh) {

	// Gen VAO
	glGenVertexArrays(1, &s_mesh->VAO);
	glBindVertexArray(s_mesh->VAO);

	// Add buffers 
	s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->vertSize * sizeof(glm::vec3), 3, &s_mesh->Vertices[0], GL_STATIC_DRAW));

	if (s_mesh->hasUVs)
	s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->vertSize * sizeof(glm::vec2), 2, &s_mesh->UVs[0],      GL_STATIC_DRAW));

	if (s_mesh->hasNormals)
	s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->vertSize * sizeof(glm::vec3), 3, &s_mesh->Normals[0],  GL_STATIC_DRAW));

	if (!s_mesh->Tangents.empty())
	s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->Tangents.size()   * sizeof(glm::vec3), 3,  &s_mesh->Tangents[0], GL_STATIC_DRAW));

	if (!s_mesh->BiTangents.empty())
	s_mesh->VBOs.push_back(genVBO(s_mesh, s_mesh->BiTangents.size() * sizeof(glm::vec3), 3, &s_mesh->BiTangents[0], GL_STATIC_DRAW));

	glGenBuffers(1, &s_mesh->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_mesh->drawSize * sizeof(unsigned short), &s_mesh->Indices[0], GL_STATIC_DRAW);
}

unsigned int Mesh::getSubMeshCount(){
	return this->sMesh_cout;
}

subMesh* Mesh::operator[](unsigned int index) {
	return this->meshes[index];
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

GLuint Mesh::genIntVBO(subMesh* m_mesh, GLsizeiptr size, GLint dataSize, const void* data, GLenum usage) {

	glBindVertexArray(m_mesh->VAO);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);

	glEnableVertexAttribArray(m_mesh->VBOs.size());
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribIPointer(m_mesh->VBOs.size(), dataSize, GL_INT, 0, 0);

	return buffer;
}