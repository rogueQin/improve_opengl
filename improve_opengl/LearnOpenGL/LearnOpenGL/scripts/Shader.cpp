#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragementPath) 
{
	std::string vertexCode;
	std::string fragementCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragementPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragementCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error::shader::file_not_succesfully_read!" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragementCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// 顶点着色器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error::shader::vertes::compilation_failed\n" << infoLog << std::endl;
	}

	// 片段着色器
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error::shader::fragemnt::compilation_failed\n" << infoLog << std::endl;
	}

	// 着色器程序
	
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error::shader::program::compilation_failed\n" << infoLog << std::endl;
	}

	// 清理连接到程序对象的着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragementPath, const GLchar* geometryPath)
{
	std::string vertexCode;
	std::string fragementCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragementPath);
		gShaderFile.open(geometryPath);
		std::stringstream vShaderStream, fShaderStream, gShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();
		gShaderFile.close();

		vertexCode = vShaderStream.str();
		fragementCode = fShaderStream.str();
		geometryCode = gShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error::shader::file_not_succesfully_read!" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragementCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	unsigned int vertex, fragment, geometry;
	int success;
	char infoLog[512];

	// 顶点着色器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error::shader::vertes::compilation_failed\n" << infoLog << std::endl;
	}

	// 几何着色器
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &gShaderCode, NULL);
	glCompileShader(geometry);
	glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometry, 512, NULL, infoLog);
		std::cout << "Error::shader::geometry::compilation_failed\n" << infoLog << std::endl;
	}

	// 片段着色器
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error::shader::fragemnt::compilation_failed\n" << infoLog << std::endl;
	}

	// 着色器程序
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, geometry);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error::shader::program::compilation_failed\n" << infoLog << std::endl;
	}

	// 清理连接到程序对象的着色器
	glDeleteShader(vertex);
	glDeleteShader(geometry);
	glDeleteShader(fragment);
}

Shader::~Shader() 
{
	glDeleteProgram(ID);
}

void Shader::use() 
{
	glUseProgram(ID);
}


void Shader::setBool(const std::string &name, bool value) const 
{
	GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformLocation, (int)value);
}

void Shader::setInt(const std::string &name, int value) const 
{
	GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformLocation, value);
}

void Shader::setFloat(const std::string &name, float value) const 
{
	GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uniformLocation, value);
}

void Shader::setMatrix4f(const std::string &name, glm::mat4 transform) const
{
	GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
	// uniformLocation 
	// 参数二 : 矩阵数量
	// 参数三 : 是否交换矩阵（行列对换）
	// 参数四 : 矩阵数据
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(transform));
}

void Shader::setVec3f(const std::string name, glm::vec3 vec)const 
{
	GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
	glUniform3f(uniformLocation, vec.x, vec.y, vec.z);
}

void Shader::setBlock(const std::string name, int value)const 
{
	GLuint uniformLocation = glGetUniformBlockIndex(ID, name.c_str());
	glUniformBlockBinding(ID, uniformLocation, value);
}