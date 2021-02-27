#pragma once

#include <glm/glm.hpp>


class Camera
{
public:
	Camera();

	glm::vec3 position, front, right, up;
	float yaw, pitch, fov, speed, sensitivity;

	double lastMouseX = -1, lastMouseY = -1;

	glm::mat4 viewMatrix;

	void update(float deltaTime);
	void rotate(double x, double y);
};

