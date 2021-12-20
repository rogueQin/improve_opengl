
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

		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,

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


};

GLfloat vertices_panel [] = {
	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 5.0f,
	 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f,
	 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 0.0f,
						
	 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 5.0f
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
	glfwWindowHint(GLFW_SAMPLES, 4);
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

	camera_main = new Camera(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 100.0f);
	// camera_main = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 100.0f);
	// camera_main = new Camera(glm::vec3(7.0f, 7.0f, -7.0f), glm::vec3(-7.0f, -7.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 100.0f);

	stbi_set_flip_vertically_on_load(true);	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_MULTISAMPLE);
	//glDepthFunc(GL_LESS); //GL_ALWAYS、GL_NEVER、GL_LESS、GL_EQUAL、GL_LEQUAL

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetKeyCallback(window, key_callback);

	
	GLuint VBO_panel;
	glGenBuffers(1, &VBO_panel);
	// 设置顶点缓冲对象缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO_panel);
	// 向缓冲区中写入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_panel), vertices_panel, GL_STATIC_DRAW);
	
	GLuint VAO_panel;
	glGenVertexArrays(1, &VAO_panel);
	glBindVertexArray(VAO_panel);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	GLuint VAO_BG;
	glGenVertexArrays(1, &VAO_BG);
	glBindVertexArray(VAO_BG);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// 
	GLuint VBO_box;
	glGenBuffers(1, &VBO_box);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

	GLuint VAO_box;
	glGenVertexArrays(1, &VAO_box);
	glBindVertexArray(VAO_box);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// 帧缓冲对象 depth map buffer
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// 纹理缓冲附件
	unsigned int depthMapTexture;
	glGenTextures(1, &depthMapTexture);
	glBindTexture(GL_TEXTURE_2D, depthMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Config::DepthMap_width, Config::DepthMap_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 渲染缓冲对象附件
	unsigned int depthMapRBO;
	glGenRenderbuffers(1, &depthMapRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, depthMapRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Config::Screen_width, Config::Screen_height);
	
	// 帧缓冲状态检测
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthMapRBO);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR:FRAMEBUFFER:: framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

	//Model model_planet = Model("../LearnOpenGL/res/planet/planet.obj");
	//Model model_rock = Model("../LearnOpenGL/res/rock/rock.obj");
	//Model model_nanosuit = Model("../LearnOpenGL/res/nanosuit/nanosuit.obj");

	// unsigned int cube_texture = loadTexture("../LearnOpenGL/res/container2.png");
	 unsigned int floor_texture = loadTexture("../LearnOpenGL/res/wood.png");
	//unsigned int pushYourLuck_texture = loadTexture("../LearnOpenGL/res/GameObject.png");
	//unsigned int pushYourBG_texture = loadTexture("../LearnOpenGL/res/GameBG.png");
	// unsigned int grass_texture = loadTexture("../LearnOpenGL/res/grass.png");
	// unsigned int window_texture = loadTexture("../LearnOpenGL/res/blending_transparent_window.png");	

	Shader shader_light_view = Shader("../LearnOpenGL/res/shader_431_light_view.vs", "../LearnOpenGL/res/shader_431_light_view.fs");
	Shader shader_depth_view = Shader("../LearnOpenGL/res/shader_431_depth_view.vs", "../LearnOpenGL/res/shader_431_depth_view.fs");
	Shader shader_shadow_mapping = Shader("../LearnOpenGL/res/shader_431_shadow_mapping.vs", "../LearnOpenGL/res/shader_431_shadow_mapping.fs");

	camera_main->update();
	glm::mat4 view = camera_main->getView();
	glm::mat4 projection = camera_main->getProjection();

	shader_shadow_mapping.setBlock("Camera", 0);

	GLuint UBO_camera;
	glGenBuffers(1, &UBO_camera);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO_camera);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO_camera, 0, 2 * sizeof(glm::mat4));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));


	while (!glfwWindowShouldClose(window))
	{
		// 检查并调用事件
		glfwPollEvents();	
		// 处理输入事件 
		processInput(window);

		glm::mat4 trans = glm::mat4(1.0f);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 生成深度缓冲
		glViewport(0, 0, Config::DepthMap_width, Config::DepthMap_height);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		glm::vec3 light_position = glm::vec3(7.0f, 7.0f, -7.0f);
		glm::mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 25.0f);
		glm::mat4 light_view = glm::lookAt(light_position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightSpaceMatrix = light_projection * light_view;

		shader_light_view.use();
		shader_light_view.setMatrix4f("light_space_matrix", lightSpaceMatrix);

		trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::scale(trans, glm::vec3(10, 10, 1));
		shader_light_view.setMatrix4f("transform", trans);
		glBindVertexArray(VAO_BG);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-3, 1.5, -3));
		shader_light_view.setMatrix4f("transform", trans);
		glBindVertexArray(VAO_box);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0, 0.6, 0));
		shader_light_view.setMatrix4f("transform", trans);
		glBindVertexArray(VAO_box);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(2, 2, 0));
		shader_light_view.setMatrix4f("transform", trans);
		glBindVertexArray(VAO_box);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);



		
		/** 
		
		// 渲染深度贴图
		glViewport(0, 0, Config::Screen_width, Config::Screen_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera_main->setCameraPosition(glm::vec3(0.0f, 0.0f, 5.0f));
		camera_main->setCameraFront(glm::vec3(0.0f, 0.0f, -5.0f));
		camera_main->setCameraUp(glm::vec3(0.0f, 1.0f, 0.0f));
		camera_main->update();
		view = camera_main->getView();
		projection = camera_main->getProjection();

		shader_depth_view.use();
		shader_depth_view.setMatrix4f("view", view);
		shader_depth_view.setMatrix4f("projection", projection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMapTexture);

		shader_depth_view.setInt("texture_diffuse", 0); 

		trans = glm::mat4(1.0f);
		trans = glm::scale(trans, glm::vec3(1.5));
		shader_depth_view.setMatrix4f("transform", trans);

		glBindVertexArray(VAO_panel);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		*/


		// 处理渲染指令
		glViewport(0, 0, Config::Screen_width, Config::Screen_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera_main->update();
		view = camera_main->getView();
		projection = camera_main->getProjection();
		
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
		// glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(render_distance));

		shader_shadow_mapping.use();
		// material
		shader_shadow_mapping.setFloat("material.shininess", 32.0f);
		// camera
		shader_shadow_mapping.setVec3f("viewPos", camera_main->getCameraPosition());
		
		// direction_light
		shader_shadow_mapping.setVec3f("directionLight.direction", glm::vec3(-1.0f, -1.0f, 1.0f));
		shader_shadow_mapping.setVec3f("directionLight.ambient", glm::vec3(0.2f));
		shader_shadow_mapping.setVec3f("directionLight.diffuse", glm::vec3(0.5f));
		shader_shadow_mapping.setVec3f("directionLight.specular", glm::vec3(1.0f));

		// texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floor_texture);
		shader_shadow_mapping.setInt("material.texture_diffuse1", 0);

		// shadow mapping
		shader_shadow_mapping.setMatrix4f("lightSpaceMatrix", lightSpaceMatrix);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMapTexture);
		shader_shadow_mapping.setInt("ShadowTexture", 1);
		
		// transform info
		trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::scale(trans, glm::vec3(10, 10, 1));
		shader_shadow_mapping.setMatrix4f("transform", trans);
		glBindVertexArray(VAO_BG);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		shader_shadow_mapping.setInt("material.texture_diffuse1", 0);
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-3, 1.5, -3));
		shader_shadow_mapping.setMatrix4f("transform", trans);
		glBindVertexArray(VAO_box);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		shader_shadow_mapping.setInt("material.texture_diffuse1", 0);
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0, 0.6, 0));
		shader_shadow_mapping.setMatrix4f("transform", trans);
		glBindVertexArray(VAO_box);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		shader_shadow_mapping.setInt("material.texture_diffuse1", 0);
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(2, 2, 0));
		shader_shadow_mapping.setMatrix4f("transform", trans);
		glBindVertexArray(VAO_box);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 交换缓冲区
		glfwSwapBuffers(window);
	}

	// glDeleteVertexArrays(1, &VAO_panel);
	// glDeleteVertexArrays(1, &VBO_panel);

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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
