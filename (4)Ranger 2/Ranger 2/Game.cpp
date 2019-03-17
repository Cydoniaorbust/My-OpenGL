#include "Game.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

GLboolean Game::Keys[1024];
GLEnvironment Game::Env;
Camera Game::Cam(vec3(0, 3, 0));

void Game::Init() {
	GLfloat	Axis[] = {
		1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,-1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,-1.0f
	};
	GLfloat Vertices[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	Manager.SetVAO("axis", Axis, 18, 1);
	Manager.SetVAO("sprite", Vertices, 24, 0);
	
	Manager.SetShader("axis", "Res/Axis.vert", "Res/Axis.frag", nullptr);
	Manager.SetShader("sprite", "Res/Sprite.vert", "Res/Sprite.frag", nullptr);
	
	Manager.SetTexture("sprite", "Res/awesome.png");
}
void Game::ProcessInput() {
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
void Game::Update() {
	Env.UpdateFrames();
	glfwPollEvents();
	ProcessInput();

	std::cout << std::fixed << std::setprecision(0) << "["
		<< Cam.Position.x << "]:["
		<< Cam.Position.y << "]:["
		<< Cam.Position.z << "]" << std::endl;

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Game::Draw(CcharP name, GLboolean axis) {
	uint vao = Manager.GetVAO(name);
	uint shader = Manager.GetShader(name);

	Shader::Use(shader);
	Shader::SetMat4(shader, "view", Cam.GetViewMatrix());
	Shader::SetMat4(shader, "projection", glm::perspective(radians(Cam.Zoom), Width / Height, 0.1f, 1000.0f));
	Shader::SetMat4(shader, "model", mat4());
	glBindVertexArray(vao);
	if (!axis) {
		uint texture = Manager.GetTexture(name);
		Shader::SetInt(shader, "texture", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
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
void Game::Swap() { glfwSwapBuffers(Env.GetWin()); }

void Game::CallbackFramebufferSize(GLFWwindow* Win, int width, int height) { glViewport(0, 0, width, height); }
void Game::CallbackMouse(GLFWwindow* Win, double xpos, double ypos) { Cam.ProcessMouseMovement(Env.MouseX(xpos), Env.MouseY(ypos)); }
void Game::CallbackScroll(GLFWwindow* Win, double xoffset, double yoffset) { Cam.ProcessMouseScroll(yoffset); }

uint ResManager::GetVAO(string name) { return VAOs[name]; }
void ResManager::SetVAO(string name, const GLfloat* vertices, int size, GLboolean axis) {
	glGenVertexArrays(1, &VAOs[name]);
	uint vbo;
	glGenBuffers(1, &vbo);
	glBindVertexArray(VAOs[name]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(vertices), vertices, GL_STATIC_DRAW);

	if(axis) glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	else glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
}

uint ResManager::GetShader(string name) { return Shaders[name]; }
void ResManager::SetShader(string name, CcharP V, CcharP F, CcharP G = nullptr) { Shaders[name] = Shader::CreateProgram(V, F, G); }

uint ResManager::GetTexture(string name) { return Textures[name]; }
void ResManager::SetTexture(string name, CcharP file) { Textures[name] = LoadTexture(file); }
uint ResManager::LoadTexture(CcharP file) {
	uint texture;
	int width, height, chans = 4;

	unsigned char *image = stbi_load(file, &width, &height, &chans, 0);
	if (image) texture = Texture2D::Generate(image, width, height);
	else std::cout << "Texture failed to load at path: " << file << std::endl;

	stbi_image_free(image);
	return texture;
}

GLFWwindow* Game::GetWin() const noexcept { return Env.GetWin(); }

ResManager::~ResManager() {
	for (auto iter : VAOs) glDeleteVertexArrays(1, &iter.second);
	for (auto iter : Shaders) glDeleteProgram(iter.second);
	for (auto iter : Textures) glDeleteTextures(1, &iter.second);
}

Game::Game() : Width(0), Height(0), Manager() {}
Game::Game(GLfloat width, GLfloat height) : Game() {
	Width = width;
	Height = height;
	Env.InitWin(width, height, "OpenGL");
	Env.CallbackSet(CallbackFramebufferSize, nullptr, CallbackMouse, CallbackScroll);
	Env.InitGLAD();
	Env.ApplyTests();

	Init();
}
Game::~Game() {}



