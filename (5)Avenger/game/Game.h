#pragma once

#include <Source.h>

#include "ResManager.h"

class Game {
public:
	GLfloat Width;
	GLfloat Height;
	ResManager Manager;
	vec3 LightAmb;
	vec3 LightDir;
	vec3 LightDifDir;
	vec3 LightDifSpot;

	GLFWwindow* GetWin() const noexcept;

	void Init();
	void ProcessInput();
	void Update();
	void Draw(CcharP, GLboolean);
	void Swap();
	
	static GLEnvironment Env;
	static Camera Cam;
	static GLboolean Keys[1024];

	static void CallbackFramebufferSize(GLFWwindow*, int, int);
	static void CallbackMouse(GLFWwindow*, double, double);
	static void CallbackScroll(GLFWwindow*, double, double);		
	
	Game();
	Game(GLfloat width, GLfloat height);
	~Game();

	Game(const Game &) = delete;
	Game& operator=(const Game &) = delete;
	Game(Game &&) = delete;
	Game& operator=(Game &&) = delete;	
};