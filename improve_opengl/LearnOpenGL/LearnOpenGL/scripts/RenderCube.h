#pragma once


#ifndef _RenderCube_H_
#define _RenderCube_H_

#include <vector>
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class RenderCube
{
public:
	RenderCube(int texture_width, int texture_height);
	~RenderCube();

	GLuint GetFrameBuffer();
	GLuint GetRenderCube();

	void Clear();
	void use(Shader * shader, glm::vec3 position);

private:
	//GLuint cubeMapRBO;
	GLuint cubeMapFBO;
	GLuint cubeMapCUB;
	int buffer_width, buffer_height;
	glm::vec3 position;
	std::vector<glm::mat4 > view_cube;

	GLfloat borderColor[4] = { 1.0, 1.0,1.0,1.0 };
};

#endif // !_RenderCube_H_


