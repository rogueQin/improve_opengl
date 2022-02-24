#include "Sphere.h"

const GLuint Sphere::X_SEGMENTS = 64;;
const GLuint Sphere::Y_SEGMENTS = 64;;
const float Sphere::PI = 3.14159265359f;;

Sphere::Sphere() 
{
	CreateSphere();
}

Sphere::Sphere(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	CreateSphere();
}

Sphere::~Sphere() 
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Sphere::CreateSphere()
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> indices;
	std::vector<float> data;

	float xSegment, ySegment, xPos, yPos, zPos;

	for (int x = 0; x <= X_SEGMENTS; x++)
	{
		for (int y = 0; y <= Y_SEGMENTS; y++)
		{
			xSegment = (float)x / (float)X_SEGMENTS;
			ySegment = (float)y / (float)Y_SEGMENTS;

			xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			yPos = std::cos(ySegment * PI);
			zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			positions.push_back(glm::vec3(xPos, yPos, zPos));
			uvs.push_back(glm::vec2(xSegment, ySegment));
			normals.push_back(glm::vec3(xPos, yPos, zPos));
		}
	}

	bool oddRow = false;
	for (int y = 0; y < Y_SEGMENTS; y++)
	{
		if (!oddRow)
		{
			for (int x = 0; x <= X_SEGMENTS; x++)
			{
				indices.push_back(y * (X_SEGMENTS + 1) + x);
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; x--)
			{
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				indices.push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	indexCount = static_cast<GLuint>(indices.size());

	for (GLuint i = 0; i < positions.size(); i++)
	{
		data.push_back(positions[i].x);
		data.push_back(positions[i].y);
		data.push_back(positions[i].z);

		data.push_back(normals[i].x);
		data.push_back(normals[i].y);
		data.push_back(normals[i].z);

		data.push_back(uvs[i].x);
		data.push_back(uvs[i].y);
	}

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
	glBindVertexArray(0);
}

void Sphere::setPosition(glm::vec3 position) 
{
}

void Sphere::setRotation(glm::vec3 rotation) 
{
}

void Sphere::setScale(glm::vec3 scale) 
{
}

GLuint Sphere::getVAO() 
{
	return this->VAO;
}

GLuint Sphere::getVBO() 
{
	return this->VBO;
}

void Sphere::renderSphere(Shader* shader) 
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, this->position);
	trans = glm::rotate(trans, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::rotate(trans, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, this->scale);
	shader->setMatrix4f("model", trans);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
}
