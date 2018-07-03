#include "Shader.h"

Shader::Shader(pl::string& vertexPath, pl::string& fragmentPath) {

	assert(vertexPath.size() && vertexPath.size()); // location must be valid

	pl::string vertex = load(vertexPath.c_str());
	pl::string fragment = load(fragmentPath.c_str());

	GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile vertex shaders
	const char* vertexShaderSource = vertex.c_str();
	glShaderSource(v_shader, 1, &vertexShaderSource, NULL);
	glCompileShader(v_shader);
	// Check Vertex Shader
	glGetShaderiv(v_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(v_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(v_shader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// fragment shader
	const char* fragmentShaderSource = fragment.c_str();
	glShaderSource(f_shader, 1, &fragmentShaderSource, NULL);
	glCompileShader(f_shader);
	// Check Vertex Shader
	glGetShaderiv(f_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(f_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(f_shader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, v_shader);
	glAttachShader(shaderID, f_shader);
	glLinkProgram(shaderID);

	// Check the program
	glGetProgramiv(shaderID, GL_LINK_STATUS, &Result);
	glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(shaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(shaderID, v_shader);
	glDetachShader(shaderID, f_shader);

	glDeleteShader(v_shader);
	glDeleteShader(f_shader);

	this->id_shader = shaderID;
}

void Shader::setVec3(const char* name, float v1, float v2, float v3) {
	glUseProgram(this->id_shader);
	glUniform3f(glGetUniformLocation(this->id_shader, name), v1, v2 ,v3);
}

void Shader::setVec3(const char* name, glm::vec3 v) {
	glUseProgram(this->id_shader);
	glUniform3f(glGetUniformLocation(this->id_shader, name), v.x, v.y, v.z);
}

void Shader::setFloat(const char* name, float v) {
	glUseProgram(this->id_shader);
	glUniform1f(glGetUniformLocation(this->id_shader, name), v);
}

void Shader::Use() {
	glUseProgram(this->id_shader);
}

void Shader::UnBind() {
	glUseProgram(0);
}

GLuint Shader::getID() {
	return this->id_shader;
}
