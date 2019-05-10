#include <Source.h>

#include "Game.h"

#include <iostream>

GLboolean Game::Keys[1024];
GLEnvironment Game::Env;
Camera Game::Cam(vec3(1, 1, -3));

int main(int argc, char * argv[]) {
	try {
		Game Ranger(800, 600);

		while (!glfwWindowShouldClose(Ranger.GetWin())) {
			Ranger.Update();

			Ranger.Draw("axis", true);
			Ranger.Draw("sprite", false);

			Ranger.Swap();
		}

		glfwTerminate();
	}
	catch (Error* e) {
		std::cerr << e->GetData() << std::endl;
		delete e;
		glfwTerminate();
	}

	return 0;
}