#include "Sphere.h"

const GLuint Sphere::X_SEGMENTS = 64;
const GLuint Sphere::Y_SEGMENTS = 64;
const float Sphere::PI = 3.14159265359f;

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
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;

	glm::vec3 last_pos = glm::vec3(0);
	glm::vec3 tangent = glm::vec3(0);
	glm::vec3 bitangent = glm::vec3(0);

	float xSegment, ySegment, xPos, yPos, zPos;

	for (int x = 0; x <= X_SEGMENTS; x++)
	{
		xSegment = (float)x / (float)X_SEGMENTS;
		glm::vec3 last_pos = glm::vec3(0);

		for (int y = 0; y <= Y_SEGMENTS; y++)
		{
			ySegment = (float)y / (float)Y_SEGMENTS;

			xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			yPos = std::cos(ySegment * PI);
			zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			positions.push_back(glm::vec3(xPos, yPos, zPos));
			uvs.push_back(glm::vec2(xSegment, ySegment));
			normals.push_back(glm::vec3(xPos, yPos, zPos));
			if (y == 0)
			{
				tangent = glm::normalize(glm::vec3(std::cos(xSegment * 2.0f * PI), 0, std::sin(xSegment * 2.0f * PI)));
				bitangent = glm::normalize(glm::cross(tangent, glm::vec3(0, 1, 0)));
			}
			else if (y == Y_SEGMENTS)
			{
				tangent = glm::normalize(-glm::vec3(std::cos(xSegment * 2.0f * PI), 0, -std::sin(xSegment * 2.0f * PI)));
				bitangent = glm::normalize(glm::cross(tangent, glm::vec3(0, -1, 0)));
			}
			else
			{
				tangent = glm::normalize(glm::vec3(xPos, yPos, zPos) - last_pos);
				bitangent = glm::normalize(glm::cross(tangent, glm::vec3(xPos, yPos, zPos)));
			}
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);

			last_pos = glm::vec3(xPos, yPos, zPos);
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

	glm::vec3 pos[] = {glm::vec3(0),glm::vec3(0),glm::vec3(0)};
	glm::vec2 uv[] = {glm::vec2(0),glm::vec2(0),glm::vec2(0)};

	//for (int i = 1; i < X_SEGMENTS; i++)
	//{
	//	uv[0] = uvs[i * (Y_SEGMENTS + 1)];
	//	uv[1] = uvs[(i+1) * (Y_SEGMENTS + 1) + Y_SEGMENTS / 2];
	//	uv[2] = uvs[i * (Y_SEGMENTS + 1)];
	//}

	//for (int i = 1; i < indexCount - 2; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		pos[j] = positions[indices[i + j]];
	//		uv[j] = uvs[indices[i + j]];
	//	}
	//	TBNTriangle(pos, uv, &tangent, &bitangent);
	//	for (int j = 0; j < 3; j++)
	//	{
	//		tangents[indices[i + j]] = tangent;
	//		bitangents[indices[i + j]] = bitangent;
	//	}
	//}

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

		data.push_back(tangents[i].x);
		data.push_back(tangents[i].y);
		data.push_back(tangents[i].z);

		data.push_back(bitangents[i].x);
		data.push_back(bitangents[i].y);
		data.push_back(bitangents[i].z);
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GL_FLOAT), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GL_FLOAT), (void*)(8 * sizeof(GL_FLOAT)));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GL_FLOAT), (void*)(11 * sizeof(GL_FLOAT)));
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

void Sphere::TBNTriangle(glm::vec3 position_list[], glm::vec2 uv_list[], glm::vec3 *tangent_out, glm::vec3 *bitangent_out)
{
	glm::vec3 edge1 = position_list[1] - position_list[0];
	glm::vec3 edge2 = position_list[2] - position_list[0];

	glm::vec2 deltaUV1 = uv_list[1] - uv_list[0];
	glm::vec2 deltaUV2 = uv_list[2] - uv_list[0];

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

	tangent_out[0] = tangent;
	bitangent_out[0] = bitangent;
}
