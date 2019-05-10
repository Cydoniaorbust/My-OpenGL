#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <string>

using std::string;

class ResManager {
private:
	std::map<string, GLuint> VAOs;
	std::map<string, GLuint> Shaders;
	std::map<string, Texture> Textures;

public:
	GLuint GetVAO(string name) {
		return VAOs[name]; 
	}
	void SetVAO(string name, const GLfloat* vertices, int size, GLboolean axis) {
		glGenVertexArrays(1, &VAOs[name]);
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindVertexArray(VAOs[name]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(vertices), vertices, GL_STATIC_DRAW);

		if (axis) glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		else glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDeleteBuffers(1, &vbo);
	}

	GLuint GetShader(string name) {
		return Shaders[name]; 
	}
	void SetShader(string name, const char* V, const char* F, const char* G = nullptr) { 
		Shaders[name] = Shader::CreateProgram(V, F, G); 
	}

	Texture GetTexture(string name) { 
		return Textures[name]; 
	}
	void SetTexture(string name, const char* file) { 
		Textures[name].LoadFromFile(file);
	}

	ResManager() {}
	~ResManager() {
		for (auto iter : VAOs) glDeleteVertexArrays(1, &iter.second);
		for (auto iter : Shaders) glDeleteProgram(iter.second);
		for (auto iter : Textures) glDeleteTextures(1, &iter.second.Id);
	}

	ResManager(const ResManager &) = delete;
	ResManager& operator=(const ResManager &) = delete;
	ResManager(ResManager &&) = delete;
	ResManager& operator=(ResManager &&) = delete;
};