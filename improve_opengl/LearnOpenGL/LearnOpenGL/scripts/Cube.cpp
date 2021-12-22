
#include "Cube.h"

Cube::Cube(GLfloat * vertices_cube, int size)
{
	glGenBuffers(1, &VBO);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 向缓冲区中写入数据
	glBufferData(GL_ARRAY_BUFFER, size, vertices_cube, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

Cube::Cube(GLfloat * vertices_cube, int size, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	glGenBuffers(1, &VBO);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 向缓冲区中写入数据
	glBufferData(GL_ARRAY_BUFFER, size, vertices_cube, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Cube::~Cube() 
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VBO);
}

void Cube::setPosition(glm::vec3 position) 
{
	this->position = position;
}

void Cube::setRotation(glm::vec3 rotation) 
{
	this->rotation = rotation;
}

void Cube::setScale(glm::vec3 scale) 
{
	this->scale = scale;
}

GLuint Cube::getVAO()
{
	return this->VAO;
}

GLuint Cube::getVBO()
{
	return this->VBO;
}

//void Cube::setShader(Shader* shader)
//{
//	this->shader = shader;
//}

void Cube::renderCube(Shader* shader)
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::scale(trans, this->scale);
	trans = glm::rotate(trans, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::rotate(trans, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::translate(trans, this->position);
	shader->setMatrix4f("transform", trans);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

