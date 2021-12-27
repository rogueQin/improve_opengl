#pragma once

#ifndef _RenderBuffer_H_
#define _RenderBuffer_H_

#include <glad/glad.h>
#include <iostream>

class RenderBuffer
{
public:
	RenderBuffer(int texture_width, int texture_height);
	~RenderBuffer();

	GLuint GetFrameBuffer();
	GLuint GetRenderTexture();
	GLuint GetRenderObject();

	void Clear();
	void use();

private:
	GLuint depthMapFBO;
	GLuint depthMapRBO;
	GLuint depthMapTexture;
	int buffer_width, buffer_height;

	GLfloat borderColor[4] = { 1.0, 1.0,1.0,1.0 };
};

#endif // !_RenderBuffer_H_


