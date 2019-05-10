#include "Source.h"

#include "Game.h"



GLboolean Game::Keys[1024];
GLEnvironment Game::Env;
Camera Game::Cam(vec3(0, 10, 0));

int main(int argc, char * argv[]) {
	try {
		Game Avenger(800, 600);

		while (!glfwWindowShouldClose(Avenger.GetWin())) {
			Avenger.Update();

			Avenger.Draw();

			Avenger.Swap();
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