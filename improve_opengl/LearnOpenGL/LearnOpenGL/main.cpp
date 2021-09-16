
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
	GLuint VBO_cub, VBO_panel;
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

	// light
	GLuint VAO_cube, VAO_plane;
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

	Shader shader_stencil = Shader("../LearnOpenGL/res/shader_light.vs", "../LearnOpenGL/res/shader_light.fs");
	Shader shader_obj = Shader("../LearnOpenGL/res/shader.vs", "../LearnOpenGL/res/shader.fs");
	Shader shader_gress = Shader("../LearnOpenGL/res/shader_blend.vs", "../LearnOpenGL/res/shader_blend.fs");
	Shader shader_frame = Shader("../LearnOpenGL/res/shader_light.vs", "../LearnOpenGL/res/shader_frame.fs");

	Model model = Model("../LearnOpenGL/res/nanosuit/nanosuit.obj");

	GLuint FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	unsigned int FBOTexture_RGB;
	glGenTextures(1, &FBOTexture_RGB);
	glBindTexture(GL_TEXTURE_2D, FBOTexture_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Config::Screen_width, Config::Screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBOTexture_RGB, 0);

	GLuint RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Config::Screen_width, Config::Screen_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error::FrameBuffer::FrameBuffer is not complete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		// 检查并调用事件
		glfwPollEvents();	

		// 处理输入事件 
		processInput(window);

		camera_main->update();

		
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

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
		glStencilMask(0x00);
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
		//glCullFace(GL_FRONT);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glm::mat4 transform_cub = glm::mat4(1.0f);
		shader_obj.use();
		shader_obj.setMatrix4f("transform", transform_cub);
		shader_obj.setMatrix4f("view", view);
		shader_obj.setMatrix4f("projection", projection);
		model.draw(shader_obj);

		// cube
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
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
		

		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // RGBA使用相同的混合模式
		// glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO); // RGB使用一种混合模式，alpha使用一种混合模式
		// glBlendEquation(GL_FUNC_ADD); // 修改混合模式混合算法的运算符

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// 窗户
		for (int i = 0; i < 3; i++)
		{
			transform = glm::mat4(1.0f);
			transform = glm::translate(transform, window_pos_list[i]);
			transform = glm::scale(transform, glm::vec3(3.0f, 3.0f, 3.0f));
			glStencilMask(0x00);
			shader_gress.use();
			shader_gress.setMatrix4f("transform", transform);
			shader_gress.setMatrix4f("view", view);
			shader_gress.setMatrix4f("projection", projection);
			glBindVertexArray(VAO_plane);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, window_texture);
			shader_gress.setInt("diffuse_texture", 1);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// 草地
		for (int i =0; i < 4; i++)
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, grass_pos_list[i]);
			glStencilMask(0x00);
			shader_gress.use();
			shader_gress.setMatrix4f("transform", transform);
			shader_gress.setMatrix4f("view", view);
			shader_gress.setMatrix4f("projection", projection);
			glBindVertexArray(VAO_plane);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, grass_texture);
			shader_gress.setInt("diffuse_texture", 1);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		//// model outline
		//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//glStencilMask(0x00);
		//transform_cub = glm::mat4(1.0f);
		//shader_stencil.use();
		//shader_stencil.setMatrix4f("transform", transform_cub);
		//shader_stencil.setMatrix4f("view", view);
		//shader_stencil.setMatrix4f("projection", projection);
		//shader_stencil.setFloat("outline", 0.1f);
		//model.draw(shader_stencil);
		//glStencilMask(0xFF);
		//glEnable(GL_DEPTH_TEST);

		/**
			清理完模版数据
			第一次写入模版缓冲
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE) : 设置模版缓冲修改规则（模版缓冲写入规则，模版测试失败、模版深度测试失败、模版测试通过）
			glStencilFunc(GL_ALWAYS, 1, 0xFF): 设置模版缓冲测试通过规则 func测试方式:模版值与ref参考值对比方式; ref参考值:与模版对比的参考值; mask掩码:模版测试之前分别需要与模版值和参考值做与运算
			glStencilMask(0xFF): 设置模版缓冲写入掩码（与最终模版写入码做 与 运算）
			model.draw():渲染模型(与模版缓冲做测试，测试通过保留色值，并根据stencilop规则刷新模版数据)
		*/
		glClear(GL_STENCIL_BUFFER_BIT);
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(10.0f, 0.0f, 0.0f));
		glStencilMask(0xFF);

		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		glStencilFunc(GL_NEVER, 2, 0xFF);
		shader_stencil.use();
		shader_stencil.setMatrix4f("transform", transform);
		shader_stencil.setMatrix4f("view", view);
		shader_stencil.setMatrix4f("projection", projection);
		shader_stencil.setFloat("outline", 0.1f);
		model.draw(shader_stencil);

		glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
		glStencilFunc(GL_NEVER, 1, 0xFF);
		shader_obj.use();
		shader_obj.setMatrix4f("transform", transform);
		shader_obj.setMatrix4f("view", view);
		shader_obj.setMatrix4f("projection", projection);
		//shader_obj.setFloat("outline", 0.1f);
		model.draw(shader_obj);

		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_EQUAL, 2, 0xFF);
		shader_stencil.use();
		shader_stencil.setMatrix4f("transform", transform);
		shader_stencil.setMatrix4f("view", view);
		shader_stencil.setMatrix4f("projection", projection);
		shader_stencil.setFloat("outline", 0.1f);
		model.draw(shader_stencil);

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		//glEnable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(2.0f));
		//transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shader_frame.use();
		shader_frame.setMatrix4f("transform", transform);
		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);
		shader_frame.setMatrix4f("view", view);
		shader_frame.setMatrix4f("projection", projection);
		glBindVertexArray(VAO_plane);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, FBOTexture_RGB);
		shader_frame.setInt("testTexture", 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// 交换缓冲区
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO_cube);
	glDeleteVertexArrays(1, &VAO_plane);
	glDeleteBuffers(1, &VBO_cub);
	glDeleteBuffers(1, &VBO_panel);
	glDeleteFramebuffers(1, &FBO);
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
