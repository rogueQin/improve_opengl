#pragma once

#ifndef _SkyBox_H_
#define _SkyBox_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class SkyBox
{
public:
	SkyBox(GLfloat * vertices_cube, int size);
	~SkyBox();

	void renderCube();

private:
	GLuint VBO;
	GLuint VAO;
};

#endif
