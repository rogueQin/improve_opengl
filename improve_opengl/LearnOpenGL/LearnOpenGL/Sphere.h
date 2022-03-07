#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"

class Sphere
{
public:
	Sphere();
	Sphere(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Sphere();

	void CreateSphere();

	void setPosition(glm::vec3 position);

	void setRotation(glm::vec3 rotation);

	void setScale(glm::vec3 scale);

	void TBNTriangle(glm::vec3 position_list[], glm::vec2 uv_list[], glm::vec3 *tangent_out, glm::vec3 *bitangent_out);

	GLuint getVAO();

	GLuint getVBO();

	void renderSphere(Shader* shader);

private:
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	GLuint indexCount;

	static const GLuint X_SEGMENTS;
	static const GLuint Y_SEGMENTS;
	static const float PI;
};

