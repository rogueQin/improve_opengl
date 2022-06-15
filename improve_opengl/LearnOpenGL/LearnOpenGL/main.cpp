
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>
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
#include "Sphere.h"
#include "Panel.h"

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

Sphere * sphere[100];

Model * cerberus;

Cube * sky_box;
Panel * pane_lut;

RenderCube * renderCube;
RenderCube * irradianceCube;
RenderCube * prefilterCube;
RenderBuffer * PreBRDFbuffer;


Shader * shader_equipmap_cub;
Shader * shader_irradiance_cub;
Shader * shader_prefilter_cub;
Shader * shader_prebuild_brdf;
Shader * shader_panel;
Shader * shader_light;
Shader * shader_model;
Shader * shader_skybox;

GLuint texture_albedo;
GLuint texture_normal;
GLuint texture_metallic;
GLuint texture_roughness;
GLuint texture_ao;
GLuint texture_er_map;


glm::vec3 model_pos_lit[] = {
	glm::vec3(-3.0f, 0.0f, -3.0f),
	glm::vec3(-1.0f, 0.0f, -3.0f),	
	glm::vec3(1.0f, 0.0f, -3.0f),
	glm::vec3(3.0f, 0.0f, -3.0f),

	glm::vec3(-3.0f, 0.0f, -1.0f),
	glm::vec3(-1.0f, 0.0f, -1.0f),
	glm::vec3(1.0f, 0.0f, -1.0f),
	glm::vec3(3.0f, 0.0f, -1.0f),

	glm::vec3(-3.0f, 0.0f, 1.0f),
	glm::vec3(-1.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(3.0f, 0.0f, 1.0f),

	glm::vec3(-3.0f, 0.0f, 3.0f),
	glm::vec3(-1.0f, 0.0f, 3.0f),
	glm::vec3(1.0f, 0.0f, 3.0f),
	glm::vec3(3.0f, 0.0f, 3.0f)
};

glm::vec3 light_pos_list[] = {
	glm::vec3(10.0f, 5.0f, -10.0f),
	glm::vec3(-10.0f, 5.0f, -10.0f),
	glm::vec3(-10.0f, 5.0f, 10.0f),
	glm::vec3(10.0f, 5.0f, 10.0f)
};

glm::vec3 light_color_list[] = {
	glm::vec3(1.1),
	glm::vec3(1.1,0,1.1),
	glm::vec3(0,0,1.1)
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window);

void key_callback(GLFWwindow * window, int key, int scancode, int actin, int mods);

void mouse_callback(GLFWwindow * window, double xpos, double ypos);

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

void preRender();

unsigned int loadTexture(std::string fileName);
unsigned int loadEquirectangularMap(std::string fileName);
unsigned int loadCubeMap(std::vector<std::string> faces);
int renderPanel(GLfloat * vertex_input, GLfloat * vertex_output);

GLfloat lerp(GLfloat a, GLfloat b, GLfloat f);

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

	camera_main = new Camera(glm::vec3(0.0f, 6.0f, 7.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 50.0f);
	//camera_main = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 50.0f);

	stbi_set_flip_vertically_on_load(true);	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_MULTISAMPLE);
	glDepthFunc(GL_LEQUAL); //GL_ALWAYS、GL_NEVER、GL_LESS、GL_EQUAL、GL_LEQUAL

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetKeyCallback(window, key_callback);

	for (int i= 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			sphere[i * 10 + j] = new Sphere(glm::vec3(i - 5, 0, j -  5), glm::vec3(0), glm::vec3(0.4));
		}
	}

	//sphere[0] = new Sphere(glm::vec3(-1, 0, -1), glm::vec3(0), glm::vec3(0.8));
	//sphere[1] = new Sphere(glm::vec3(-1, 0, 1), glm::vec3(0), glm::vec3(0.8));
	//sphere[2] = new Sphere(glm::vec3(1, 0, 1), glm::vec3(0), glm::vec3(0.8));
	//sphere[3] = new Sphere(glm::vec3(1, 0, -1), glm::vec3(0), glm::vec3(0.8));

	sky_box = new Cube(glm::vec3(0), glm::vec3(0), glm::vec3(2));
	cerberus = new Model("../LearnOpenGL/res/res_530/cerberus/Cerberus_LP.FBX", true);

	pane_lut = new Panel(glm::vec3(0), glm::vec3(0), glm::vec3(2, 2, 1));

	renderCube = new RenderCube(1024, 1024, true);
	irradianceCube = new RenderCube(32, 32);
	prefilterCube = new RenderCube(256, 256, true);
	PreBRDFbuffer = new RenderBuffer(512, 512);

	shader_equipmap_cub = new Shader("../LearnOpenGL/res/res_530/shader_530_equip_cub.vs", "../LearnOpenGL/res/res_530/shader_530_equip_cub.fs", "../LearnOpenGL/res/res_530/shader_530_equip_cub.gs");
	shader_irradiance_cub = new Shader("../LearnOpenGL/res/res_530/shader_530_irradiance_cub.vs", "../LearnOpenGL/res/res_530/shader_530_irradiance_cub.fs", "../LearnOpenGL/res/res_530/shader_530_irradiance_cub.gs");
	shader_prefilter_cub = new Shader("../LearnOpenGL/res/res_530/shader_530_filter_cub.vs", "../LearnOpenGL/res/res_530/shader_530_filter_cub.fs", "../LearnOpenGL/res/res_530/shader_530_filter_cub.gs");
	shader_prebuild_brdf = new Shader("../LearnOpenGL/res/res_530/shader_530_brdf.vs", "../LearnOpenGL/res/res_530/shader_530_brdf.fs");
	shader_panel = new Shader("../LearnOpenGL/res/res_530/shader_530_panel.vs", "../LearnOpenGL/res/res_530/shader_530_panel.fs");
	shader_light = new Shader("../LearnOpenGL/res/res_530/shader_530_light.vs", "../LearnOpenGL/res/res_530/shader_530_light.fs");
	shader_model = new Shader("../LearnOpenGL/res/res_530/shader_530_model.vs", "../LearnOpenGL/res/res_530/shader_530_model.fs");
	shader_skybox = new Shader("../LearnOpenGL/res/res_530/shader_530_cubmap.vs", "../LearnOpenGL/res/res_530/shader_530_cubmap.fs");

	texture_albedo = loadTexture("../LearnOpenGL/res/res_530/rustediron2_basecolor.png");
	texture_normal = loadTexture("../LearnOpenGL/res/res_530/rustediron2_normal.png");
	texture_metallic = loadTexture("../LearnOpenGL/res/res_530/rustediron2_metallic.png");
	texture_roughness = loadTexture("../LearnOpenGL/res/res_530/rustediron2_roughness.png");
	texture_ao = loadTexture("../LearnOpenGL/res/res_530/rustediron2_ao.png");
	texture_er_map = loadEquirectangularMap("../LearnOpenGL/res/res_530/MonValley_G_DirtRoad_8k.jpg");

	camera_main->update();
	glm::mat4 view = camera_main->getView();
	glm::mat4 projection = camera_main->getProjection();

	shader_light->setBlock("Camera", 0);
	shader_skybox->setBlock("Camera", 0);
	shader_panel->setBlock("Camera", 0);

	GLuint UBO_camera;
	glGenBuffers(1, &UBO_camera);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO_camera);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO_camera, 0, 2 * sizeof(glm::mat4));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// 预渲染场景天空盒
	preRender();

	while (!glfwWindowShouldClose(window))
	{
		// 检查并调用事件
		glfwPollEvents();	
		// 处理输入事件 
		processInput(window);
		
		glm::mat4 trans = glm::mat4(1.0f);
		camera_main->update();
		view = camera_main->getView();
		projection = camera_main->getProjection();
		
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));

		
		// 渲染场景
		glViewport(0, 0, Config::Screen_width, Config::Screen_height);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// pbr
		shader_light->use();
		shader_light->setVec3f("camPos", camera_main->getCameraPosition());
		shader_light->setInt("image_irradiance_cube", 0);
		shader_light->setInt("image_prefilter_cube", 1);
		shader_light->setInt("image_brdf_LUT", 2);

		shader_light->setVec3f("albedo", glm::vec3(0.5f,0.0f,0.0f));
		shader_light->setFloat("ao", 1.0f);




		//shader_light->setInt("image_albedo", 3);
		//shader_light->setInt("image_normal", 4);
		//shader_light->setInt("image_ao", 5);
		//shader_light->setInt("image_metallic", 6);
		//shader_light->setInt("image_roughness", 7);

		for (int i = 0; i < 4; i++)
		{
			shader_light->setVec3f("lightPosition[" + std::to_string(i) + "]", light_pos_list[i]);
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceCube->GetRenderCube());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterCube->GetRenderCube());

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, PreBRDFbuffer->GetRenderTexture());


		//glActiveTexture(GL_TEXTURE3);
		//glBindTexture(GL_TEXTURE_2D, texture_albedo);

		//glActiveTexture(GL_TEXTURE4);
		//glBindTexture(GL_TEXTURE_2D, texture_normal);

		//glActiveTexture(GL_TEXTURE5);
		//glBindTexture(GL_TEXTURE_2D, texture_ao);

		//glActiveTexture(GL_TEXTURE6);
		//glBindTexture(GL_TEXTURE_2D, texture_metallic);

		//glActiveTexture(GL_TEXTURE7);
		//glBindTexture(GL_TEXTURE_2D, texture_roughness);
		int nrRows = 10;
		int nrColumns = 10;
		for (int row = 0; row < nrRows; ++row)
		{
			shader_light->setFloat("metallic", (float)row / (float)nrRows);
			for (int col = 0; col < nrColumns; ++col)
			{
				// we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
				// on direct lighting.
				shader_light->setFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));

				//model = glm::mat4(1.0f);
				//model = glm::translate(model, glm::vec3(
				//	(float)(col - (nrColumns / 2)) * spacing,
				//	(float)(row - (nrRows / 2)) * spacing,
				//	-2.0f
				//));
				//pbrShader.setMat4("model", model);
				//renderSphere();
				sphere[row * nrColumns + col]->renderSphere(shader_light);
			}
		}

		//for (int i = 0; i < 4; i++)
		//{
		//	shader_light->setFloat("metallic", 1.0 / (float)(4 - i));
		//	shader_light->setFloat("roughness", 1.0 / (float)(i + 1));
		//	sphere[i]->renderSphere(shader_light);
		//}


		// 天空盒
		shader_skybox->use();
		shader_skybox->setInt("image_cube", 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, renderCube->GetRenderCube());

		sky_box->renderCube(shader_skybox);


		// 交换缓冲区
		glfwSwapBuffers(window);
	}

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
	glm::mat4 trans = glm::mat4(1.0f);
}

