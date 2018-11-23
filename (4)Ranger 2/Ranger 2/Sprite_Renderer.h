#pragma once

#include "Study/Texture.h"
#include "Study/Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpriteRenderer {
private:
	Shader shader;
	GLuint quadVAO;	
public:
	SpriteRenderer();
	SpriteRenderer(Shader);
	~SpriteRenderer();

	void initRenderData();
	void DrawSprite(Texture2D, glm::vec2, glm::vec2, GLfloat, glm::vec3);
};