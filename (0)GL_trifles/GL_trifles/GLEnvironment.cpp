#include "GLEnvironment.h"

#include <iostream>

#pragma region Ctor/Dtor

GLEnvironment::GLEnvironment() : Width(0), Height(0), LastX(0), LastY(0), Delta(0), TimeLast(0) {}
GLEnvironment::GLEnvironment(int W, int H) : GLEnvironment() {
	Width = W;
	Height = H;
	LastX = Width / 2.;
	LastY = Height / 2.;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);	
}
GLEnvironment::~GLEnvironment() {}

#pragma endregion

#pragma region Set/Get

GLFWwindow* GLEnvironment::GetWin() const noexcept { return Win; }
int GLEnvironment::GetWidth() const noexcept { return Width; }
int GLEnvironment::GetHeight() const noexcept { return Height; }
GLfloat GLEnvironment::GetDelta() const noexcept { return Delta; }

#pragma endregion

#pragma region Methods

void GLEnvironment::InitWin(const char* name) {
	Win = glfwCreateWindow(Width, Height, name, nullptr, nullptr);
	if (!Win) throw new MYERROR("GLFW window is not initialized!\n");
	glfwMakeContextCurrent(Win);
}
void GLEnvironment::Callback_Set(
	GLFWframebuffersizefun buffer,
	GLFWkeyfun key,
	GLFWcursorposfun mouse,
	GLFWscrollfun scroll) {
	glfwSetFramebufferSizeCallback(Win, buffer);
	glfwSetKeyCallback(Win, key);
	glfwSetCursorPosCallback(Win, mouse);
	glfwSetScrollCallback(Win, scroll);
	glfwSetInputMode(Win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void GLEnvironment::InitGLAD() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw new MYERROR("Failed to initialize GLAD\n");
}
void GLEnvironment::ApplyTests() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}
GLfloat GLEnvironment::MouseX(double xpos) {
	GLfloat xoffset = xpos - LastX;
	LastX = xpos;
	return xoffset;
}
GLfloat GLEnvironment::MouseY(double ypos) {
	GLfloat yoffset = LastY - ypos;  // Reversed since y-coordinates go from bottom to left
	LastY = ypos;
	return yoffset;
}
void GLEnvironment::UpdateFrames() {
	GLfloat TimeCurrent = glfwGetTime();
	Delta = TimeCurrent - TimeLast;
	TimeLast = TimeCurrent;
}

#pragma endregion

#pragma region Copy

#pragma endregion