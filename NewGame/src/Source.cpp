#include <Engine.h>

#include "Manager.h"

class Kamera {
public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::mat4 view;

	Kamera() {
		pos = glm::vec3(0, 10, 0);
		float a = glm::radians(180.0f);
		float b = glm::radians(-90.0f);
		front = normalize(glm::vec3(cos(a) * cos(b), sin(b), sin(a) * cos(b)));
		view = lookAt(pos, pos + front, normalize(cross(normalize(cross(front, glm::vec3(0, 1, 0))), front)));
	}
};

#include <functional>
#include <math.h>

GLboolean keys[1024];
GLEnvironment env;
Manager manager;
Kamera cam;

void ConsoleInfo() {
	system("cls");

	std::cout << std::fixed << std::setprecision(4);
	std::cout << "Ticks since system started: " << GetTickCount() << std::endl;
	std::cout << "TPS: " << env.CountTPS() << std::endl;
	std::cout << "FPS: " << env.CountFPS() << std::endl;
	std::cout << "Delta (time between updates): " << env.delta << std::endl;
	std::cout << "Shots active: " << manager.CountShots() << std::endl;
	std::cout << "Player pos: [" 
		<< manager.hero.GetHitbox()->GetPosition()[3][0] << "]:["
		<< manager.hero.GetHitbox()->GetPosition()[3][2] << "]\n";
}
void Update() {
	Player &HERO = manager.hero;
	Enemy &ENEMY = manager.foe;

	if (keys[GLFW_KEY_E]) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (keys[GLFW_KEY_R]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (keys[GLFW_KEY_T]) env.drawHits ? env.drawHits = 0 : env.drawHits = 1;

	if (keys[GLFW_KEY_W]) {
		HERO.Move(Movement::FORWARD, env.delta);
		if (Manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
			HERO.Move(Movement::BACKWARD, env.delta);
			HERO.Collide();
			ENEMY.Collide();
		}
		else {
			HERO.UnCollide();
			ENEMY.UnCollide();
		}
	}
	if (keys[GLFW_KEY_S]) {
		HERO.Move(Movement::BACKWARD, env.delta);
		if (Manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
			HERO.Move(Movement::FORWARD, env.delta);
			HERO.Collide();
			ENEMY.Collide();
		}
		else {
			HERO.UnCollide();
			ENEMY.UnCollide();
		}
	}
	if (keys[GLFW_KEY_A]) {
		HERO.Move(Movement::LEFT, env.delta);
		if (Manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
			HERO.Move(Movement::RIGHT, env.delta);
			HERO.Collide();
			ENEMY.Collide();
		}
		else {
			HERO.UnCollide();
			ENEMY.UnCollide();
		}
	}
	if (keys[GLFW_KEY_D]) {
		HERO.Move(Movement::RIGHT, env.delta);
		if (Manager::CollisionBetween(HERO.GetHitbox(), ENEMY.GetHitbox())) {
			HERO.Move(Movement::LEFT, env.delta);
			HERO.Collide();
			ENEMY.Collide();
		}
		else {
			HERO.UnCollide();
			ENEMY.UnCollide();
		}
	}

	if (keys[GLFW_MOUSE_BUTTON_1]) {
		//if(ReleaseInputLock) 
		keys[GLFW_MOUSE_BUTTON_1] = false;
		for (int i = 0; i < manager.shots.size(); i++) {
			if (!manager.shots[i].GetState()) {
				float x = HERO.GetHitbox()->GetPosition()[3][0];
				float y = HERO.GetHitbox()->GetPosition()[3][2];
				manager.shots[i].Activate(x, y);
				//ReleaseInputLock = false;
				break;
			}
		}
	}

	manager.MoveBullets(env.delta);
}
void Draw(glm::vec3 _pos, glm::mat4 _view, GLfloat _aspect, bool _drawHits) {
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	manager.hero.Draw(_pos, _view, _aspect, _drawHits);
	manager.foe.Draw(_pos, _view, _aspect, _drawHits);
	manager.backImage.Draw(_view, _aspect);
	for (int i = 0; i < manager.shots.size(); i++)
		if (manager.shots[i].GetState())
			manager.shots[i].Draw(_pos, _view, _aspect, _drawHits);
}

void CallbackFramebufferSize(GLFWwindow* _win, int _width, int _height) {
	glViewport(0, 0, _width, _height);
}
void CallbackMouseButton(GLFWwindow* _win, int _button, int _action, int _mods) {
	if (_button >= 0 && _button < 10)
		if (_action == GLFW_PRESS) {// && timer == 0) {
			keys[_button] = true;
			//timer = 100;
		}
		else
			if (_action == GLFW_RELEASE) keys[_button] = false;
}
void CallbackKey(GLFWwindow* _win, int _key, int _scancode, int _action, int _mode) {
	if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
		glfwSetWindowShouldClose(_win, GL_TRUE);
	if (_key >= 30 && _key < 350)
		if (_action == GLFW_PRESS) keys[_key] = true;
		else
			if (_action == GLFW_RELEASE) keys[_key] = false;
}

int main(int argc, char * argv[]) {
	try {
		/*
		std::function<void(int, int)> foo = [](int a, int b) { std::cout << a; };
		foo(3, 5);
		auto bar = std::bind(
			Manager::Draw, manager, 
			std::placeholders::_1, 
			std::placeholders::_2, 
			std::placeholders::_3, 
			std::placeholders::_4);			
		*/

		env.InitWin(800, 800, "OpenGL");

		env.CallbackFramebufferSize(CallbackFramebufferSize);
		env.CallbackMouseButton(CallbackMouseButton);
		env.CallbackKey(CallbackKey);
		env.SetInputMode();

		env.InitGLAD();
		env.ApplyTests();

		manager.SetData();

		
		env.Loop(Update, Draw, cam.pos, cam.view, ConsoleInfo);
	}
	catch (Error* _e) {
		std::cout << _e->GetData() << std::endl;
		delete _e;
		glfwTerminate();
	}

	return 0;
}