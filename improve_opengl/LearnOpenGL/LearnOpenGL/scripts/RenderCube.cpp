#include "RenderCube.h"


RenderCube::RenderCube(int texture_width, int texture_height)
{
	buffer_width = texture_width;
	buffer_height = texture_height;

	// 帧缓冲对象 depth map buffer
	glGenFramebuffers(1, &depthMapFBO);

	// 纹理缓冲附件
	glGenTextures(1, &depthMapCUB);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthMapCUB);

	for (int i =0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i , 0, GL_DEPTH_COMPONENT, texture_width, texture_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMapCUB, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// 帧缓冲状态检测
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR:FRAMEBUFFER:: framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderCube::~RenderCube()
{
	glDeleteTextures(1, &depthMapCUB);
	glDeleteFramebuffers(1, &depthMapFBO);
}

GLuint RenderCube::GetFrameBuffer()
{
	return this->depthMapFBO;
}

GLuint RenderCube::GetRenderCube()
{
	return this->depthMapCUB;
}

void RenderCube::Clear()
{
}

void RenderCube::use(Shader * shader, glm::vec3 position)
{
	glViewport(0, 0, buffer_width, buffer_height);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

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

