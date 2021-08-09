#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:

	glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 camera_right = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_world_up = glm::vec3(0.0f, 1.0f, 0.0f);

	float camera_speed = 1.0f;
	float mouse_sensitivity = 1.0f;

	float delta_time = 0.0f;
	float last_frame = 0.0f;

	float pitch = 0.0f;
	float yaw = 0.0f;

	float lastX = 0.0f;
	float lastY = 0.0f;

	float fov = 45.0f;


public:
	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);
	~Camera();

	void setFov(float fov);

	void mouse_callback(GLFWwindow * window, double xpos, double ypos);

	void scale_callback(GLFWwindow * window, double xoffset, double yoffset);

	void input_callback(GLFWwindow * window);


};


#endif // !CAMERA_H

