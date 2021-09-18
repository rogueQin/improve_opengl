
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Model.h"
#include "Config.h"


GLfloat vertices_cube [] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,

		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
};

GLfloat vertices_panel [] = {
	-0.5f, -0.5f, 0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,

	 0.5f,  0.5f, 0.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
};

GLfloat vertices_skybox[] = {
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
				
		 1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		 		
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 		
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
				
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
	
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,

		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,

		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f
};

glm::vec3 cube_pos_lit[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(-2.0f, -2.0f, 2.0f),
	glm::vec3(-2.0f, 2.0f, 2.0f),
	glm::vec3(2.0f, 2.0f, 2.0f),
	glm::vec3(2.0f, -2.0f, 2.0f),
	glm::vec3(-2.0f, -2.0f, -2.0f),
	glm::vec3(-2.0f, 2.0f, -2.0f),
	glm::vec3(2.0f, 2.0f, -2.0f),
	glm::vec3(2.0f, -2.0f, -2.0f)
};

glm::vec3 light_pos_list[] = {
	glm::vec3(3.0f, 3.0f, 0.0f),
	glm::vec3(-3.0f, -3.0f, 0.0f),
	glm::vec3(3.0f, -3.0f, 0.0f),
	glm::vec3(-3.0f, 3.0f, 0.0f),

	glm::vec3(0.0f, 5.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f)
};

glm::vec3 grass_pos_list[] = {
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(3.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 3.0f),
	glm::vec3(2.0f, 1.0f, 2.0f),
};

glm::vec3 window_pos_list[] = {
	glm::vec3(0.0f, 7.0f, 3.0f),
	glm::vec3(-1.0f, 8.0f, 5.0f),
	glm::vec3(-1.0f, 5.0f, 7.0f),
};

unsigned int indices[] = {
	0,1,2,
	2,3,0,

	4,5,6,
	6,7,4,

	8,9,10,
	10,11,8,

	12,13,14,
	14,15,12,

	16,17,18,
	18,19,16,

	20,21,22,
	22,23,20
};

Camera * camera_main;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window);

void key_callback(GLFWwindow * window, int key, int scancode, int actin, int mods);

void mouse_callback(GLFWwindow * window, double xpos, double ypos);

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

unsigned int loadTexture(std::string fileName);
unsigned int loadCubeMap(std::vector<std::string> faces);

