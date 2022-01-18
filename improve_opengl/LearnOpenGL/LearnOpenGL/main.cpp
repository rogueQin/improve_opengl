
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
#include "Cube.h"
#include "RenderBuffer.h"
#include "RenderCube.h"
#include "SkyBox.h"


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

GLfloat vertices_ground[] = {

	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 5.0f, 5.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 5.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 5.0f, 5.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 5.0f, 0.0f,

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
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 5.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 5.0f, 5.0f,

	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 5.0f, 5.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 5.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
};

GLfloat vertices_panel [] = {
	 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
						
	 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
};

GLfloat vertices_normal_map_panel[] = {
	 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

	 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
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
	glm::vec3(-1.6, 2, 1.2),
	glm::vec3(-1.6, 1, -1.2),
	glm::vec3(1.2, 2, 0.8)
};

glm::vec3 light_color_list[] = {
	glm::vec3(1.1),
	glm::vec3(1.1,0,1.1),
	glm::vec3(0,0,1.1)
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

void renderScene(Shader * render_shader);

void renderLight(Shader * render_shader);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window);

void key_callback(GLFWwindow * window, int key, int scancode, int actin, int mods);

void mouse_callback(GLFWwindow * window, double xpos, double ypos);

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

unsigned int loadTexture(std::string fileName);
unsigned int loadCubeMap(std::vector<std::string> faces);
int renderPanel(GLfloat * vertex_input, GLfloat * vertex_output);

Cube * cube_ground;

Cube * cube_box_1;
Cube * cube_box_2;
Cube * cube_box_3;
Cube * cube_box_4;

Cube * cube_light_1;
Cube * cube_light_2;
Cube * cube_light_3;

