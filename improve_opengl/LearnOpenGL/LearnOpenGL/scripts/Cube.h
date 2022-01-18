#pragma once

#ifndef _CUBE_H_
#define _CUBE_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"


class Cube
{
public:
	Cube(GLfloat * vertices_cube);
	Cube(GLfloat * vertices_cube, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Cube();

	void setPosition(glm::vec3 position);

	void setRotation(glm::vec3 rotation);

	void setScale(glm::vec3 scale);

	GLuint getVAO();

	GLuint getVBO();

	void TBNTriangle(GLfloat * vertex_input, GLfloat * vertex_output);

	void renderCube(Shader* shader);

	//void setShader(Shader* shader);

private:
	GLuint VBO;
	GLuint VAO;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	//Shader* shader;
};


#endif // !_Cube_H_


