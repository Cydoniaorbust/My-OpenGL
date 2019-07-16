#pragma once

#include "Manager.h"
#include "Camera.h"

#include <math.h>

#define HERO data.hero
#define ENEMY data.foe
#define BULLET data.shots

class World {
public:
	static GLboolean keys[1024];
	GLEnvironment env;
	Manager data;
	Camera cam;
	
	GLfloat width;
	GLfloat height;
	GLfloat aspect;

	GLfloat delta = 0;
	GLuint framesNumber = 0;
	GLfloat framesTotalTime = 0;
	
	void ConsoleInfo() {
		system("cls");

		std::cout << framesNumber / FPSUpdateRate << " fps\n";
		std::cout << "Delta: " << delta << std::endl;
		std::cout << "Shots active: " << data.CountShots() << std::endl;
		std::cout << std::fixed << std::setprecision(0) << "Player pos: ["
			<< HERO.GetHitbox()->GetPosition()[3][0] << "]:["
			<< HERO.GetHitbox()->GetPosition()[3][2] << "]\n";
	}
	void FrameCounter() {
		if (framesTotalTime >= FPSUpdateRate) {
			ConsoleInfo();
			
			ReleaseInputLock = true;
			framesNumber = 0;
			framesTotalTime -= FPSUpdateRate;
		}
	}
	void ProcessInput() {
		if (keys[GLFW_KEY_E]) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (keys[GLFW_KEY_R]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (keys[GLFW_KEY_T]) if (DrawHits) DrawHits = 0; else DrawHits = 1;

		if (keys[GLFW_KEY_W]) {
			HERO.Move(FORWARD, delta);
			if (Manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
				HERO.Move(BACKWARD, delta);
				HERO.Collide();
				ENEMY.Collide();
			}
			else {
				HERO.UnCollide();
				ENEMY.UnCollide();
			}
		}
		if (keys[GLFW_KEY_S]) {
			HERO.Move(BACKWARD, delta);
			if (Manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
				HERO.Move(FORWARD, delta);
				HERO.Collide();
				ENEMY.Collide();
			}
			else {
				HERO.UnCollide();
				ENEMY.UnCollide();
			}
		}
		if (keys[GLFW_KEY_A]) {
			HERO.Move(LEFT, delta);
			if (Manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
				HERO.Move(RIGHT, delta);
				HERO.Collide();
				ENEMY.Collide();
			}
			else {
				HERO.UnCollide();
				ENEMY.UnCollide();
			}
		}
		if (keys[GLFW_KEY_D]) {
			HERO.Move(RIGHT, delta);
			if (Manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
				HERO.Move(LEFT, delta);
				HERO.Collide();
				ENEMY.Collide();
			}
			else {
				HERO.UnCollide();
				ENEMY.UnCollide();
			}
		}

		if (keys[GLFW_MOUSE_BUTTON_1]) {
			if(ReleaseInputLock)
				for (int i = 0; i < BULLET.size(); i++) {
					if (!BULLET[i].GetState()) {
						float x = HERO.GetHitbox()->GetPosition()[3][0];
						float y = HERO.GetHitbox()->GetPosition()[3][2];
						BULLET[i].Activate(x, y);
						ReleaseInputLock = false;
						break;
					}
				}
		}
	}
	void MoveBullets() {
		for (int i = 0; i < BULLET.size(); i++) {
			if (BULLET[i].GetState()) { 
				BULLET[i].Move(FORWARD, delta * 4); 
				if (Manager::CollisionBetween(BULLET[i].GetHitbox(), ENEMY.GetHitbox())) {
					//BULLET[i].Deactivate();
					ENEMY.Collide();
				}
				else ENEMY.UnCollide();
				if (BULLET[i].GetHitbox()->OutOfBounds()) BULLET[i].Deactivate();
			}
		} 
	}

	void Update() {
		delta = env.UpdateDelta();
		framesNumber++;
		framesTotalTime += delta;

		FrameCounter();

		glfwPollEvents();
		ProcessInput();
		MoveBullets();

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Draw() {
		HERO.Draw(cam.Position, cam.View, aspect);
		ENEMY.Draw(cam.Position, cam.View, aspect);
		data.backImage.Draw(cam.View, aspect);
		for (int i = 0; i < BULLET.size(); i++)
			if (BULLET[i].GetState()) BULLET[i].Draw(cam.Position, cam.View, aspect);

		env.Swap();
	}

	void Loop() {
		while (!glfwWindowShouldClose(env.GetWin())) {
			Update();
			Draw();
		}

		glfwTerminate();
	}

	static void CallbackFramebufferSize(GLFWwindow* _win, int _width, int _height) { 
		glViewport(0, 0, _width, _height); 
	}
	static void CallbackMouseButton(GLFWwindow* _win, int _button, int _action, int _mods) {
		if (_button >= 0 && _button < 10)
			if (_action == GLFW_PRESS) keys[_button] = true;
			else
				if (_action == GLFW_RELEASE) keys[_button] = false;
	}
	static void CallbackKey(GLFWwindow* _win, int _key, int _scancode, int _action, int _mode) {
		/*
		int state = glfwGetKey(env.GetWin(), GLFW_KEY_E);
		if (state == GLFW_PRESS)
			activate_airship();
		*/

		if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
			glfwSetWindowShouldClose(_win, GL_TRUE);
		if (_key >= 30 && _key < 350)
			if (_action == GLFW_PRESS) keys[_key] = true;
			else
				if (_action == GLFW_RELEASE) keys[_key] = false;
	}

	World() : cam(vec3(0, 10, 0)) {}
	World(GLfloat _width, GLfloat _height) : World() {
		width = _width;
		height = _height;
		aspect = width / height;

		env.InitWin(_width, _height, "OpenGL");
		env.CallbackSet(CallbackFramebufferSize, CallbackMouseButton, CallbackKey, nullptr, nullptr);
		env.InitGLAD();
		env.ApplyTests();

		data.SetData();
	}

	World(const World &) = delete;
	World& operator=(const World &) = delete;
	World(World &&) = delete;
	World& operator=(World &&) = delete;
};