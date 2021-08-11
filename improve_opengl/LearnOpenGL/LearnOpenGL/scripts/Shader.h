#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
	unsigned int ID;
	
	Shader(const GLchar* vertexPath, const GLchar* fragementPath);
	~Shader();

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMatrix4f(const std::string &name, glm::mat4 transform) const;
	void setVec3f(const std::string name, glm::vec3 vec)const;
};


#endif // !1

