// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Source.h"

constexpr bool Logging = 1;
Logger logger;

#include "World.h"

GLboolean World::Keys[1024];


int main(int argc, char * argv[]) {
	try {
		if (Logging) {
			logger.write("<<Game initiated.>>\n");
		}
		World Avenger(800, 600);

		Avenger.Loop();
	}
	catch (Error* e) {
		logger.write(e->GetData());
		//std::cerr << e->GetData() << std::endl;
		delete e;
		glfwTerminate();
	}

	return 0;
}