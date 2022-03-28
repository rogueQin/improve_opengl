
#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(int texture_width, int texture_height)
{
	buffer_width = texture_width;
	buffer_height = texture_height;

	// 帧缓冲对象 depth map buffer
	glGenFramebuffers(1, &depthMapFBO);

	glGenRenderbuffers(1, &depthMapRBO);
	
	// 纹理缓冲附件
	glGenTextures(1, &depthMapTexture);
	glBindTexture(GL_TEXTURE_2D, depthMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, texture_width, texture_height, 0, GL_RG, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	// 渲染缓冲对象附件
	//glBindRenderbuffer(GL_RENDERBUFFER, depthMapRBO);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, texture_width, texture_height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, depthMapTexture, 0);

	// 帧缓冲状态检测
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthMapRBO);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR:FRAMEBUFFER:: framebuffer is not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &depthMapRBO);
	glDeleteTextures(1, &depthMapTexture);
	glDeleteFramebuffers(1, &depthMapFBO);
}

GLuint RenderBuffer::GetFrameBuffer() 
{
	return this->depthMapFBO;
}

GLuint RenderBuffer::GetRenderTexture() 
{
	return this->depthMapTexture;
}

GLuint RenderBuffer::GetRenderObject() 
{
	return this->depthMapRBO;
}

void RenderBuffer::Clear() 
{
}

void RenderBuffer::use()
{
	glViewport(0, 0, buffer_width, buffer_height);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
