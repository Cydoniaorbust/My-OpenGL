#pragma once

#include "ResManager.h"

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

class Game {
public:
	GLfloat Width;
	GLfloat Height;
	ResManager Manager;

	static GLEnvironment Env;
	static Camera Cam;
	static GLboolean Keys[1024];
	
	GLFWwindow* GetWin() const noexcept { return Env.GetWin(); }

	void Init() {
		GLfloat	Axis[] = {
			10.0f, 0.0f, 0.0f,-10.0f, 0.0f, 0.0f,
			0.0f, 10.0f, 0.0f, 0.0f,-10.0f, 0.0f,
			0.0f, 0.0f, 10.0f, 0.0f, 0.0f,-10.0f
		};
		GLfloat Vertices[] = {
			0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 1.0f, 1.0f
		};

		Manager.SetVAO("axis", Axis, 18, 1);
		Manager.SetVAO("sprite", Vertices, 24, 0);

		Manager.SetShader("axis",
			"D:/Google/Resources/Shaders/Vert/Simp.vert",
			"D:/Google/Resources/Shaders/Frag/Axis.frag",
			nullptr);
		Manager.SetShader("sprite",
			"D:/Google/Resources/Shaders/Vert/Sprite.vert",
			"D:/Google/Resources/Shaders/Frag/TexOnly.frag",
			nullptr);

		Manager.SetTexture("sprite", "D:/Google/Resources/Tex/awesome.png");
	}
	void ProcessInput() {
		for (int i = 0; i < 257; i++) {
			if (glfwGetKey(Env.GetWin(), i) == GLFW_PRESS)
				switch (i) {
				case GLFW_KEY_ESCAPE: { exit(0); } break;
				case GLFW_KEY_W: { Cam.ProcessKeyboard(FORWARD, Env.GetDelta()); } break;
				case GLFW_KEY_S: { Cam.ProcessKeyboard(BACKWARD, Env.GetDelta()); } break;
				case GLFW_KEY_A: { Cam.ProcessKeyboard(LEFT, Env.GetDelta()); } break;
				case GLFW_KEY_D: { Cam.ProcessKeyboard(RIGHT, Env.GetDelta()); } break;
				case GLFW_KEY_E: { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); } break;
				case GLFW_KEY_R: { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); } break;
				}
		}
	}
	void Update() {
		Env.UpdateFrames();
		glfwPollEvents();
		ProcessInput();

		system("cls");

		std::cout << std::fixed << std::setprecision(0) << "["
			<< Cam.Position.x << "]:["
			<< Cam.Position.y << "]:["
			<< Cam.Position.z << "]" << std::endl;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Draw(const char* name, GLboolean axis) {
		GLuint vao = Manager.GetVAO(name);
		GLuint shader = Manager.GetShader(name);

		Shader::Use(shader);
		Shader::SetMat4(shader, "view", Cam.GetViewMatrix());
		Shader::SetMat4(shader, "projection", glm::perspective(radians(Cam.Zoom), Width / Height, 0.1f, 1000.0f));
		Shader::SetMat4(shader, "model", mat4());
		glBindVertexArray(vao);
		if (!axis) {
			Texture tex = Manager.GetTexture(name);
			Shader::SetInt(shader, "texture", 0);
			glActiveTexture(GL_TEXTURE0);
			tex.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		else {
			glLineWidth(3.f);
			Shader::SetVec3(shader, "_color", 1.0, 0.0, 0.0); glDrawArrays(GL_LINES, 0, 2);
			Shader::SetVec3(shader, "_color", 0.0, 1.0, 0.0); glDrawArrays(GL_LINES, 2, 2);
			Shader::SetVec3(shader, "_color", 0.0, 0.0, 1.0); glDrawArrays(GL_LINES, 4, 2);
		}
		glBindVertexArray(0);
	}
	void Swap() { glfwSwapBuffers(Env.GetWin()); }
	
	static void CallbackFramebufferSize(GLFWwindow* Win, int width, int height) { glViewport(0, 0, width, height); }
	static void CallbackMouse(GLFWwindow* Win, double xpos, double ypos) { Cam.ProcessMouseMovement(Env.MouseX(xpos), Env.MouseY(ypos)); }
	static void CallbackScroll(GLFWwindow* Win, double xoffset, double yoffset) { Cam.ProcessMouseScroll(yoffset); }

	Game(GLfloat width, GLfloat height) {
		Width = width;
		Height = height;

		Env.InitWin(width, height, "OpenGL");
		Env.CallbackSet(CallbackFramebufferSize, nullptr, CallbackMouse, CallbackScroll);
		Env.InitGLAD();
		Env.ApplyTests();

		Init();
	}
	~Game() {}

	Game(const Game &) = delete;
	Game& operator=(const Game &) = delete;
	Game(Game &&) = delete;
	Game& operator=(Game &&) = delete;	
};

