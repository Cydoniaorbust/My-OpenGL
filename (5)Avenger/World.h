#pragma once

#include "Manager.h"
#include "Camera.h"

#include <math.h>

#define HERO Data.Hero
#define ENEMY Data.Foe

class World {
public:
	static GLboolean Keys[1024];
	GLEnvironment Env;
	manager Data;
	Camera Cam;
	
	GLfloat Width;
	GLfloat Height;
	GLfloat Aspect;

	GLfloat Delta = 0;
	GLuint FramesNumber = 0;
	GLfloat FramesTotalTime = 0;
		
	void FrameCounter() {
		FramesNumber++;
		FramesTotalTime += Delta;
		if (FramesTotalTime >= 1.0) {
			system("cls");
			
			std::cout << FramesNumber << " fps\n";
			
			std::cout << std::fixed << std::setprecision(0) << "["
				<< Cam.Position.x << "]:["
				<< Cam.Position.y << "]:["
				<< Cam.Position.z << "]" << std::endl;
			
			FramesNumber = 0;
			FramesTotalTime -= 1.0;
		}
	}
	void ProcessInput() {
		if (Keys[GLFW_KEY_E]) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (Keys[GLFW_KEY_R]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		if (Keys[GLFW_KEY_W]) {
			HERO.Move(FORWARD, Delta);
			if (manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
				//HERO.Move(BACKWARD, Delta);
				HERO.Collide();
				ENEMY.Collide();
			}
			else {
				HERO.UnCollide();
				ENEMY.UnCollide();
			}
		}
		if (Keys[GLFW_KEY_S]) {
			HERO.Move(BACKWARD, Delta);
			if (manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
				//HERO.Move(FORWARD, Delta);
				HERO.Collide();
				ENEMY.Collide();
			}
			else {
				HERO.UnCollide();
				ENEMY.UnCollide();
			}
		}
		if (Keys[GLFW_KEY_A]) {
			HERO.Move(LEFT, Delta);
			if (manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
				//HERO.Move(RIGHT, Delta);
				HERO.Collide();
				ENEMY.Collide();
			}
			else {
				HERO.UnCollide();
				ENEMY.UnCollide();
			}
		}
		if (Keys[GLFW_KEY_D]) {
			HERO.Move(RIGHT, Delta);
			if (manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
				//HERO.Move(LEFT, Delta);
				HERO.Collide();
				ENEMY.Collide();
			}
			else {
				HERO.UnCollide();
				ENEMY.UnCollide();
			}
		}

		if (Keys[GLFW_MOUSE_BUTTON_1]) {
			if (Data.shots.size() < 100) {
				std::cout << "Another one\n";
				Data.shots.push_back(Bullet());
			}
			else std::cout << "Enough\n";
			//check if buffer is full
				//create Bullet
				//set timer
				//send Bullet
				//check collisions
				//delete Bullet
		}
	}	
	void MoveBullets() {
		for (int i = 0; i < 100; i++) { if (Data.shots[i] != nullptr) Data.shots[i].Collide(); }
		//for (auto iter : Data.shots) {}//330 95 
	}

	void Update() {
		Delta = Env.UpdateDelta();
		FrameCounter();

		glfwPollEvents();
		ProcessInput();
		MoveBullets();

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Draw() {
		HERO.Draw(Cam.Position, Cam.View, Aspect);
		ENEMY.Draw(Cam.Position, Cam.View, Aspect);
		Data.BImage.Draw(Cam.View, Aspect);

		Env.Swap();
	}

	void Loop() {
		while (!glfwWindowShouldClose(Env.GetWin())) {
			Update();
			Draw();
		}

		glfwTerminate();
	}

	static void CallbackFramebufferSize(GLFWwindow* Win, int width, int height) { glViewport(0, 0, width, height); }
	static void CallbackMouseButton(GLFWwindow* Win, int button, int action, int mods) {
		if (button >= 0 && button < 10)
			if (action == GLFW_PRESS) Keys[button] = true;
			else
				if (action == GLFW_RELEASE) Keys[button] = false;
	}
	static void CallbackKey(GLFWwindow* Win, int key, int scancode, int action, int mode) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)	glfwSetWindowShouldClose(Win, GL_TRUE);
		if (key >= 30 && key < 350)
			if (action == GLFW_PRESS) Keys[key] = true;
			else
				if (action == GLFW_RELEASE) Keys[key] = false;
	}

	World() : Cam(vec3(0, 10, 0)) {}
	World(GLfloat width, GLfloat height) : World() {
		Width = width;
		Height = height;
		Aspect = Width / Height;

		Env.InitWin(width, height, "OpenGL");
		Env.CallbackSet(CallbackFramebufferSize, CallbackMouseButton, CallbackKey, nullptr, nullptr);
		Env.InitGLAD();
		Env.ApplyTests();

		Data.BImage.SetBack();
		HERO.SetPlayer();
		ENEMY.SetEnemy(0.7);
	}

	World(const World &) = delete;
	World& operator=(const World &) = delete;
	World(World &&) = delete;
	World& operator=(World &&) = delete;
};

