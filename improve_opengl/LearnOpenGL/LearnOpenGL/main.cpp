
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"


const int screen_width = 800;
const int screen_height = 600;

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
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

glm::vec3 cube_pos_list[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(5.0f, 5.0f, -5.0f),
	glm::vec3(-5.0f, 5.0f, -5.0f),
	glm::vec3(-5.0f, -5.0f, -5.0f),
	glm::vec3(5.0f, -5.0f, -5.0f),
	glm::vec3(5.0f, 5.0f, 5.0f),
	glm::vec3(-5.0f, 5.0f, 5.0f),
	glm::vec3(-5.0f, -5.0f, 5.0f),
	glm::vec3(5.0f, -5.0f, 5.0f)
};

Camera * camera_main;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window);

void key_callback(GLFWwindow * window, int key, int scancode, int actin, int mods);

void mouse_callback(GLFWwindow * window, double xpos, double ypos);

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

int main() 
{
	// 初始化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建GLFW窗口
	GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "LearnOpenGL", NULL, NULL);
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

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	camera_main = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.01f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	//glfwSetScrollCallback(window, camera_main->scroll_callback);

	// 声明一个顶点缓冲对象
	GLuint VBO;
	glGenBuffers(1, &VBO);
	// 声明一个顶点数组对象
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	// 生命一个EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
		// 设置顶点缓冲对象缓冲区类型
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// 向缓冲区中写入数据
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// EBO数据
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// 连接顶点属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6* sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	

	// 创建Texture缓存对象
	unsigned int texture_wall, texture_face;
	int width, height, nrChanels;

	glGenTextures(1, &texture_wall);
	glBindTexture(GL_TEXTURE_2D, texture_wall);

	// 为当前绑定的纹理对象设置环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 加载纹理
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data_wall = stbi_load("../LearnOpenGL/res/container.jpg", &width, &height, &nrChanels, 0);
	if (data_wall)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_wall);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture!" << std::endl;
	}
	stbi_image_free(data_wall);


	glGenTextures(1, &texture_face);
	glBindTexture(GL_TEXTURE_2D, texture_face);

	// 为当前绑定的纹理对象设置环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data_face = stbi_load("../LearnOpenGL/res/awesomeface.png", &width, &height, &nrChanels, 0);
	if (data_face)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_face);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture!" << std::endl;
	}
	stbi_image_free(data_face);

	Shader* shader = new Shader("../LearnOpenGL/res/shader.vs", "../LearnOpenGL/res/shader.fs");
	shader->use();
	shader->setInt("fallTexture", 0);
	shader->setInt("faceTexture", 1);

	while (!glfwWindowShouldClose(window))
	{
		// 检查并调用事件
		glfwPollEvents();
		
		// 处理输入事件 
		processInput(window);

		camera_main->update();

		// 处理渲染指令
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// 观察矩阵
		glm::mat4 view = camera_main->getView();
		shader->setMatrix4f("view", view);

		// 投影矩阵
		glm::mat4 projection = camera_main->getProjection();
		shader->setMatrix4f("projection", projection);

		for (int i = 0; i < 9; i++)
		{
			// 模型矩阵
			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, cube_pos_list[i]);
			trans = glm::rotate(trans, glm::radians(-45.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		
			shader->setMatrix4f("transform", trans);
			shader->use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_wall);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture_face);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		// 交换缓冲区
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete shader;

	glfwTerminate();
	return 0;
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
	//if (nullptr != camera_main)
	//{
	//	camera_main->key_callback(window, key, scancode, action, mods);
	//}
}
