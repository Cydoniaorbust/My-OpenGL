#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Camera {
public:
	vec3 Position;
	vec3 Front;
	mat4 View;

	Camera(vec3 pos) : Position(pos) {
		float a = radians(180.0f);
		float b = radians(-90.0f);
		Front = normalize(vec3(
				cos(a) * cos(b), 
				sin(b), 
				sin(a) * cos(b)));
		View = lookAt(
			Position, 
			Position + Front, 
			normalize(cross(normalize(cross(Front, vec3(0, 1, 0))), Front)));
	}
};