int main() 
{
	// 初始化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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

	camera_main = new Camera(glm::vec3(0.0f, 7.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 100.0f);

	stbi_set_flip_vertically_on_load(true);	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_MULTISAMPLE);
	//glDepthFunc(GL_LESS); //GL_ALWAYS、GL_NEVER、GL_LESS、GL_EQUAL、GL_LEQUAL

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetKeyCallback(window, key_callback);


	cube_ground = new Cube(vertices_ground, glm::vec3(0, -0.01f, 0), glm::vec3(0,0,0), glm::vec3(8, 0.02f, 8));

	cube_box_1 = new Cube(vertices_cube, glm::vec3(2, 1, 2), glm::vec3(45, 45, 45), glm::vec3(0.8));
	cube_box_2 = new Cube(vertices_cube, glm::vec3(2, 2.4, -2), glm::vec3(30, 45, 60), glm::vec3(0.8));
	cube_box_3 = new Cube(vertices_cube, glm::vec3(-2, 2.8, 2), glm::vec3(45, 40, 50), glm::vec3(0.8));
	cube_box_4 = new Cube(vertices_cube, glm::vec3(-2, 1.2, -2), glm::vec3(50, 80, 70), glm::vec3(0.8));

	cube_light_1 = new Cube(vertices_cube, light_pos_list[0], glm::vec3(0), glm::vec3(0.5));
	cube_light_2 = new Cube(vertices_cube, light_pos_list[1], glm::vec3(0), glm::vec3(0.5));
	cube_light_3 = new Cube(vertices_cube, light_pos_list[2], glm::vec3(0), glm::vec3(0.5));

	GLuint wood = loadTexture("../LearnOpenGL/res/res_470/wood.png");
	GLuint container2 = loadTexture("../LearnOpenGL/res/res_470/container2.png");
	GLuint container2_specular = loadTexture("../LearnOpenGL/res/res_470/container2_specular.png");
	GLuint toy_box_normal = loadTexture("../LearnOpenGL/res/res_470/toy_box_normal.png");
	GLuint toy_box_disp = loadTexture("../LearnOpenGL/res/res_470/toy_box_disp.png");

	std::cout << glGetError() << std::endl;

	Shader * shader_scene = new Shader("../LearnOpenGL/res/res_470/shader_470_scene.vs", "../LearnOpenGL/res/res_470/shader_470_scene.fs");
	Shader * shader_light = new Shader("../LearnOpenGL/res/res_470/shader_470_light.vs", "../LearnOpenGL/res/res_470/shader_470_light.fs");
	Shader * shader_blur = new Shader("../LearnOpenGL/res/res_470/shader_470_blur.vs", "../LearnOpenGL/res/res_470/shader_470_blur.fs");
	Shader * shader_hdr = new Shader("../LearnOpenGL/res/res_470/shader_470_hdr.vs", "../LearnOpenGL/res/res_470/shader_470_hdr.fs");

	camera_main->update();
	glm::mat4 view = camera_main->getView();
	glm::mat4 projection = camera_main->getProjection();

	shader_scene->setBlock("Camera", 0);
	shader_light->setBlock("Camera", 0);

	GLuint UBO_camera;
	glGenBuffers(1, &UBO_camera);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO_camera);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO_camera, 0, 2 * sizeof(glm::mat4));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));

	// 帧缓冲
	GLuint FBO_scene;
	glGenFramebuffers(1, &FBO_scene);

	GLfloat borderColor[4] = { 1.0, 1.0, 1.0, 1.0 };
	// 场景纹理缓冲附件
	GLuint texture_scene_frag;
	glGenTextures(1, &texture_scene_frag);
	glBindTexture(GL_TEXTURE_2D, texture_scene_frag);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Config::Screen_width, Config::Screen_height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// 场景纹理缓冲附件
	GLuint texture_scene_bloom;
	glGenTextures(1, &texture_scene_bloom);
	glBindTexture(GL_TEXTURE_2D, texture_scene_bloom);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Config::Screen_width, Config::Screen_height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// 渲染缓冲对象附件
	GLuint RBO_scene;
	glGenRenderbuffers(1, &RBO_scene);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO_scene);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Config::Screen_width, Config::Screen_height);
	
	glBindFramebuffer(GL_FRAMEBUFFER, FBO_scene);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_scene_frag, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, texture_scene_bloom, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO_scene);

	GLuint attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(2, attachments);

	// 帧缓冲状态检测
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR:FRAMEBUFFER:: framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	GLfloat blurBorderColor[4] = { 0.0, 0.0, 0.0, 1.0 };

	// 横向模糊缓冲
	GLuint FBO_blur[2];
	glGenFramebuffers(2, FBO_blur);

	// 横向模糊纹理缓冲附件
	GLuint texture_blur[2];
	glGenTextures(2, texture_blur);

	for (int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture_blur[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Config::Screen_width, Config::Screen_height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, blurBorderColor);

		glBindFramebuffer(GL_FRAMEBUFFER, FBO_blur[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_blur[i], 0);

		// 帧缓冲状态检测
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR:FRAMEBUFFER:: framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// 显示面板
	GLuint VBO_view;
	glGenBuffers(1, &VBO_view);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_view);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_panel), vertices_panel, GL_STATIC_DRAW);

	GLuint VAO_view;
	glGenVertexArrays(1, &VAO_view);
	glBindVertexArray(VAO_view);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);


	// panel数据
	GLfloat *Panel_triangle_1 = new GLfloat[42]();
	GLfloat *Panel_triangle_2 = new GLfloat[42]();
	int triangle_length_1, triangle_length_2;
	triangle_length_1 = renderPanel(&vertices_normal_map_panel[0], Panel_triangle_1);
	triangle_length_2 = renderPanel(&vertices_normal_map_panel[24], Panel_triangle_2);
	
	GLfloat panel_triangle[84];
	for (int i = 0; i < 42; i++)
	{
		panel_triangle[i] = Panel_triangle_1[i];
		panel_triangle[42 + i] = Panel_triangle_2[i];
	}

	GLuint VBO_Normal_Panel;
	glGenBuffers(1, &VBO_Normal_Panel);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normal_Panel);
	glBufferData(GL_ARRAY_BUFFER, sizeof(panel_triangle), panel_triangle, GL_STATIC_DRAW);

	GLuint VAO_Normal_Panel;
	glGenVertexArrays(1, &VAO_Normal_Panel);
	glBindVertexArray(VAO_Normal_Panel);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
		glEnableVertexAttribArray(4);
	glBindVertexArray(0);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	while (!glfwWindowShouldClose(window))
	{
		// 检查并调用事件
		glfwPollEvents();	
		// 处理输入事件 
		processInput(window);
		
		glBindFramebuffer(GL_FRAMEBUFFER, FBO_scene);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 lightPos = glm::vec3(0.0f, 5.0f, 0.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		
		lightPos.x = 2.0 * glm::sin((float)glfwGetTime() * glm::radians(50.0f));
		lightPos.z = 2.0 * glm::cos((float)glfwGetTime() * glm::radians(50.0f));

		camera_main->update();
		view = camera_main->getView();
		projection = camera_main->getProjection();
		
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));

		trans = glm::mat4(1.0f);

		shader_scene->use();
		shader_scene->setInt("material.texture_diffuse1", 0);
		shader_scene->setInt("material.texture_specular1", 1);
		shader_scene->setInt("material.texture_normal1", 2);
		shader_scene->setInt("material.texture_diplamence1", 3);

		shader_scene->setFloat("material.height_scale", 0.2f);
		shader_scene->setFloat("material.shininess", 32.0f);

		shader_scene->setVec3f("directionLightPos", lightPos);
		shader_scene->setVec3f("directionLight.ambient", glm::vec3(0.2f));
		shader_scene->setVec3f("directionLight.diffuse", glm::vec3(0.5f));
		shader_scene->setVec3f("directionLight.specular", glm::vec3(1.0f));

		for (int i = 0; i < 3; i++)
		{
			shader_scene->setVec3f("pointLightPos[" + std::to_string(i) + "]", light_pos_list[i]);
			shader_scene->setVec3f("pointLights[" + std::to_string(i) + "].ambient", light_color_list[i] * 0.2f);
			shader_scene->setVec3f("pointLights[" + std::to_string(i) + "].diffuse", light_color_list[i] * 0.5f);
			shader_scene->setVec3f("pointLights[" + std::to_string(i) + "].specular", light_color_list[i] * 1.0f);

			shader_scene->setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
			shader_scene->setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09f);
			shader_scene->setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
		}

		shader_scene->setVec3f("viewPos", camera_main->getCameraPosition());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, container2);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, container2_specular);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, toy_box_normal);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, toy_box_disp);

		renderScene(shader_scene);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wood);

		cube_ground->renderCube(shader_scene);

		shader_light->use();
		renderLight(shader_light);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// 高斯模糊
		trans = glm::mat4(1.0f);
		shader_blur->use();
		shader_blur->setMatrix4f("model", trans);
		shader_blur->setInt("image", 0);

		bool horizontal = true;
		for (int i = 0; i < 20; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, FBO_blur[i % 2]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			shader_blur->setBool("horizontal", horizontal);
			horizontal = !horizontal;
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, i == 0 ? texture_scene_bloom : texture_blur[(i + 1) % 2]);

			glBindVertexArray(VAO_view);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		// 显示
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader_hdr->use();
		shader_hdr->setMatrix4f("model", trans);
		shader_hdr->setInt("FragImg", 0);
		shader_hdr->setInt("FragImg", 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_scene_frag);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_blur[1]);

		glBindVertexArray(VAO_view);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// 交换缓冲区
		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &VBO_Normal_Panel);
	glDeleteBuffers(1, &VAO_Normal_Panel);

	glfwTerminate();
	 
	return 0;
}

