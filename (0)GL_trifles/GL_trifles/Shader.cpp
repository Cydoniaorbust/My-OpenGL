#include "Shader.h"

#include <fstream>

#pragma region Ctor/Dtor

Shader::Shader() :
	Id(glCreateProgram()),
	ShaderV(glCreateShader(GL_VERTEX_SHADER)),
	ShaderF(glCreateShader(GL_FRAGMENT_SHADER)),
	ShaderG(glCreateShader(GL_GEOMETRY_SHADER)) {}
Shader::Shader(const Shader & t) : Shader() {
	Id = t.GetId();
	ShaderV = t.GetShaderV();
	ShaderF = t.GetShaderF();
	ShaderG = t.GetShaderG();

	glLinkProgram(Id);
}
Shader::Shader(Shader &&t) : Shader(t) {
	t.SetId(0); 
	t.SetShaderV(0);
	t.SetShaderF(0);
	t.SetShaderG(0);
}
Shader::~Shader() {
	glDeleteShader(ShaderV);
	glDeleteShader(ShaderF);
	glDeleteShader(ShaderG);
}

Shader::Shader(const char* _vPath, const char* _fPath) : Shader() {
	CreateShader(_vPath, ShaderV);
	CreateShader(_fPath, ShaderF);

	glLinkProgram(Id);
}
Shader::Shader(const char* _vPath, const char* _fPath, const char* _gPath) : Shader() {
	CreateShader(_vPath, ShaderV);
	CreateShader(_fPath, ShaderF);
	CreateShader(_gPath, ShaderG);

	glLinkProgram(Id);
}

#pragma endregion

#pragma region Set/Get

uint Shader::GetId() const noexcept { return Id; }
uint Shader::GetShaderV() const noexcept { return ShaderV; }
uint Shader::GetShaderF() const noexcept { return ShaderF; }
uint Shader::GetShaderG() const noexcept { return ShaderG; }

void Shader::SetId(uint v) { Id = v; }
void Shader::SetShaderV(uint v) { ShaderV = v; }
void Shader::SetShaderF(uint v) { ShaderF = v; }
void Shader::SetShaderG(uint v) { ShaderG = v; }

void Shader::SetBool(const_str &name, bool value) {
	glUniform1i(glGetUniformLocation(Id, name.c_str()), (int)value); 
}
void Shader::SetInt(const_str &name, int value) { 
	glUniform1i(glGetUniformLocation(Id, name.c_str()), value); 
}
void Shader::SetFloat(const_str &name, float value) { 
	glUniform1f(glGetUniformLocation(Id, name.c_str()), value); 
}

void Shader::SetVec2(const_str &name, const glm::vec2 &v) {
	glUniform2fv(glGetUniformLocation(Id, name.c_str()), 1, &v[0]); 
}
void Shader::SetVec3(const_str &name, const glm::vec3 &v) {
	glUniform3fv(glGetUniformLocation(Id, name.c_str()), 1, &v[0]); 
}
void Shader::SetVec4(const_str &name, const glm::vec4 &v) {
	glUniform4fv(glGetUniformLocation(Id, name.c_str()), 1, &v[0]); 
}

void Shader::SetVec2(const_str &name, float x, float y) {
	glUniform2f(glGetUniformLocation(Id, name.c_str()), x, y); 
}
void Shader::SetVec3(const_str &name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(Id, name.c_str()), x, y, z);
}
void Shader::SetVec4(const_str &name, float x, float y, float z, float w) { 
	glUniform4f(glGetUniformLocation(Id, name.c_str()), x, y, z, w); 
}

void Shader::SetMat2(const_str &name, const glm::mat2 &a) { 
	glUniformMatrix2fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &a[0][0]);
}
void Shader::SetMat3(const_str &name, const glm::mat3 &a) { 
	glUniformMatrix3fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &a[0][0]);
}
void Shader::SetMat4(const_str &name, const glm::mat4 &a) {
	glUniformMatrix4fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &a[0][0]);
}

#pragma endregion

#pragma region Methods

void Shader::Use() const { glUseProgram(Id); }
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

	glAttachShader(Id, _shader);
}

#pragma endregion

#pragma region Copy

void Shader::Swap(Shader &t) {
	std::swap(t.Id, Id);
	std::swap(t.ShaderV, ShaderV);
	std::swap(t.ShaderF, ShaderF);
	std::swap(t.ShaderG, ShaderG);
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