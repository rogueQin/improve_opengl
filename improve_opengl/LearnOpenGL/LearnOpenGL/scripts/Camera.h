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
	float yaw = 90.0f;

	float lastX = 0.0f;
	float lastY = 0.0f;

	float fov = 45.0f; // field of view

	float near = 0.1f;
	float far = 100.0f;


	bool first_mounse = true;
	// ortho Õý½»
	// perspective Í¸ÊÓ

public:
	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float fov, float near, float far);
	~Camera();

	void setCameraPosition(glm::vec3 position);

	glm::vec3 getCameraPosition();

	void setCameraFront(glm::vec3 front);

	void setCameraUp(glm::vec3 up);

	void setSpeed(float speed);

	void setSensitivity(float sensitivity);

	void setFov(float fov);

	void setCameraType();

	void mouse_callback(GLFWwindow * window, double xpos, double ypos);

	void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

	void input_callback(GLFWwindow * window);

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);

	glm::mat4 getView();

	glm::mat4 getProjection();

	void update();
};


#endif // !CAMERA_H