int renderPanel(GLfloat * vertex_input, GLfloat * vertex_output)
{
	glm::vec3 pos1 = glm::vec3(vertex_input[0], vertex_input[1], vertex_input[2]);
	glm::vec3 pos2 = glm::vec3(vertex_input[8], vertex_input[9], vertex_input[10]);
	glm::vec3 pos3 = glm::vec3(vertex_input[16], vertex_input[17], vertex_input[18]);
		
	glm::vec2 uv1 = glm::vec2(vertex_input[6], vertex_input[7]);
	glm::vec2 uv2 = glm::vec2(vertex_input[14], vertex_input[15]);
	glm::vec2 uv3 = glm::vec2(vertex_input[22], vertex_input[23]);

	glm::vec3 norm1 = glm::vec3(vertex_input[3], vertex_input[4], vertex_input[5]);
	glm::vec3 norm2 = glm::vec3(vertex_input[11], vertex_input[12], vertex_input[13]);
	glm::vec3 norm3 = glm::vec3(vertex_input[19], vertex_input[20], vertex_input[21]);

	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;

	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	glm::vec3 tangent, bitangent;

	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent = glm::normalize(tangent);

	bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent = glm::normalize(bitangent);

	GLfloat * vertex_array = new GLfloat[42]{
		pos1.x, pos1.y, pos1.z, norm1.x, norm1.y, norm1.z, uv1.x, uv1.y, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z,
		pos2.x, pos2.y, pos2.z, norm2.x, norm2.y, norm2.z, uv2.x, uv2.y, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z,
		pos3.x, pos3.y, pos3.z, norm3.x, norm3.y, norm3.z, uv3.x, uv3.y, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z
	};
	for (int i = 0; i < 42; i++)
	{
		if (vertex_array[i] > -0.001f && vertex_array[i] < 0.001f)
		{
			vertex_array[i] = 0.0f;
		}
		if (vertex_array[i] < 1.001f && vertex_array[i] > 0.999f)
		{
			vertex_array[i] = 1.0f;
		}
		if (vertex_array[i] > -1.001f && vertex_array[i] < -0.999f)
		{
			vertex_array[i] = -1.0f;
		}

		vertex_output[i] = vertex_array[i];
	}

	return 42;
}

void renderScene(Shader * render_shader) 
{
	cube_box_1->renderCube(render_shader);
	cube_box_2->renderCube(render_shader);
	cube_box_3->renderCube(render_shader);
	cube_box_4->renderCube(render_shader);
}

void renderLight(Shader * render_shader)
{
	render_shader->setVec3f("LightColor", light_color_list[0]);
	cube_light_1->renderCube(render_shader);

	render_shader->setVec3f("LightColor", light_color_list[1]);
	cube_light_2->renderCube(render_shader);

	render_shader->setVec3f("LightColor", light_color_list[2]);
	cube_light_3->renderCube(render_shader);
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
