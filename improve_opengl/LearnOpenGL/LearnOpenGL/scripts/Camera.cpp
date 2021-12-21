#include "Camera.h"
#include "Config.h"

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float fov, float near, float far) 
{
	this->camera_pos = pos;
	this->camera_front = glm::normalize(front);
	this->camera_up = up;
	this->fov = fov;
	this->near = near;
	this->far = far;
	this->mouse_sensitivity = 0.05f;
	this->first_mounse = true;

	this->pitch = 0;
	this->yaw = -90.0f;
}

Camera::~Camera() 
{
}

void Camera::setCameraPosition(glm::vec3 position) 
{
	this->camera_pos = position;
}

glm::vec3 Camera::getCameraPosition()
{
	return this->camera_pos;
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

float Camera::getNear() 
{
	return this->near;
}

void Camera::setNear(float near_value) 
{
	this->near = near_value;
}

float Camera::getFar() 
{
	return this->far;
}

void Camera::setFar(float far_value) 
{
	this->far = far_value;
}

void Camera::setCameraType() 
{
}

void Camera::mouse_callback(GLFWwindow * window, double xpos, double ypos) 
{
	if (this->first_mounse)
	{
		this->first_mounse = false;
		this->lastX = xpos;
		this->lastY = ypos;
		return;
	}

	float xoffset = xpos - this->lastX;
	float yoffset = ypos - this->lastY;

	this->lastX = xpos;
	this->lastY = ypos;

	xoffset *= this->mouse_sensitivity;
	yoffset *= this->mouse_sensitivity;

	this->pitch += yoffset;
	this->yaw += xoffset;

	if (this->pitch > 89.0f)
	{
		this->pitch = 89.0f;
	}

	if (this->pitch < -89.0f)
	{
		this->pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
	front.y = sin(glm::radians(this->pitch));
	front.z = cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));

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
	//glm::mat4 projection_orth = glm::ortho(-10.0f, 10.0f, -9.0f, 9.0f, 0.05f, 25.0f);
	//return projection_orth;
	glm::mat4 projection_perspective = glm::perspective(glm::radians(this->fov), Config::Screen_width / Config::Screen_height, this->near, this->far);
	return projection_perspective;
}



