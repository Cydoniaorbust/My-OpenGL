#include "Study/Camera.h"

Camera::Camera() : 
	Up_World(vec3(0, 1, 0)), Front(0), Up(0), Right(0), 
	MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM), 
	Position(0), Yaw(YAW), Pitch(PITCH) {}
Camera::Camera(vec3 position) : Camera() {
	Position = position;

	updateCameraVectors();
}
Camera::Camera(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch) : Camera() {
	Position = position;
	Up_World = up;
	Yaw = yaw;
	Pitch = pitch;

	updateCameraVectors();
}

mat4 Camera::GetViewMatrix() const { return lookAt(Position, Position + Front, Up); }
vec3 Camera::GetFront() const { return Front; }

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
	GLfloat velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)	Position += Front * velocity;
	if (direction == BACKWARD)	Position -= Front * velocity;
	if (direction == LEFT)	Position -= Right * velocity;
	if (direction == RIGHT)	Position += Right * velocity;
}
void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset) {
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f) Pitch = 89.0f;
	if (Pitch < -89.0f) Pitch = -89.0f;

	updateCameraVectors();
}
void Camera::ProcessMouseScroll(GLfloat yoffset) {
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

//Front + Right + Up
void Camera::updateCameraVectors() {
	vec3 front;

	front.x = cos(radians(Yaw)) * cos(radians(Pitch));
	front.y = sin(radians(Pitch));
	front.z = sin(radians(Yaw)) * cos(radians(Pitch));

	Front = normalize(front);
	Right = normalize(cross(Front, Up_World));
	Up = normalize(cross(Right, Front));
}