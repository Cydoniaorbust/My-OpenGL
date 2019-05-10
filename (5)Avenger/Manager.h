#pragma once

#include "Entity.h"
#include "PhysObject.h"
#include "Unit.h"

#include <map>
#include <iomanip>

class manager {
private:
	/*
	entity* back;
	
	entity* player;
	entity* player_hit;

	std::map<string, entity*> enemies;
	std::map<string, entity*> enemies_hit;
	*/

public:
	background BImage;
	player Hero;
	enemy Enemy;
	hitbox Hitbox;
	
	/*
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
	*/

	manager() {}
	~manager() {
		/*
		for (auto iter : VAOs) glDeleteVertexArrays(1, &iter.second);
		for (auto iter : Shaders) glDeleteProgram(iter.second);
		for (auto iter : Textures) glDeleteTextures(1, &iter.second.Id);
		*/
	}

	manager(const manager &) = delete;
	manager& operator=(const manager &) = delete;
	manager(manager &&) = delete;
	manager& operator=(manager &&) = delete;
};