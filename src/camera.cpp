#include "camera.h"
#include "window.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera()
{
	speed = 6.0f;
	sensitivity = 0.1f;
	position = glm::vec3(0.0f);

	yaw = -90.0f;
	pitch = 0.0f;

	fov = 80.0f;

	update(0);
}

void Camera::update(float deltaTime)
{
	if (deltaTime != 0)
	{
		if (glfwGetKey(Window::window, GLFW_KEY_W) == GLFW_PRESS)
			position += deltaTime * speed * front;
		if (glfwGetKey(Window::window, GLFW_KEY_S) == GLFW_PRESS)
			position -= deltaTime * speed * front;
		if (glfwGetKey(Window::window, GLFW_KEY_D) == GLFW_PRESS)
			position += deltaTime * speed * right;
		if (glfwGetKey(Window::window, GLFW_KEY_A) == GLFW_PRESS)
			position -= deltaTime * speed * right;
		if (glfwGetKey(Window::window, GLFW_KEY_SPACE) == GLFW_PRESS)
			position += deltaTime * speed * glm::vec3(0.0f, 1.0f, 0.0f);
		if (glfwGetKey(Window::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			position -= deltaTime * speed * glm::vec3(0.0f, 1.0f, 0.0f);
		
		double mouseX, mouseY;
		glfwGetCursorPos(Window::window, &mouseX, &mouseY);
		if (lastMouseX != -1 && lastMouseY != -1)
			rotate(mouseX - lastMouseX, lastMouseY - mouseY);
		lastMouseX = mouseX;
		lastMouseY = mouseY;
	}

	front = glm::normalize(glm::vec3(
		glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
		glm::sin(glm::radians(pitch)),
		glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch))
	));
	right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
	up = glm::normalize(glm::cross(right, front));

	viewMatrix = glm::lookAt(position, position + front, up);
}

void Camera::rotate(double x, double y)
{
	yaw += x * sensitivity;
	pitch += y * sensitivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}
