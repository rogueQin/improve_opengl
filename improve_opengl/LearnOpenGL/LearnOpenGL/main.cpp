
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"


GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f
};

unsigned int indices[] = {
	0,1,2,
	2,3,0
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window);

int main() 
{
	// ��ʼ��GLFW����
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ����GLFW����
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	// ����һ�����㻺�����
	GLuint VBO;
	glGenBuffers(1, &VBO);
	// ����һ�������������
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	// ����һ��EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
		// ���ö��㻺����󻺳�������
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// �򻺳�����д������
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// EBO����
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// ���Ӷ�������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	

	Shader* shader = new Shader("../LearnOpenGL/res/shader.vs", "../LearnOpenGL/res/shader.fs");

	while (!glfwWindowShouldClose(window))
	{
		// ��鲢�����¼�
		glfwPollEvents();
		// ���������¼�
		processInput(window);

		// ������Ⱦָ��
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// ����������
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
}
