#include "Shader.h"

void Shader::Use			(GLuint id) {
	glUseProgram(id);
}
void Shader::CreateShader	(const char* path, GLuint shader, GLuint program) {
	std::ifstream fin(path, std::ifstream::binary);

	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, fin.beg);

	char * code = new char[length + 1];

	fin.read(code, length);
	code[length] = '\0';
	fin.close();

	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	glAttachShader(program, shader);

	delete[] code;
	glDeleteShader(shader);
}
GLuint Shader::CreateProgram(const char* pathV, const char* pathF, const char* pathG) {
	GLuint id = glCreateProgram();

	CreateShader(pathV, glCreateShader(GL_VERTEX_SHADER), id);
	CreateShader(pathF, glCreateShader(GL_FRAGMENT_SHADER), id);
	if (pathG != nullptr)
		CreateShader(pathG, glCreateShader(GL_GEOMETRY_SHADER), id);

	glLinkProgram(id);

	return id;
}

void Shader::SetBool		(GLuint id, const std::string & name, bool val) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)val); 
}
void Shader::SetInt			(GLuint id, const std::string & name, int val) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), val); 
}
void Shader::SetFloat		(GLuint id, const std::string & name, float val) {
	glUniform1f(glGetUniformLocation(id, name.c_str()), val); 
}

void Shader::SetVec2		(GLuint id, const std::string & name, const glm::vec2 & vec) {
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]); 
}
void Shader::SetVec3		(GLuint id, const std::string & name, const glm::vec3 & vec) {
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]); 
}
void Shader::SetVec4		(GLuint id, const std::string & name, const glm::vec4 & vec) {
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]); 
}

void Shader::SetVec2		(GLuint id, const std::string & name, float x, float y) {
	glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}
void Shader::SetVec3		(GLuint id, const std::string & name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
void Shader::SetVec4		(GLuint id, const std::string & name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w); 
}

void Shader::SetMat2		(GLuint id, const std::string & name, const glm::mat2 & arr) {
	glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &arr[0][0]);
}
void Shader::SetMat3		(GLuint id, const std::string & name, const glm::mat3 & arr) {
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &arr[0][0]);
}
void Shader::SetMat4		(GLuint id, const std::string & name, const glm::mat4 & arr) {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &arr[0][0]);
}