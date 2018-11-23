#include "Study/Shader.h"

#include <fstream>

#pragma region Ctor/Dtor
Shader::Shader() :
	id(glCreateProgram()),
	vShader(glCreateShader(GL_VERTEX_SHADER)),
	fShader(glCreateShader(GL_FRAGMENT_SHADER)),
	gShader(glCreateShader(GL_GEOMETRY_SHADER)) {}
Shader::Shader(const Shader & t) : 
	id(t.GetId()), 
	vShader(t.GetvShader()),
	fShader(t.GetfShader()),
	gShader(t.GetgShader()) {}
Shader::Shader(Shader &&t) : Shader(t) {
	t.SetId(0);
	t.SetvShader(0);
	t.SetfShader(0);
	t.SetgShader(0);
}
Shader::Shader(const char* _vPath, const char* _fPath) : Shader() {
	CreateShader(_vPath, vShader);
	CreateShader(_fPath, fShader);

	glLinkProgram(id);
}
Shader::Shader(const char* _vPath, const char* _fPath, const char* _gPath) : Shader() {
	CreateShader(_vPath, vShader);
	CreateShader(_fPath, fShader);
	CreateShader(_gPath, gShader);

	glLinkProgram(id);
}
Shader::~Shader() {
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteShader(gShader);
}
#pragma endregion
#pragma region Set/Get
uint Shader::GetId() const noexcept { return id; }
uint Shader::GetvShader() const noexcept { return vShader; }
uint Shader::GetfShader() const noexcept { return fShader; }
uint Shader::GetgShader() const noexcept { return gShader; }

void Shader::SetId(uint v) { id = v; }
void Shader::SetvShader(uint v) { vShader = v; }
void Shader::SetfShader(uint v) { fShader = v; }
void Shader::SetgShader(uint v) { gShader = v; }

void Shader::SetBool(const_str &name, bool value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); 
}
void Shader::SetInt(const_str &name, int value) { 
	glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
}
void Shader::SetFloat(const_str &name, float value) { 
	glUniform1f(glGetUniformLocation(id, name.c_str()), value); 
}

void Shader::SetVec2(const_str &name, const glm::vec2 &v) {
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &v[0]); 
}
void Shader::SetVec3(const_str &name, const glm::vec3 &v) {
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &v[0]); 
}
void Shader::SetVec4(const_str &name, const glm::vec4 &v) {
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &v[0]); 
}

void Shader::SetVec2(const_str &name, float x, float y) {
	glUniform2f(glGetUniformLocation(id, name.c_str()), x, y); 
}
void Shader::SetVec3(const_str &name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
void Shader::SetVec4(const_str &name, float x, float y, float z, float w) { 
	glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w); 
}

void Shader::SetMat2(const_str &name, const glm::mat2 &a) { 
	glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &a[0][0]);
}
void Shader::SetMat3(const_str &name, const glm::mat3 &a) { 
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &a[0][0]);
}
void Shader::SetMat4(const_str &name, const glm::mat4 &a) {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &a[0][0]);
}
#pragma endregion
#pragma region Methods
void Shader::Use() const { glUseProgram(id); }
void Shader::CreateShader(const char* _path, uint _shader) {
	std::ifstream fin(_path, std::ifstream::binary);

	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, fin.beg);

	char * code = new char[length + 1];

	fin.read(code, length);
	code[length] = '\0';

	glShaderSource(_shader, 1, &code, nullptr);
	glCompileShader(_shader);

	delete[] code;

	fin.close();

	glAttachShader(id, _shader);
}
#pragma endregion
#pragma region Copy
void Shader::Swap(Shader &t) {
	std::swap(t.id, id);
	std::swap(t.vShader, vShader);
	std::swap(t.fShader, fShader);
	std::swap(t.gShader, gShader);
}
Shader& Shader::operator=(const Shader &t) {
	if (this != &t) Shader(t).Swap(*this);
	return *this;
}
Shader& Shader::operator=(Shader &&t) {
	Swap(t);
	return *this;
}
#pragma endregion