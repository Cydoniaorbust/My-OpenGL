#include <Source.h>

#pragma comment (lib, "Assimp/x86/assimp.lib")

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <Stb/stb_image.h>
#endif

#include "Model.h"

#include <iomanip>
#include <time.h>

GLEnvironment Env;
Camera Cam(vec3(0, 3, 0));
vec3 LightAmb(1), LightDir(-0.2f, -1.0f, -0.3f), LightDifDir(1), LightDifSpot(1);

void callback_framebuffer_size(GLFWwindow* Win, int width, int height) {
	glViewport(0, 0, width, height);
}
void callback_mouse(GLFWwindow* Win, double xpos, double ypos) {
	Cam.ProcessMouseMovement(Env.MouseX(xpos), Env.MouseY(ypos));
}
void callback_scroll(GLFWwindow* Win, double xoffset, double yoffset) {
	Cam.ProcessMouseScroll(yoffset);
}
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) if (LightAmb.x < 1) LightAmb += 0.05;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) if (LightAmb.x > 0) LightAmb -= 0.05;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) if (LightDifDir.x < 1) LightDifDir += 0.05;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) if (LightDifDir.x > 0) LightDifDir -= 0.05;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) if (LightDifSpot.x < 1) LightDifSpot += 0.05;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) if (LightDifSpot.x > 0) LightDifSpot -= 0.05;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) exit(0);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) Cam.ProcessKeyboard(FORWARD, Env.GetDelta());
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) Cam.ProcessKeyboard(BACKWARD, Env.GetDelta());
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) Cam.ProcessKeyboard(LEFT, Env.GetDelta());
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) Cam.ProcessKeyboard(RIGHT, Env.GetDelta());
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void DrawAxes(uint shader, mat4 view, mat4 projection) {
	GLfloat	Axis[] = {
		1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,-1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,-1.0f};
//Assigning
	GLuint VAO_a, VBO_a;
	glGenVertexArrays(1, &VAO_a);
	glGenBuffers(1, &VBO_a);
	glBindVertexArray(VAO_a);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_a);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Axis), Axis, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
//Shader
	Shader::Use(shader);
	Shader::SetMat4(shader, "view", view);
	Shader::SetMat4(shader, "projection", projection);
	Shader::SetMat4(shader, "model", mat4());
//Drawing
	glLineWidth(3.f);
	glBindVertexArray(VAO_a);
	Shader::SetVec3(shader, "_color", 1.0, 0.0, 0.0);
	glDrawArrays(GL_LINES, 0, 2);
	Shader::SetVec3(shader, "_color", 0.0, 1.0, 0.0);
	glDrawArrays(GL_LINES, 2, 2);
	Shader::SetVec3(shader, "_color", 0.0, 0.0, 1.0);
	glDrawArrays(GL_LINES, 4, 2);
	glBindVertexArray(0);
//Cleaning
	glDeleteVertexArrays(1, &VAO_a);
	glDeleteBuffers(1, &VBO_a);
}
void DrawScene(uint shader, mat4 view, mat4 projection, Model model) {
	Shader::Use(shader);
	Shader::SetMat4(shader, "view", view);
	Shader::SetMat4(shader, "projection", projection);
	mat4 _model;
	_model = rotate(_model, radians(90.0f), vec3(-1.0, 0.0, 0.0));
	_model = scale(_model, vec3(0.01));
	Shader::SetMat4(shader, "model", _model);
	//Basic
	Shader::SetFloat(shader, "material.shininess", 500);
	Shader::SetVec3(shader, "ViewPos", Cam.Position);
	Shader::SetVec3(shader, "Ambient", LightAmb);
	//Directional
	Shader::SetVec3(shader, "DirLight.direction", LightDir);
	Shader::SetVec3(shader, "DirLight.diffuse", LightDifDir);
	//SpotLight
	Shader::SetVec3(shader, "SpotLight.position", Cam.Position);
	Shader::SetVec3(shader, "SpotLight.direction", Cam.GetFront());
	Shader::SetVec3(shader, "SpotLight.diffuse", LightDifSpot);
	Shader::SetFloat(shader, "SpotLight.inner", cos(radians(12.5f)));
	Shader::SetFloat(shader, "SpotLight.outer", cos(radians(15.0f)));
	model.Draw(shader);
}

void OpenGL() {
	try {
		Env.InitWin(800, 600, "OpenGL");
		Env.CallbackSet(callback_framebuffer_size, nullptr, callback_mouse, callback_scroll);
		Env.InitGLAD();
		Env.ApplyTests();
	//Preparation begins
		uint 
			AxisShader = Shader::CreateProgram("Res/Axis.vert", "Res/Axis.frag"),
			ObjShader = Shader::CreateProgram("Res/Shader.vert", "Res/Shader.frag");
		Model Model("D:/Google/Resources/Model/runner/runner.obj");
		GLuint nbFrames = 0;
		GLfloat LastTime = (GLfloat)glfwGetTime();
	//Main loop
		while (!glfwWindowShouldClose(Env.GetWin())) {
		//Start
			processInput(Env.GetWin());
		//Scene and Camera
			Env.UpdateFrames();

			mat4 view = Cam.GetViewMatrix();
			mat4 projection = perspective(radians(Cam.Zoom), (GLfloat)Env.GetWidth() / (GLfloat)Env.GetHeight(), 0.1f, 1000.0f);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Drawing			
			DrawAxes(AxisShader, view, projection);
			DrawScene(ObjShader, view, projection, Model);
		//FPS counter
			nbFrames++;
			if (GLfloat(glfwGetTime()) - LastTime >= 1.0) {
				std::cout << nbFrames << " fps\n";
				nbFrames = 0;
				LastTime += 1.0;
			}
		//Finish
			glfwSwapBuffers(Env.GetWin());
			glfwPollEvents();
		}
	//Cleaning
		glfwTerminate();
	}
	catch (MYERROR* e) {
		std::cerr << e->what() << std::endl;
		delete e;
		std::terminate();
	}
}

int main(int argc, char * argv[]) {
	srand((GLuint)time(NULL));

	OpenGL();
	
	return 0;
}