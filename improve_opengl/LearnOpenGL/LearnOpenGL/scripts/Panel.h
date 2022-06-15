#pragma once

#ifndef _PANEL_H_
#define _PANEL_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"

class Panel
{
public:
	Panel();
	Panel(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Panel();

	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);
	GLuint getVAO();
	GLuint getVBO();

	void renderPanel(Shader* shader);

private:
	GLuint VBO;
	GLuint VAO;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	//Shader* shader;
	static const GLfloat panel_vertices[];

	void TBNTriangle(const GLfloat * vertex_input, GLfloat * vertex_output);
};


#endif
