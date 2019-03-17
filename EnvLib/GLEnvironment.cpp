#include "stdafx.h"
#include "GLEnvironment.h"

GLEnvironment::GLEnvironment() : Width(0), Height(0), Delta(0), LastX(0), LastY(0), TimeLast(0) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}
GLEnvironment::~GLEnvironment() {}

GLFWwindow* GLEnvironment::GetWin() const noexcept { return Win; }
int GLEnvironment::GetWidth() const noexcept { return Width; }
int GLEnvironment::GetHeight() const noexcept { return Height; }
float GLEnvironment::GetDelta() const noexcept { return Delta; }

void GLEnvironment::InitWin(int w, int h, const char* name) {
	Width = w;
	Height = h;
	LastX = Width / 2.;
	LastY = Height / 2.;

	Win = glfwCreateWindow(Width, Height, name, nullptr, nullptr);
	if (!Win) throw new MYERROR("GLFW window is not initialized!\n");
	glfwMakeContextCurrent(Win);
}
void GLEnvironment::CallbackSet(
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

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
float GLEnvironment::MouseX(double xpos) {
	float xoffset = xpos - LastX;
	LastX = xpos;
	return xoffset;
}
float GLEnvironment::MouseY(double ypos) {
	float yoffset = LastY - ypos;  // Reversed since y-coordinates go from bottom to left
	LastY = ypos;
	return yoffset;
}
void GLEnvironment::UpdateFrames() {
	float TimeCurrent = glfwGetTime();
	Delta = TimeCurrent - TimeLast;
	TimeLast = TimeCurrent;
}