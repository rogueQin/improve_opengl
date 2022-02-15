
#include "Cube.h"

Cube::Cube(GLfloat * vertices_cube)
{
	GLfloat *Panel_triangle = new GLfloat[504]();

	for (int i = 0; i < 12; i++)
	{
		TBNTriangle(vertices_cube, &Panel_triangle[42 * i]);
	}

	glGenBuffers(1, &VBO);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 向缓冲区中写入数据
	glBufferData(GL_ARRAY_BUFFER, 504 * sizeof(GLfloat), Panel_triangle, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
		glEnableVertexAttribArray(4);

	glBindVertexArray(0);
}

Cube::Cube(GLfloat * vertices_cube, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	GLfloat *Panel_triangle = new GLfloat[504]();

	for (int i = 0; i < 12; i ++)
	{
		TBNTriangle(&vertices_cube[24 * i], &Panel_triangle[42 * i]);
	}

	glGenBuffers(1, &VBO);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 向缓冲区中写入数据
	glBufferData(GL_ARRAY_BUFFER, 504 * sizeof(GLfloat), Panel_triangle, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
		glEnableVertexAttribArray(4);
	glBindVertexArray(0);

	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Cube::~Cube() 
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
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

void Cube::renderCube(Shader* shader)
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, this->position);
	trans = glm::rotate(trans, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::rotate(trans, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, this->scale);
	shader->setMatrix4f("model", trans);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::TBNTriangle(GLfloat * vertex_input, GLfloat * vertex_output)
{
	glm::vec3 pos[3] = { 
		glm::vec3(vertex_input[0], vertex_input[1], vertex_input[2]), 
		glm::vec3(vertex_input[8], vertex_input[9], vertex_input[10]), 
		glm::vec3(vertex_input[16], vertex_input[17], vertex_input[18]) 
	};
	glm::vec2 uv[3] = {
		glm::vec2(vertex_input[6], vertex_input[7]),
		glm::vec2(vertex_input[14], vertex_input[15]),
		glm::vec2(vertex_input[22], vertex_input[23])
	};
	glm::vec3 normal[3] = {
		glm::vec3(vertex_input[3], vertex_input[4], vertex_input[5]),
		glm::vec3(vertex_input[11], vertex_input[12], vertex_input[13]),
		glm::vec3(vertex_input[19], vertex_input[20], vertex_input[21])
	};

	glm::vec3 edge1 = pos[1] - pos[0];
	glm::vec3 edge2 = pos[2] - pos[0];

	glm::vec2 deltaUV1 = uv[1] - uv[0];
	glm::vec2 deltaUV2 = uv[2] - uv[0];

	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	glm::vec3 tangent, bitangent;

	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent = glm::normalize(tangent);

	bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent = glm::normalize(bitangent);

	for (int i = 0; i < 3; i++)
	{
		vertex_output[14 * i] = pos[i].x;
		vertex_output[14 * i + 1] = pos[i].y;
		vertex_output[14 * i + 2] = pos[i].z;
		vertex_output[14 * i + 3] = normal[i].x;
		vertex_output[14 * i + 4] = normal[i].y;
		vertex_output[14 * i + 5] = normal[i].z;
		vertex_output[14 * i + 6] = uv[i].x;
		vertex_output[14 * i + 7] = uv[i].y;
		vertex_output[14 * i + 8] = tangent.x;
		vertex_output[14 * i + 9] = tangent.y;
		vertex_output[14 * i + 10] = tangent.z;
		vertex_output[14 * i + 11] = bitangent.x;
		vertex_output[14 * i + 12] = bitangent.y;
		vertex_output[14 * i + 13] = bitangent.z;
	}

	for (int i = 0; i < 42; i++)
	{
		if (vertex_output[i] > -0.001f && vertex_output[i] < 0.001f)
		{
			vertex_output[i] = 0.0f;
		}
		if (vertex_output[i] < 1.001f && vertex_output[i] > 0.999f)
		{
			vertex_output[i] = 1.0f;
		}
		if (vertex_output[i] > -1.001f && vertex_output[i] < -0.999f)
		{
			vertex_output[i] = -1.0f;
		}
	}
}