int main() 
{
	// 初始化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建GLFW窗口
	GLFWwindow* window = glfwCreateWindow(Config::Screen_width, Config::Screen_height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// 初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}

	glViewport(0, 0, Config::Screen_width, Config::Screen_height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	camera_main = new Camera(glm::vec3(0.0f, 10.0f, 20.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 100.0f);

	stbi_set_flip_vertically_on_load(true);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS); //GL_ALWAYS、GL_NEVER、GL_LESS、GL_EQUAL、GL_LEQUAL

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	// 声明一个顶点缓冲对象
	GLuint VBO_cub, VBO_panel, VBO_skybox;
	glGenBuffers(1, &VBO_cub);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cub);
	// 向缓冲区中写入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO_panel);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO_panel);
	// 向缓冲区中写入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_panel), vertices_panel, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO_skybox);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO_skybox);
	// 向缓冲区中写入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_skybox), vertices_skybox, GL_STATIC_DRAW);
	
	// light
	GLuint VAO_cube, VAO_plane, VAO_skybox;
	glGenVertexArrays(1, &VAO_cube);
	glBindVertexArray(VAO_cube);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_cub);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAO_skybox);
		glBindVertexArray(VAO_skybox);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_skybox);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAO_plane);
	glBindVertexArray(VAO_plane);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_panel);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	unsigned int cube_texture = loadTexture("../LearnOpenGL/res/container2.png");
	unsigned int floor_texture = loadTexture("../LearnOpenGL/res/wall.jpg");
	unsigned int grass_texture = loadTexture("../LearnOpenGL/res/grass.png");
	unsigned int window_texture = loadTexture("../LearnOpenGL/res/blending_transparent_window.png");
	
	std::vector<std::string> faces = {
		"../LearnOpenGL/res/skybox/right.jpg",
		"../LearnOpenGL/res/skybox/left.jpg",
		"../LearnOpenGL/res/skybox/top.jpg",
		"../LearnOpenGL/res/skybox/bottom.jpg",
		"../LearnOpenGL/res/skybox/front.jpg",
		"../LearnOpenGL/res/skybox/back.jpg"
	};
	unsigned int cubeMapTexture = loadCubeMap(faces);

	Shader shader_stencil = Shader("../LearnOpenGL/res/shader_light.vs", "../LearnOpenGL/res/shader_light.fs");
	Shader shader_obj = Shader("../LearnOpenGL/res/shader.vs", "../LearnOpenGL/res/shader.fs");
	Shader shader_gress = Shader("../LearnOpenGL/res/shader_blend.vs", "../LearnOpenGL/res/shader_blend.fs");
	Shader shader_frame = Shader("../LearnOpenGL/res/shader_light.vs", "../LearnOpenGL/res/shader_frame.fs");
	Shader shader_skybox = Shader("../LearnOpenGL/res/shader_skybox.vs", "../LearnOpenGL/res/shader_skybox.fs");

	Model model = Model("../LearnOpenGL/res/nanosuit/nanosuit.obj");

	while (!glfwWindowShouldClose(window))
	{
		// 检查并调用事件
		glfwPollEvents();	

		// 处理输入事件 
		processInput(window);

		camera_main->update();

		// 处理渲染指令
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		// 观察矩阵
		glm::mat4 view = camera_main->getView();
		// 投影矩阵
		glm::mat4 projection = camera_main->getProjection();
		// 模型矩阵
		glm::mat4 transform = glm::mat4(1.0f);

		//transform = glm::translate(transform, glm::vec3(0.0f, -1.0f, 0.0f));
		transform = glm::scale(transform, glm::vec3(30.0f));
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		// 地面
		shader_obj.use();
		shader_obj.setMatrix4f("transform", transform);
		shader_obj.setMatrix4f("view", view);
		shader_obj.setMatrix4f("projection", projection);
		glBindVertexArray(VAO_plane);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floor_texture);
		shader_obj.setInt("testTexture", 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// model
		glEnable(GL_CULL_FACE);
		glm::mat4 transform_cub = glm::mat4(1.0f);
		shader_obj.use();
		shader_obj.setMatrix4f("transform", transform_cub);
		shader_obj.setMatrix4f("view", view);
		shader_obj.setMatrix4f("projection", projection);
		model.draw(shader_obj);

		// cube
		transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(3.0f, 3.0f,3.0f));
		transform = glm::translate(transform, glm::vec3(-3.0f, 3.0f, 0.0f));
		shader_obj.use();
		shader_obj.setMatrix4f("transform", transform);
		shader_obj.setMatrix4f("view", view);
		shader_obj.setMatrix4f("projection", projection);
		glBindVertexArray(VAO_cube);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cube_texture);
		shader_obj.setInt("testTexture", 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDisable(GL_CULL_FACE);

		// 天空盒
		glDepthFunc(GL_LEQUAL);
		shader_skybox.use();
		shader_skybox.setMatrix4f("view", glm::mat4(glm::mat3(view)));
		shader_skybox.setMatrix4f("projection", projection);
		glBindVertexArray(VAO_skybox);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
		shader_skybox.setInt("skybox", 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthFunc(GL_ALWAYS);

		// 交换缓冲区
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO_cube);
	glDeleteVertexArrays(1, &VAO_plane);
	glDeleteVertexArrays(1, &VAO_skybox);
	glDeleteBuffers(1, &VBO_cub);
	glDeleteBuffers(1, &VBO_panel);
	glDeleteBuffers(1, &VBO_skybox);
	//delete &shader_obj;
	//delete &shader_light;

	glfwTerminate();
	return 0;
}

unsigned int loadTexture(std::string fileName)
{
	std::string file_path = fileName;

	unsigned int texture;
	int width, height, nrChanels;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &nrChanels, 0);
	if (data)
	{
		GLenum format;
		if (nrChanels == 1)
		{
			format = GL_RED;
		}
		else if (nrChanels == 3)
		{
			format = GL_RGB;
		}
		else if (nrChanels == 4)
		{
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load diffuse texture!" << std::endl;
	}
	stbi_image_free(data);

	return texture;
}

unsigned int loadCubeMap(std::vector<std::string> faces) 
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	stbi_set_flip_vertically_on_load(false);
	int width, height, nrChannels;
	for (int i = 0; i < faces.size(); i ++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else 
		{
			std::cout << "Cubemap texture failed to load at path:" << faces[i] << std::endl;
		}
		stbi_image_free(data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (nullptr != camera_main)
	{
		camera_main->input_callback(window);
	}
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (nullptr != camera_main)
	{
		camera_main->mouse_callback(window, xpos, ypos);
	}
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) 
{
	if (nullptr != camera_main)
	{
		camera_main->scroll_callback(window, xoffset, yoffset);
	}
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}
