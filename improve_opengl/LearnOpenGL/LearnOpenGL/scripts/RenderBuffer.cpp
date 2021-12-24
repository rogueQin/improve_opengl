
#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(int texture_width, int texture_height)
{
	buffer_width = texture_width;
	buffer_height = texture_height;

	// 帧缓冲对象 depth map buffer
	glGenFramebuffers(1, &depthMapFBO);
	
	// 纹理缓冲附件
	glGenTextures(1, &depthMapTexture);
	glBindTexture(GL_TEXTURE_2D, depthMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, texture_width, texture_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 渲染缓冲对象附件
	glGenRenderbuffers(1, &depthMapRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, depthMapRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, texture_width, texture_height);

	// 帧缓冲状态检测
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthMapRBO);
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
	glClear(GL_DEPTH_BUFFER_BIT);
}
