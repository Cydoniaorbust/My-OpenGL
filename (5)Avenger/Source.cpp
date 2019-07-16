#include "Source.h"

bool DrawHits = true;
bool ReleaseInputLock = true;
GLfloat FPSUpdateRate = 0.5;

#include "World.h"

GLboolean World::keys[1024];

int main(int argc, char * argv[]) {
	Logger logger;

	try {
		logger.Write("<<Game initiated.>>\n");
		World avenger(800, 800);

		avenger.Loop();
	}
	catch (Error* _e) {
		logger.Write(_e->GetData());
		delete _e;
		glfwTerminate();
	}

	return 0;
}