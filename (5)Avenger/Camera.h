#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::mat4 View;

	Camera(glm::vec3 position) {
		Position = position;
		float a = glm::radians(180.0f);
		float b = glm::radians(-90.0f);
		Front = glm::normalize(glm::vec3(
				glm::cos(a) * glm::cos(b), 
				glm::sin(b), 
				glm::sin(a) * glm::cos(b)));
		View = glm::lookAt(Position, Position + Front, glm::normalize(glm::cross(glm::normalize(glm::cross(Front, glm::vec3(0, 1, 0))), Front)));
	}
};