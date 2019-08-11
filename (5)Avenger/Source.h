#pragma once

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "GlfwX64/lib-vc2015/glfw3.lib")
#pragma comment (lib, "Assimp/x64/assimp-vc140-mt.lib")

#ifdef _DEBUG
	#pragma comment (lib, "GladDebugX64/GladDebugX64.lib")
	#pragma comment (lib, "ModelLib/Debug_x64.lib")
	#pragma comment (lib, "EnvLib/Debug_x64.lib")
#else
	#pragma comment (lib, "GladReleaseX64/GladReleaseX64.lib")	
	#pragma comment (lib, "ModelLib/Release_x64.lib")
	#pragma comment (lib, "EnvLib/Release_x64.lib")
#endif

#include <EnvLib/GLEnvironment.h>
#include <ModelLib/Model.h>

#include "Manager.h"

class Camera {
public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::mat4 view;

	Camera() {
		pos = glm::vec3(0, 10, 0);
		float a = glm::radians(180.0f);
		float b = glm::radians(-90.0f);
		front = normalize(glm::vec3(cos(a) * cos(b), sin(b), sin(a) * cos(b)));
		view = lookAt(pos, pos + front, normalize(cross(normalize(cross(front, glm::vec3(0, 1, 0))), front)));
	}
};

#include <functional>
#include <math.h>