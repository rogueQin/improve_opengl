#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
};

class Mesh
{
public:
	// 顶点数据
	std::vector<Vertex> vertices;
	// 顶点索引
	std::vector<unsigned int> indices;
	// 图片
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Draw(Shader shader);

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif
