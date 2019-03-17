#pragma once

#pragma comment (lib, "opengl32.lib")

#ifdef _DEBUG
	#pragma comment (lib, "Glad/Debug.lib")
	#include <Glad/Debug/glad.h>
	
	#pragma comment (lib, "EnvLib/Debug_x64.lib")
	#pragma comment (lib, "ShaderLib/Debug_x64.lib")
	#pragma comment (lib, "TextureLib/Debug_x64.lib")
#else
	#pragma comment (lib, "Glad/Release.lib")
	#include <Glad/Release/glad.h>
	
	#pragma comment (lib, "EnvLib/Release_x64.lib")
	#pragma comment (lib, "ShaderLib/Release_x64.lib")
	#pragma comment (lib, "TextureLib/Release_x64.lib")
#endif

#ifdef _WIN64
#pragma comment (lib, "Glfw/Win64/lib-vc2015/glfw3.lib")
#include <glfw/Win64/glfw3.h>
#else
#pragma comment (lib, "Glfw/Win32/lib-vc2015/glfw3.lib")
#include <glfw/Win32/glfw3.h>
#endif

#pragma comment (lib, "opengl32.lib")

#include <GLEnvironment.h>
#include <Shader.h>
#include <Texture.h>