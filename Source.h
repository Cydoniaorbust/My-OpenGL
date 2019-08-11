#pragma once

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "Glfw/Win64/lib-vc2015/glfw3.lib")
#pragma comment (lib, "Assimp/x64/assimp-vc140-mt.lib")

//#ifndef STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb/stb_image.h>
//#endif

#ifdef _DEBUG
	#pragma comment (lib, "Glad/Debug.lib")
	#include <Glad/Debug/glad.h>

	#pragma comment (lib, "EnvLib/Debug_x64.lib")
	#pragma comment (lib, "ShaderLib/Debug_x64.lib")
	#pragma comment (lib, "CameraLib/Debug_x64.lib")
	#pragma comment (lib, "TextureLib/Debug_x64.lib")
#else
	#pragma comment (lib, "Glad/Release.lib")
	#include <Glad/Release/glad.h>

	#pragma comment (lib, "EnvLib/Release_x64.lib")
	#pragma comment (lib, "ShaderLib/Release_x64.lib")
	#pragma comment (lib, "CameraLib/Release_x64.lib")
	#pragma comment (lib, "TextureLib/Release_x64.lib")
#endif

#include <glfw/Win64/glfw3.h>

#include <GLEnvironment.h>
#include <Shader.h>
#include <Camera.h>
#include <Texture.h>