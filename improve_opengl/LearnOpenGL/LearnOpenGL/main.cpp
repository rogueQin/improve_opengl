
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
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,

		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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

	camera_main = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.01f, 100.0f);

 	glEnable(GL_DEPTH_TEST);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);
	//glfwSetKeyCallback(window, key_callback);

	// 声明一个顶点缓冲对象
	GLuint VBO;
	glGenBuffers(1, &VBO);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 向缓冲区中写入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 声明一个顶点数组对象
	GLuint VAO_obj;
	glGenVertexArrays(1, &VAO_obj);

	// cube obj
	glBindVertexArray(VAO_obj);
		// 连接顶点属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6* sizeof(GLfloat)));
		//glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// light
	GLuint VAO_light;
	glGenVertexArrays(1, &VAO_light);
	glBindVertexArray(VAO_light);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	Shader* shader_light = new Shader("../LearnOpenGL/res/shader.vs", "../LearnOpenGL/res/shader_light.fs");
	Shader* shader_obj = new Shader("../LearnOpenGL/res/shader.vs", "../LearnOpenGL/res/shader.fs");	

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
		// 投影矩阵
		glm::mat4 projection = camera_main->getProjection();
		
		shader_light->use();
		shader_light->setMatrix4f("view", view);
		shader_light->setMatrix4f("projection", projection);

		glm::mat4 trans_light = glm::mat4(1.0f);
		trans_light = glm::translate(trans_light, glm::vec3(2.0f, 2.0f, 2.0f));
		shader_light->setMatrix4f("transform", trans_light);
		glBindVertexArray(VAO_light);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		shader_obj->use();
		

		shader_obj->setMatrix4f("view", view);
		shader_obj->setMatrix4f("projection", projection);
		glm::mat4 trans_obj = glm::mat4(1.0f);
		trans_obj = glm::scale(trans_obj, glm::vec3(0.8f, 0.8f, 0.8f));
		trans_obj = glm::rotate(trans_obj, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
		shader_obj->setMatrix4f("transform", trans_obj);

		glm::vec3 light_color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 light_pos = glm::normalize(glm::vec3(1.2f, 1.0f, 2.0f));

		shader_obj->setVec3f("lightPos", light_pos);
		shader_obj->setVec3f("lightColor", light_color);
		shader_obj->setVec3f("objColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shader_obj->setVec3f("viewPos", glm::vec3(0.0f, 0.0f, 3.0f));
		glBindVertexArray(VAO_obj);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// 交换缓冲区
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO_obj);
	glDeleteVertexArrays(1, &VAO_light);
	glDeleteBuffers(1, &VBO);
	//delete shader_obj;
	delete shader_light;

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
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}
