#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <string>

using std::string;
using CcharP = const char*;

class ResManager {
private:
	std::map<string, uint> VAOs;
	std::map<string, uint> Shaders;
	std::map<string, uint> Textures;

public:
	uint GetVAO(string);
	void SetVAO(string, const GLfloat*, int, GLboolean);

	uint GetShader(string);
	void SetShader(string, CcharP, CcharP, CcharP);

	uint GetTexture(string);
	void SetTexture(string, CcharP, GLboolean);
	uint LoadTexture(CcharP, GLboolean);

	ResManager() {}
	~ResManager();

	ResManager(const ResManager &) = delete;
	ResManager& operator=(const ResManager &) = delete;
	ResManager(ResManager &&) = delete;
	ResManager& operator=(ResManager &&) = delete;
};