void renderLight(Shader * render_shader)
{
}

GLfloat lerp(GLfloat a, GLfloat b, GLfloat f) 
{
	return a + f * (b - a);
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

void preRender() 
{
	glm::mat4 trans = glm::mat4(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	trans = glm::mat4(1.0f);

	// cube_map
	shader_equipmap_cub->use();
	shader_equipmap_cub->setInt("image_equimap", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_er_map);

	renderCube->use(shader_equipmap_cub, glm::vec3(0));
	sky_box->renderCube(shader_equipmap_cub);
	renderCube->generateMipmap();

	// irradiance_map
	shader_irradiance_cub->use();
	shader_irradiance_cub->setInt("image_cube", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, renderCube->GetRenderCube());

	irradianceCube->use(shader_irradiance_cub, glm::vec3(0));
	sky_box->renderCube(shader_irradiance_cub);

	// prefilter_cub_map
	shader_prefilter_cub->use();
	shader_prefilter_cub->setInt("image_cube", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, renderCube->GetRenderCube());

	int width = 256;
	int height = 256;
	float roughness = 0;

	for (GLuint mip = 0; mip < 5; mip++)
	{
		width = 256 * std::pow(0.5, mip);
		height = 256 * std::pow(0.5, mip);
		roughness = (float)mip / 4.0f;

		shader_prefilter_cub->setFloat("roughness", roughness);
		prefilterCube->useMipMap(shader_prefilter_cub, glm::vec3(0), mip, width, height);
		//prefilterCube->use(shader_prefilter_cub, glm::vec3(0));
		sky_box->renderCube(shader_prefilter_cub);
	}

	// prebuild BRDF
	shader_prebuild_brdf->use();
	PreBRDFbuffer->use();
	pane_lut->renderPanel(shader_prebuild_brdf);
}

unsigned int loadEquirectangularMap(std::string fileName)
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

	float * data = stbi_loadf(file_path.c_str(), &width, &height, &nrChanels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16, width, height, 0, GL_RGB, GL_FLOAT, data);
	}
	else
	{
		std::cout << "Failed to load Equirectangular texture!" << std::endl;
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
