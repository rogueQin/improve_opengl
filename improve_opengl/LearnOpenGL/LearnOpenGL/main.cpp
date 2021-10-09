
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
	-0.05f,  0.05f, 1.0f, 0.0f, 1.0f,
	 0.05f,  0.05f, 0.0f, 1.0f, 1.0f,
	 0.05f, -0.05f, 1.0f, 1.0f, 0.0f,

	 0.05f, -0.05f, 1.0f, 1.0f, 0.0f,
	-0.05f, -0.05f, 1.0f, 0.0f, 0.0f,
	-0.05f,  0.05f, 1.0f, 0.0f, 1.0f
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

	camera_main = new Camera(glm::vec3(0.0f, 50.0f, 50.0f), glm::vec3(0.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 100.0f);

	stbi_set_flip_vertically_on_load(true);

	//glEnable(GL_STENCIL_TEST);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS); //GL_ALWAYS、GL_NEVER、GL_LESS、GL_EQUAL、GL_LEQUAL

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);
	//glfwSetKeyCallback(window, key_callback);

	glm::vec2 instanceData[100];
	float offset = 0.1f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			instanceData[i * 10 + j] = glm::vec2((i - 5) / 5.0f + offset, (j - 5) / 5.0f + offset);
		}
	}

	GLuint instance_VBO;
	glGenBuffers(1, &instance_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &instanceData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Model model_planet = Model("../LearnOpenGL/res/planet/planet.obj");
	Model model_rock = Model("../LearnOpenGL/res/rock/rock.obj");

	unsigned int amount = 1000;
	glm::mat4 * model_matrices;
	model_matrices = new glm::mat4[amount];
	srand(glfwGetTime());
	float radius = 30.0f;
	offset = 2.5f;
	for (int i = 0; i < amount; i ++)
	{
		glm::mat4 trans = glm::mat4(1.0f);

		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;

		trans = glm::translate(trans, glm::vec3(x, y, z));

		float scale = (rand() % 20) / 100.0f + 0.05f;
		trans = glm::scale(trans, glm::vec3(scale));

		float rotAngle = (rand() % 360);
		trans = glm::rotate(trans, rotAngle, glm::vec3(0.4, 0.6, 0.8));

		model_matrices[i] = trans;
	}

	GLuint rock_ins_VBO;
	glGenBuffers(1, &rock_ins_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, rock_ins_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * amount, model_matrices, GL_STATIC_DRAW);
	model_rock.setInstanceArray(rock_ins_VBO);

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

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(2, 1);
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
	//Shader shader_obj = Shader("../LearnOpenGL/res/shader.vs", "../LearnOpenGL/res/shader.fs", "../LearnOpenGL/res/shader.gs");
	Shader shader_obj = Shader("../LearnOpenGL/res/shader_model.vs", "../LearnOpenGL/res/shader_model.fs");
	Shader shader_obj_ins = Shader("../LearnOpenGL/res/shader_model_instance.vs", "../LearnOpenGL/res/shader_model_instance.fs");
	Shader shader_normal = Shader("../LearnOpenGL/res/shader_normal.vs", "../LearnOpenGL/res/shader_normal.fs", "../LearnOpenGL/res/shader_normal.gs");
	Shader shader_gress = Shader("../LearnOpenGL/res/shader_blend.vs", "../LearnOpenGL/res/shader_blend.fs");
	Shader shader_frame = Shader("../LearnOpenGL/res/shader_light.vs", "../LearnOpenGL/res/shader_frame.fs");
	Shader shader_skybox = Shader("../LearnOpenGL/res/shader_skybox.vs", "../LearnOpenGL/res/shader_skybox.fs");
	Shader shader_geometry = Shader("../LearnOpenGL/res/shader_gs_test.vs", "../LearnOpenGL/res/shader_gs_test.fs", "../LearnOpenGL/res/shader_gs_test.gs");
	Shader shader_instance = Shader("../LearnOpenGL/res/shader_instance.vs", "../LearnOpenGL/res/shader_instance.fs");

	//Model model = Model("../LearnOpenGL/res/nanosuit/nanosuit.obj");

	camera_main->update();
	glm::mat4 view = camera_main->getView();
	glm::mat4 projection = camera_main->getProjection();

	shader_obj.setBlock("Camera", 0);
	// shader_normal.setBlock("Camera", 0);

	GLuint UBO_camera;
	glGenBuffers(1, &UBO_camera);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO_camera);
	glBufferData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO_camera, 0, 2*sizeof(glm::mat4));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));

	while (!glfwWindowShouldClose(window))
	{
		// 检查并调用事件
		glfwPollEvents();	

		// 处理输入事件 
		processInput(window);

		//camera_main->update();

		// 处理渲染指令
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		glm::mat4 transform = glm::mat4(1.0);
		shader_obj.use();
		shader_obj.setMatrix4f("transform", transform);
		model_planet.draw(shader_obj);

		//for (int i = 0; i < amount; i ++)
		//{
		//	shader_obj_ins.use();
		//	shader_obj_ins.setMatrix4f("transform", model_matrices[i]);
		//	model_rock.draw(shader_obj_ins);
		//}
		shader_obj_ins.use();
		model_rock.drawInstance(shader_obj_ins, amount);

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
