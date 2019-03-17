#include "Game.h"

#include <iostream>

class Error : public std::exception {
	const char* data;
public:
	Error(const char* _data) : data(_data) {};
	const char* GetData() { return data; };
};

int main(int argc, char *argv[]) {
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