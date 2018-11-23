#pragma once

#include "Res_Manager.h"
#include "Sprite_renderer.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

enum GameState { GAME_ACTIVE, GAME_MENU, GAME_WIN };

class Game {
public:
	GameState	State;
	GLboolean	Keys[1024];
	GLuint		Width, Height;
	Res_Manager Manager;
	
	Game();
	Game(GLuint width, GLuint height);
	~Game();
	
	void Init(SpriteRenderer &);
	
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render(SpriteRenderer);
};