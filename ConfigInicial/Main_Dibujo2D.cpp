// Angel Jesus Mendoza Rodriguez 
// Practica 2
// Fecha de entrega: 22 de agosto del 2025
// 319087288

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2 Angel Mendoza", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//1.0f,  0.1f, 0.0f,    1.0f,0.0f,0.0f,  // top right
		//0.5f, -0.5f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right
		//-0.5f, -0.5f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left
		//-0.5f,  0.5f, 0.0f,   1.0f,1.0f,0.0f, // top left 

		// Ojos 
		-0.12f, 0.12f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.08f, 0.12f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.12f, 0.08f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.08f, 0.08f, 0.0f,	0.0f, 0.0f, 0.0f,

		0.08f, 0.12f, 0.0f,		1.0f, 1.0f, 1.0f,// 5
		0.12f, 0.12f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.08f, 0.08f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.12f, 0.08f, 0.0f,		0.0f, 0.0f, 0.0f,

		// Cara-boca
		-0.2f, 0.04f, 0.0f,		0.97f, 0.8f, 0.56f, 
		-0.16f, 0.04f, 0.0f,	0.97f, 0.8f, 0.56f,
		-0.12f, 0.04f, 0.0f,	0.97f, 0.8f, 0.56f, //10
		-0.08f, 0.04f, 0.0f,	0.97f, 0.8f, 0.56f,
		-0.04f, 0.04f, 0.0f,	0.97f, 0.8f, 0.56f,
		0.0f, 0.04f, 0.0f,	0.97f, 0.8f, 0.56f,
		0.04f, 0.04f, 0.0f,		0.97f, 0.8f, 0.56f,
		0.08f, 0.04f, 0.0f,		0.97f, 0.8f, 0.56f,
		0.12f, 0.04f, 0.0f,		0.97f, 0.8f, 0.56f,
		0.16f, 0.04f, 0.0f,		0.97f, 0.8f, 0.56f,
		0.2f, 0.04f, 0.0f,		0.97f, 0.8f, 0.56f,

		-0.16f, 0.0f, 0.0f,		0.97f, 0.8f, 0.56f, //20
		-0.12f, 0.0f, 0.0f,		0.97f, 0.8f, 0.56f,
		-0.08f, 0.0f, 0.0f,		0.97f, 0.8f, 0.56f, 
		-0.04f, 0.0f, 0.0f,		0.97f, 0.8f, 0.56f,
		0.0f, 0.0f, 0.0f,	0.97f, 0.8f, 0.56f,
		0.04f, 0.0f, 0.0f,		0.97f, 0.8f, 0.56f,
		0.08f, 0.0f, 0.0f,		0.97f, 0.8f, 0.56f,
		0.12f, 0.0f, 0.0f,		0.97f, 0.8f, 0.56f, 
		0.16f, 0.0f, 0.0f,		0.97f, 0.8f, 0.56f,

		-0.12f, -0.04f, 0.0f,	0.97f, 0.8f, 0.56f, 
		-0.08f, -0.04f, 0.0f,	0.97f, 0.8f, 0.56f, //30
		-0.04f, -0.04f, 0.0f,	0.97f, 0.8f, 0.56f,
		0.0f, -0.04f, 0.0f,	0.97f, 0.8f, 0.56f,	
		0.04f, -0.04f, 0.0f,	0.97f, 0.8f, 0.56f,
		0.08f, -0.04f, 0.0f,	0.97f, 0.8f, 0.56f,
		0.12f, -0.04f, 0.0f,	0.97f, 0.8f, 0.56f, 

		//A de la mascara
		-0.04f, 0.4f, 0.0f,		1.0f, 1.0f, 1.0f,
		-0.0f, 0.4f,0.0f,		1.0f, 1.0f, 1.0f, 
		0.04f, 0.4f, 0.0f,		1.0f, 1.0f, 1.0f,
		
		-0.08f, 0.36f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.04f, 0.36f, 0.0f,	1.0f, 1.0f, 1.0f, //40
		0.0f, 0.36f,0.0f,		1.0f, 1.0f, 1.0f,
		0.04f, 0.36f, 0.0f,		1.0f, 1.0f, 1.0f,
		0.08f, 0.36f, 0.0f,		1.0f, 1.0f, 1.0f,

		-0.08f, 0.32f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.04f, 0.32f, 0.0f,	1.0f, 1.0f, 1.0f,
		//0.0f, 0.32f,0.0f,	1.0f, 1.0f, 1.0f, // Centro A
		0.04f, 0.32f, 0.0f,		1.0f, 1.0f, 1.0f,
		0.08f, 0.32f, 0.0f,		1.0f, 1.0f, 1.0f,
		
		-0.08f, 0.28f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.04f, 0.28f, 0.0f,	1.0f, 1.0f, 1.0f, 
		0.0f, 0.28f,0.0f,		1.0f, 1.0f, 1.0f,//50
		0.04f, 0.28f, 0.0f,		1.0f, 1.0f, 1.0f,
		0.08f, 0.28f, 0.0f,		1.0f, 1.0f, 1.0f,

		-0.08f, 0.24f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.04f, 0.24f, 0.0f,	1.0f, 1.0f, 1.0f,
		//0.0f, 0.24f,0.0f,	1.0f, 1.0f, 1.0f, //Apertura A
		0.04f, 0.24f, 0.0f,		1.0f, 1.0f, 1.0f,
		0.08f, 0.24f, 0.0f,		1.0f, 1.0f, 1.0f,

		// MASCARA DEL CAPITAN AMERICA
		-0.08f, 0.44f, 0.0f,	0.21f, 0.43f,0.96f,
		-0.04f, 0.44f, 0.0f,	0.21f, 0.43f,0.96f,
		0.0f, 0.44f, 0.0f,		0.21f, 0.43f,0.96f,
		0.04f, 0.44f, 0.0f,		0.21f, 0.43f,0.96f, //60
		0.08f, 0.44f, 0.0f,		0.21f, 0.43f,0.96f,

		-0.16f, 0.40f, 0.0f,	0.21f, 0.43f,0.96f,
		-0.12f, 0.40f, 0.0f,	0.21f, 0.43f,0.96f,
		-0.08f, 0.40f, 0.0f,	0.21f, 0.43f,0.96f,
		0.08f, 0.40f, 0.0f,		0.21f, 0.43f,0.96f,
		0.12f, 0.40f, 0.0f,		0.21f, 0.43f,0.96f,
		0.16f, 0.40f, 0.0f,		0.21f, 0.43f,0.96f,

		-0.2f, 0.36f, 0.0f,		0.21f, 0.43f,0.96f,
		-0.16f, 0.36f, 0.0f,	0.21f, 0.43f,0.96f,
		-0.12f, 0.36f, 0.0f,	0.21f, 0.43f,0.96f,//70
		0.12f, 0.36f, 0.0f,		0.21f, 0.43f,0.96f,
		0.16f, 0.36f, 0.0f,		0.21f, 0.43f,0.96f,
		0.2f, 0.36f, 0.0f,		0.21f, 0.43f,0.96f,

		-0.2f, 0.32f, 0.0f,		0.21f, 0.43f,0.96f,
		-0.16f, 0.32f, 0.0f,	0.21f, 0.43f,0.96f,
		-0.12f, 0.32f, 0.0f,	0.21f, 0.43f,0.96f,
		0.0f, 0.32f, 0.0f,		0.21f, 0.43f, 0.96f, // Centro A
		0.12f, 0.32f, 0.0f,		0.21f, 0.43f,0.96f,
		0.16f, 0.32f, 0.0f,		0.21f, 0.43f,0.96f,
		0.2f, 0.32f, 0.0f,		0.21f, 0.43f,0.96f, //80

		-0.24f, 0.28f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.2f, 0.28f, 0.0f,		0.21f, 0.43f, 0.96f,
		-0.16f, 0.28f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.12f, 0.28f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.12f, 0.28f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.16f, 0.28f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.2f, 0.28f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.24f, 0.28f, 0.0f,		0.21f, 0.43f, 0.96f,

		-0.24f, 0.24f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.2f, 0.24f, 0.0f,		0.21f, 0.43f, 0.96f,//90
		-0.16f, 0.24f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.12f, 0.24f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.0f, 0.24f, 0.0f,		0.21f, 0.43f, 0.96f, //Apertura A
		0.12f, 0.24f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.16f, 0.24f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.2f, 0.24f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.24f, 0.24f, 0.0f,		0.21f, 0.43f, 0.96f,

		-0.24f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		-0.2f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		-0.16f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f, //100
		-0.12f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		-0.08f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		-0.04f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.0f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.04f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.08f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.12f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.16f, 0.2f, 0.0f,		 0.21f, 0.43f, 0.96f,
		0.2f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.24f, 0.2f, 0.0f,		0.21f, 0.43f, 0.96f, //110

		-0.24f, 0.16f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.2f, 0.16f, 0.0f,		0.21f, 0.43f, 0.96f,
		-0.16f, 0.16f, 0.0f,	0.21f, 0.43f, 0.96f, 
		-0.12f, 0.16f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.08f, 0.16f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.04f, 0.16f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.0f, 0.16f, 0.0f, 0.21f, 0.43f, 0.96f,
		0.04f, 0.16f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.08f, 0.16f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.12f, 0.16f, 0.0f,		0.21f, 0.43f, 0.96f, //120
		0.16f, 0.16f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.2f, 0.16f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.24f, 0.16f, 0.0f,		0.21f, 0.43f, 0.96f,

		-0.24f, 0.12f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.2f, 0.12f, 0.0f,		0.21f, 0.43f, 0.96f,
		-0.16f, 0.12f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.04f, 0.12f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.0f, 0.12f, 0.0f, 0.21f, 0.43f, 0.96f,
		0.04f, 0.12f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.16f, 0.12f, 0.0f,		0.21f, 0.43f, 0.96f,//130
		0.2f, 0.12f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.24f, 0.12f, 0.0f,		0.21f, 0.43f, 0.96f,

		-0.2f, 0.08f, 0.0f,		0.21f, 0.43f, 0.96f,
		-0.16f, 0.08f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.04f, 0.08f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.0f, 0.08f, 0.0f, 0.21f, 0.43f, 0.96f,
		0.04f, 0.08f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.16f, 0.08f, 0.0f,		0.21f, 0.43f, 0.96f, 
		0.2f, 0.08f, 0.0f,		0.21f, 0.43f, 0.96f, //139

		/* --- ESCUDO DEL CAPITAN AMERICA ---
		* Parte roja */
		-0.32f, -0.04f, 0.0f,	1.0f, 0.0f, 0.0f, //140
		-0.28f, -0.04f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.24f, -0.04f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.2f, -0.04f, 0.0f,	1.0f, 0.0f, 0.0f,

		-0.36f, -0.08f, 0.0f,	1.0f, 0.0f, 0.0f, 
		-0.32f, -0.08f, 0.0f,	1.0f, 0.0f, 0.0f, 
		-0.2f, -0.08f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.16f, -0.08f, 0.0f,	1.0f, 0.0f, 0.0f,

		-0.4f, -0.12f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.36f, -0.12f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.16f, -0.12f, 0.0f,	1.0f, 0.0f, 0.0f,//150
		-0.12f, -0.12f, 0.0f,	1.0f, 0.0f, 0.0f,

		-0.4f, -0.16f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.12f, -0.16f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.4f, -0.2f, 0.0f,		1.0f, 0.0f, 0.0f,
		-0.12f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f,

		-0.4f, -0.24f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.36f, -0.24f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.16f, -0.24f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.12f, -0.24f, 0.0f,	1.0f, 0.0f, 0.0f,

		-0.36f, -0.28f, 0.0f,	1.0f, 0.0f, 0.0f, //160
		-0.32f, -0.28f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.2f, -0.28f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.16f, -0.28f, 0.0f,	1.0f, 0.0f, 0.0f,

		-0.32f, -0.32f, 0.0f,	1.0f, 0.0f, 0.0f, 
		-0.28f, -0.32f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.24f, -0.32f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.2f, -0.32f, 0.0f,	1.0f, 0.0f, 0.0f, //167

		//Parte blanca
		-0.28f, -0.08f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.24f, -0.08f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.32f, -0.12f, 0.0f,	1.0f, 1.0f, 1.0f, //170
		-0.2f, -0.12f, 0.0f,	1.0f, 1.0f, 1.0f,

		-0.36f, -0.16f, 0.0f,	1.0f, 1.0f, 1.0f, 
		-0.28f, -0.16f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.24f, -0.16f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.16f, -0.16f, 0.0f,	1.0f, 1.0f, 1.0f, //175
		-0.36f, -0.2f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.28f, -0.2f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.24f, -0.2f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.16f, -0.2f, 0.0f,	1.0f, 1.0f, 1.0f, 

		-0.32f, -0.24f, 0.0f,	1.0f, 1.0f, 1.0f, //180
		-0.2f, -0.24f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.28f, -0.28f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.24f, -0.28f, 0.0f,	1.0f, 1.0f, 1.0f,

		// Parte azul
		-0.28f, -0.12f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.24f, -0.12f, 0.0f,	0.21f, 0.43f, 0.96f,

		-0.32f, -0.16f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.2f, -0.16f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.32f, -0.2f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.2f, -0.2f, 0.0f,		0.21f, 0.43f, 0.96f,

		-0.28f, -0.24f, 0.0f,	0.21f, 0.43f, 0.96f,//190
		-0.24f, -0.24f, 0.0f,	0.21f, 0.43f, 0.96f,

		/*--- TRAJE ---*/
		// (Parte azul)
		0.16f, -0.08f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.04f, -0.12f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.04f, -0.12f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.08f, -0.12f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.12f, -0.12f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.16f, -0.12f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.2f, -0.12f, 0.0f,		0.21f, 0.43f, 0.96f,

		0.08f, -0.16f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.12f, -0.16f, 0.0f,	0.21f, 0.43f, 0.96f, //200
		0.2f, -0.16f, 0.0f,		0.21f, 0.43f, 0.96f,

		-0.04f, -0.2f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.04f, -0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.08f, -0.2f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.12f, -0.2f, 0.0f,		0.21f, 0.43f, 0.96f,

		-0.12f, -0.32f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.08f, -0.32f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.04f, -0.32f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.0f, -0.32f, 0.0f,		0.21f, 0.43f, 0.96f,
		0.04, -0.32f, 0.0f,		0.21f, 0.43f, 0.96f,//210
		0.08f, -0.32f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.12f, -0.32f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.16f, -0.32f, 0.0f,	0.21f, 0.43f, 0.96f,

		-0.12f, -0.36f, 0.0f,	0.21f, 0.43f, 0.96f,
		-0.08f, -0.36f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.08f, -0.36f, 0.0f,	0.21f, 0.43f, 0.96f,
		0.12f, -0.36f, 0.0f,	0.21f, 0.43f, 0.96f,

		// Parte blanca
		0.0f, -0.12f, 0.0f,		1.0f, 1.0f, 1.0f,
		-0.04f, -0.16f, 0.0f,	1.0f, 1.0f, 1.0f,
		0.0f, -0.16f, 0.0f,		1.0f, 1.0f, 1.0f,//220
		0.04f, -0.16f, 0.0f,	1.0f, 1.0f, 1.0f,
		0.24f, -0.16f, 0.0f,	1.0f, 1.0f, 1.0f,
		0.0f, -0.2f, 0.0f,		1.0f, 1.0f, 1.0f,
		0.2f, -0.2f, 0.0f,		1.0f, 1.0f, 1.0f,

		-0.04f, -0.24f, 0.0f,	1.0f, 1.0f, 1.0f,
		0.04f, -0.24f, 0.0f,	1.0f, 1.0f, 1.0f,
		0.12f, -0.24f, 0.0f,	1.0f, 1.0f, 1.0f,
		-0.04f, -0.28f, 0.0f,	1.0f, 1.0f, 1.0f,
		0.04f, -0.28f, 0.0f,	1.0f, 1.0f, 1.0f,
		0.12f, -0.28f, 0.0f,	1.0f, 1.0f, 1.0f,//230

		// Parte roja, guantes y botas
		-0.08f, -0.28f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.0f, -0.24f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.0f, -0.28f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.08f, -0.24f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.08f, -0.28f, 0.0f,	1.0f, 0.0f, 0.0f,

		0.24f, -0.2f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.28f, -0.2f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.24f, -0.24f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.28f, -0.24f, 0.0f,	1.0f, 0.0f, 0.0f,

		-0.16f, -0.36f, 0.0f,	1.0f, 0.0f, 0.0f,//240
		-0.16f, -0.4f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.12f, -0.4f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.2f, -0.44f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.16f, -0.44f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.12f, -0.44f, 0.0f,	1.0f, 0.0f, 0.0f,

		0.16f, -0.36f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.12f, -0.4f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.16f, -0.4f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.12f, -0.44f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.16f, -0.44f, 0.0f,	1.0f, 0.0f, 0.0f,//250
		0.2f, -0.44f, 0.0f,		1.0f, 0.0f, 0.0f,


		/*Contorno o relleno*/
		-0.08f, 0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.04f, 0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.0f, 0.48f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.04f, 0.48f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.08f, 0.48f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.16f, 0.44f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.12f, 0.44f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.12f, 0.44f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.16f, 0.44f, 0.0f,		0.0f, 0.0f, 0.0f,//260

		-0.2f, 0.4f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.2f, 0.4f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.24f, 0.36f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.24f, 0.36f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.36f, 0.32f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.32f, 0.32f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.24f, 0.32f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.24f, 0.32f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.32f, 0.32f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.36f, 0.32f, 0.0f,		0.0f, 0.0f, 0.0f,//270

		-0.36f, 0.28f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.28f, 0.28f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.28f, 0.28f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.36f, 0.28f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.36f, 0.24f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.28f, 0.24f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.28f, 0.24f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.36f, 0.24f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.36f, 0.2f, 0.0f,		0.0f, 0.0f, 0.0f,
		-0.28f, 0.2f, 0.0f,		0.0f, 0.0f, 0.0f,//280
		0.28f, 0.2f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.36f, 0.2f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.32f, 0.16f, 0.0f,	0.0f, 0.0f, 0.0f, 
		-0.28f, 0.16f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.28f, 0.16f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.32f, 0.16f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.28f, 0.12f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.28f, 0.12f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.28f, 0.08f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.24f, 0.08f, 0.0f,	0.0f, 0.0f, 0.0f,//290
		0.24f, 0.08f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.28f, 0.08f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.24f, 0.04f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.24f, 0.04f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.32f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-0.28f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-0.24f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-0.2f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.2f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.36f, -0.04f, 0.0f,	0.0f, 0.0f, 0.0f, // 300
		-0.16f, -0.04f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.16f, -0.04f, 0.0f,	0.0f, 0.0f, 0.0f,

		-0.36f, -0.08f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.12f, -0.08f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.08f, -0.08f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.04f, -0.08f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, -0.08f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.04f, -0.08f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.08f, -0.08f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.12f, -0.08f, 0.0f,	0.0f, 0.0f, 0.0f,//310
		0.2f, -0.08f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.4f, -0.12f, 0.0f,	0.0f, 0.0f, 0.0f, 
		-0.08f, -0.12f, 0.0f,	0.0f, 0.0f, 0.0f, 
		0.24f, -0.12f, 0.0f,	0.0f, 0.0f, 0.0f, 

		-0.44f, -0.16f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.08f, -0.16f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.16f, -0.16f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.28f, -0.16f, 0.0f,	0.0f, 0.0f, 0.0f,

		-0.44f, -0.2f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.08f, -0.2f, 0.0f,	0.0f, 0.0f, 0.0f,//320
		0.16f, -0.2f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.32f, -0.2f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.44f, -0.24f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.08f, -0.24f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.16f, -0.24f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.2f, -0.24f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.32f, -0.24f, 0.0f,	0.0f, 0.0f, 0.0f,

		-0.4f, -0.28f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.12f, -0.28f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.16f, -0.28f, 0.0f,	0.0f, 0.0f, 0.0f,//330
		0.24f, -0.28f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.28f, -0.28f, 0.0f,	0.0f, 0.0f, 0.0f,

		-0.36f, -0.32f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.16f, -0.32f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.2f, -0.32f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.32f, -0.36f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.28f, -0.36f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.24f, -0.36f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.2f, -0.36f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.04f, -0.36f, 0.0f,	0.0f, 0.0f, 0.0f,//440
		0.0f, -0.36f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.04f, -0.36f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.2f, -0.36f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.2f, -0.4f, 0.0f,		0.0f, 0.0f, 0.0f,
		-0.08f, -0.4f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.08f, -0.4f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.2f, -0.4f, 0.0f,		0.0f, 0.0f, 0.0f,

		-0.24f, -0.44f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.08f, -0.44f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.08f, -0.44f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.24f, -0.44f, 0.0f,	0.0f, 0.0f, 0.0f,//351

		-0.24f, -0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.2f, -0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.16f, -0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.12f, -0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.08f, -0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.08f, -0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.12f, -0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.16f, -0.48f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.2f, -0.48f, 0.0f,		0.0f, 0.0f, 0.0f,//360
		0.24f, -0.48f, 0.0f,	0.0f, 0.0f, 0.0f,

	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        glPointSize(15); // size point
        glDrawArrays(GL_POINTS,0,361);
		

        //glDrawArrays(GL_LINES,0,2);
        //glDrawArrays(GL_LINE_LOOP,0,4); // dibujar todas las lineas
        
        //glDrawArrays(GL_TRIANGLES,0,3);
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);

       
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}