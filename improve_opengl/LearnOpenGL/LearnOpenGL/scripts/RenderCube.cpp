#include "RenderCube.h"


RenderCube::RenderCube(int texture_width, int texture_height, bool mipmap)
{
	buffer_width = texture_width;
	buffer_height = texture_height;

	// 帧缓冲对象 depth map buffer
	glGenFramebuffers(1, &cubeMapFBO);
	//// 渲染缓冲对象
	//glGenRenderbuffers(1, &cubeMapRBO);

	
	// 纹理缓冲附件
	glGenTextures(1, &cubeMapCUB);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapCUB);

	for (int i =0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i , 0, GL_RGB16F, texture_width, texture_height, 0, GL_RGB, GL_FLOAT, NULL);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (mipmap) 
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, cubeMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, cubeMapCUB, 0);

	
	//glBindRenderbuffer(GL_RENDERBUFFER, cubeMapRBO);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, texture_width, texture_height);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, cubeMapRBO);

	// 帧缓冲状态检测
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR:FRAMEBUFFER:: framebuffer is not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderCube::~RenderCube()
{
	glDeleteTextures(1, &cubeMapCUB);
	//glDeleteRenderbuffers(1, &cubeMapRBO);
	glDeleteFramebuffers(1, &cubeMapFBO);
}

GLuint RenderCube::GetFrameBuffer()
{
	return this->cubeMapFBO;
}

GLuint RenderCube::GetRenderCube()
{
	return this->cubeMapCUB;
}

void RenderCube::Clear()
{
}

void RenderCube::use(Shader * shader, glm::vec3 position)
{
	glViewport(0, 0, buffer_width, buffer_height);
	glBindFramebuffer(GL_FRAMEBUFFER, cubeMapFBO);
	//glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->position = position;

	glm::mat4 light_projection = glm::perspective(glm::radians(90.0f), (float)this->buffer_width / (float)this->buffer_width, 1.0f, 25.0f);

	view_cube.clear();
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	shader->setVec3f("lightPos", position);
	shader->setFloat("far_plane", 25.0f);
	
	for (int i = 0; i < 6; i ++)
	{
		shader->setMatrix4f("shadowMatrices[" + std::to_string(i) + "]", view_cube[i]);
	}
	
}

void RenderCube::useMipMap(Shader * shader, glm::vec3 position, GLuint level, GLuint texture_width, GLuint texture_height)
{
	glViewport(0, 0, texture_width, texture_height);
	glBindFramebuffer(GL_FRAMEBUFFER, cubeMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, cubeMapCUB, level);
	//glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->position = position;

	glm::mat4 light_projection = glm::perspective(glm::radians(90.0f), (float)this->buffer_width / (float)this->buffer_width, 1.0f, 25.0f);

	view_cube.clear();
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	view_cube.push_back(light_projection * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	shader->setVec3f("lightPos", position);
	shader->setFloat("far_plane", 25.0f);

	for (int i = 0; i < 6; i++)
	{
		shader->setMatrix4f("shadowMatrices[" + std::to_string(i) + "]", view_cube[i]);
	}
}

void RenderCube::generateMipmap()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapCUB);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}
