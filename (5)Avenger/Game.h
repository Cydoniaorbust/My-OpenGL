#pragma once

#include "Manager.h"
#include "Camera.h"

class Game {
public:
	GLfloat Width;
	GLfloat Height;
	GLfloat Aspect;

	GLfloat Second = 0;
	GLuint Frames = 0;
	
	manager Data;

	static GLEnvironment Env;
	static Camera Cam;
	static GLboolean Keys[1024];

	GLFWwindow* GetWin() const noexcept { return Env.GetWin(); }

	void ProcessInput() {
		for (int i = 0; i < 257; i++) {
			if (glfwGetKey(Env.GetWin(), i) == GLFW_PRESS)
				switch (i) {
				case GLFW_KEY_ESCAPE: { exit(0); } break;
				case GLFW_KEY_W: { Data.Hero.Model.MoveZ(Env.GetDelta());	Data.Hitbox.Model.MoveZ(Env.GetDelta()); } break;
				case GLFW_KEY_S: { Data.Hero.Model.MoveZ(-Env.GetDelta());	Data.Hitbox.Model.MoveZ(-Env.GetDelta()); } break;
				case GLFW_KEY_A: { Data.Hero.Model.MoveX(Env.GetDelta());	Data.Hitbox.Model.MoveX(Env.GetDelta()); } break;
				case GLFW_KEY_D: { Data.Hero.Model.MoveX(-Env.GetDelta());	Data.Hitbox.Model.MoveX(-Env.GetDelta()); } break;
				case GLFW_KEY_E: { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); } break;
				case GLFW_KEY_R: { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); } break;
				}
		}
	}
	void Update() {
		Env.UpdateFrames();
		glfwPollEvents();
		ProcessInput();

		Frames++;
		Second += Env.GetDelta();
		if (Second >= 1.0) {
			system("cls");
			std::cout << Frames << " fps\n";
			Frames = 0;

			std::cout << std::fixed << std::setprecision(0) << "["
				<< Cam.Position.x << "]:["
				<< Cam.Position.y << "]:["
				<< Cam.Position.z << "]" << std::endl;
			Second -= 1.0;
		}		

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Draw() {
		Data.Hero.Draw(Cam.Position, Cam.View, Aspect);
		Data.Enemy.Draw(Cam.Position, Cam.View, Aspect);
		Data.BImage.Draw(Cam.View, Aspect);
		Data.Hitbox.Draw(Cam.View, Aspect);
	}
	void Swap() { glfwSwapBuffers(Env.GetWin()); }

	static void CallbackFramebufferSize(GLFWwindow* Win, int width, int height) { glViewport(0, 0, width, height); }

	Game(GLfloat width, GLfloat height) {
		Width = width;
		Height = height;
		Aspect = Width / Height;

		Env.InitWin(width, height, "OpenGL");
		Env.CallbackSet(CallbackFramebufferSize, nullptr, nullptr, nullptr);
		Env.InitGLAD();
		Env.ApplyTests();

		Data.BImage.SetBack();
		Data.Hero.SetPlayer();
		Data.Enemy.SetEnemy();
		Data.Hitbox.SetHit();
	}

	Game(const Game &) = delete;
	Game& operator=(const Game &) = delete;
	Game(Game &&) = delete;
	Game& operator=(Game &&) = delete;
};

