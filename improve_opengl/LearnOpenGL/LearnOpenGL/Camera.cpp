#include "Camera.h"
#include "Config.h"

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float fov, float near, float far) 
{
	this->camera_pos = pos;
	this->camera_front = front;
	this->camera_up = up;
	this->fov = fov;
	this->near = near;
	this->far = far;
	this->mouse_sensitivity = 0.05f;
}

Camera::~Camera() 
{
}

void Camera::setCameraPosition(glm::vec3 position) 
{
	this->camera_pos = position;
}

void Camera::setCameraFront(glm::vec3 front) 
{
	this->camera_front = front;
}

void Camera::setCameraUp(glm::vec3 up) 
{
	this->camera_up = up;
}

void Camera::setSpeed(float speed) 
{
	this->camera_speed = speed;
}

void Camera::setSensitivity(float sensitivity) 
{
	this->mouse_sensitivity = sensitivity;
}

void Camera::setFov(float fov) 
{
	this->fov = fov;
}

void Camera::setCameraType() {}

void Camera::mouse_callback(GLFWwindow * window, double xpos, double ypos) 
{
	if (this->first_mounse)
	{
		this->first_mounse = false;
		this->lastX = xpos;
		this->lastY = ypos;
	}

	float xoffset = xpos - this->lastX;
	float yoffset = ypos - this->lastY;

	this->lastX = xpos;
	this->lastY = ypos;

	xoffset *= this->mouse_sensitivity;
	yoffset *= this->mouse_sensitivity;

	this->pitch += yoffset;
	this->yaw += xoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	this->camera_front = glm::normalize(front);
}

void Camera::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	if (this->fov >= 1.0f && this->fov <= 45.0f)
	{
		this->fov -= yoffset;
	}
	if (this->fov <= 1.0f)
	{
		this->fov = 1.0f;
	}
	if (this->fov > 45.0f)
	{
		this->fov = 45.0f;
	}
}

void Camera::input_callback(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera_pos += this->camera_front * this->camera_speed * this->delta_time;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera_pos -= this->camera_front * this->camera_speed * this->delta_time;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera_pos -= glm::normalize(glm::cross(this->camera_front, this->camera_up)) * this->camera_speed * this->delta_time;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera_pos += glm::normalize(glm::cross(this->camera_front, this->camera_up)) * this->camera_speed * this->delta_time;
	}
}

void Camera::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		this->camera_pos += this->camera_front * this->camera_speed * this->delta_time;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		this->camera_pos -= this->camera_front * this->camera_speed * this->delta_time;
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		this->camera_pos -= glm::normalize(glm::cross(this->camera_front, this->camera_up)) * this->camera_speed * this->delta_time;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		this->camera_pos += glm::normalize(glm::cross(this->camera_front, this->camera_up)) * this->camera_speed * this->delta_time;
	}
}

void Camera::update()
{
	float currentFrame = glfwGetTime();
	this->delta_time = currentFrame - this->last_frame;
	this->last_frame = currentFrame;
}

glm::mat4 Camera::getView() 
{
	glm::mat4 view = glm::lookAt(this->camera_pos, this->camera_pos + this->camera_front, this->camera_up);
	return view;
}

glm::mat4 Camera::getProjection() 
{
	glm::mat4 projection = glm::perspective(glm::radians(this->fov), Config::Screen_width / Config::Screen_height, this->near, this->far);
	return projection;
}



