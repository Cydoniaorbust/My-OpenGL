#include "Study/GLEnvironment.h"

GLEnvironment::GLEnvironment() : 
	w(1440),
	h(900),
	lastX(w / 2.),
	lastY(h / 2.),
	delta(0),
	time_last(0) {}

void GLEnvironment::Init_GLFW(int a, int b) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, a);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, b);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}
void GLEnvironment::Init_Win(const char* name) {
	Win = glfwCreateWindow(w, h, name, nullptr, nullptr);
	if (Win == nullptr) 
		throw new MYERROR("GLFW window is not initialized!\n");
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
void GLEnvironment::Init_GLAD() {
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
	GLfloat xoffset = xpos - lastX;
	lastX = xpos;
	return xoffset;
}
GLfloat GLEnvironment::MouseY(double ypos) {
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
	lastY = ypos;
	return yoffset;
}
void GLEnvironment::UpdateFrames() {
	GLfloat time_current = glfwGetTime();
	delta = time_current - time_last;
	time_last = time_current;
}