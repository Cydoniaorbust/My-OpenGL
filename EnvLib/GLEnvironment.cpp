#include "GLEnvironment.h"

GLFWwindow* GLEnvironment::GetWin() const noexcept { return win; }

GLfloat GLEnvironment::MouseX(double _xpos) {
	GLfloat xoffset = _xpos - lastX;
	lastX = _xpos;
	return xoffset;
}
GLfloat GLEnvironment::MouseY(double _ypos) {
	GLfloat yoffset = lastY - _ypos;  // Reversed since y-coordinates go from bottom to left
	lastY = _ypos;
	return yoffset;
}

GLfloat GLEnvironment::CountTPS() {
	return tick.rateCheck / frame.updateFreq;
}
GLfloat GLEnvironment::CountFPS() {
	return frame.count / frame.updateFreq;
}

void GLEnvironment::UpdateDelta() {
	timeLast = timeCurrent;
	QueryPerformanceCounter(&timeCurrent);
	delta = (timeCurrent.QuadPart - timeLast.QuadPart) / (double)frequency.QuadPart;
}

void GLEnvironment::InitWin(int _width, int _height, const char* _name) {
	aspect = _width / _height;
	lastX = _width / 2.;
	lastY = _height / 2.;

	win = glfwCreateWindow(_width, _height, _name, nullptr, nullptr);
	glfwSetWindowPos(win, 550, 50);
	if (!win) throw new Error("GLFW window is not initialized!\n");
	glfwMakeContextCurrent(win);
}

void GLEnvironment::CallbackFramebufferSize(GLFWframebuffersizefun _func) {
	glfwSetFramebufferSizeCallback(win, _func);
}
void GLEnvironment::CallbackKey(GLFWkeyfun _func) {
	glfwSetKeyCallback(win, _func);
}
void GLEnvironment::CallbackMouseButton(GLFWmousebuttonfun _func) {
	glfwSetMouseButtonCallback(win, _func);
}
void GLEnvironment::CallbackCursorPos(GLFWcursorposfun _func) {
	glfwSetCursorPosCallback(win, _func);
}
void GLEnvironment::CallbackScroll(GLFWscrollfun _func) {
	glfwSetScrollCallback(win, _func);
}

void GLEnvironment::SetInputMode() {	
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GLEnvironment::InitGLAD() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw new Error("Failed to initialize GLAD\n");
}
void GLEnvironment::ApplyTests() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void GLEnvironment::Swap() { 
	glfwSwapBuffers(win);
}
void GLEnvironment::Loop(
	std::function<void()> __Update, 
	void __Draw(glm::vec3, glm::mat4, GLfloat, bool),
	glm::vec3 position, glm::mat4 view, 
	void __ConsoleInfo()) {
	while (!glfwWindowShouldClose(win)) {
		tick.ResetCount();

		while (tick.UpdatesNotTooFast()) {
			glfwPollEvents();
			UpdateDelta();
			__Update();
			tick.MakeStep(delta);
		}

		//_manager.Draw(cam.position, cam.view, aspect, drawHits);
		__Draw(position, view, aspect, drawHits);
		Swap();
		frame.MakeStep();

		if (frame.TimeToUpdate(tick.time)) {
			if (__ConsoleInfo) __ConsoleInfo();
			tick.CheckReset();
			frame.ResetCount();
		}

		//interpolation = float( GetTickCount() + tick.skip - tick.last ) / float( tick.skip );
	}

	glfwTerminate();
}

GLEnvironment::GLEnvironment() : lastX(0), lastY(0), delta(0.0f), drawHits(false) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&timeCurrent);
}
GLEnvironment::~GLEnvironment() {}