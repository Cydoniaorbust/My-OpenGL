#include "Game.h"
#include "Res_Manager.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;


Game Ranger(SCREEN_WIDTH, SCREEN_HEIGHT);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) Ranger.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE) Ranger.Keys[key] = GL_FALSE;
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

//void processInput(GLFWwindow *window) {
//	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) if (LightAmb.x < 1) LightAmb += 0.05;
//	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) if (LightAmb.x > 0) LightAmb -= 0.05;
//	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) if (LightDifDir.x < 1) LightDifDir += 0.05;
//	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) if (LightDifDir.x > 0) LightDifDir -= 0.05;
//	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) if (LightDifSpot.x < 1) LightDifSpot += 0.05;
//	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) if (LightDifSpot.x > 0) LightDifSpot -= 0.05;
//
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) exit(0);
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, DTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, DTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, DTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, DTime);
//	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//}

class error : public std::exception {
	const char* data;
public:
	error(const char* _data) : data(_data) {};
	const char* what() { return data; };
};

void OpenGL() {
	try {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ranger", nullptr, nullptr);
		if (window == NULL) throw new error("GLFW window is not initialized!\n");
		glfwMakeContextCurrent(window);

		glfwSetKeyCallback(window, key_callback);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw new error("GLAD is not initialized!\n");
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SpriteRenderer Renderer;
		Ranger.Init(Renderer);

		GLfloat deltaTime = 0.0f;
		GLfloat lastFrame = 0.0f;

		Ranger.State = GAME_ACTIVE;

		while (!glfwWindowShouldClose(window)) {
			GLfloat currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glfwPollEvents();
			Ranger.ProcessInput(deltaTime);

			Ranger.Update(deltaTime);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Ranger.Render(Renderer);

			glfwSwapBuffers(window);
		}

		Ranger.Manager.Clear();

		glfwTerminate();
	}
	catch (error* e) {
		std::cerr << e->what() << std::endl;
		delete e;
		terminate();
	}
}

int main(int argc, char *argv[]) {
	OpenGL();

	return 0;
}