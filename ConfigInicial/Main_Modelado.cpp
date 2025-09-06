// Practica 4
// Mendoza Rodriguez Angel Jesus
// Fecha de entrega: 5 de septiembre de 2025
// 319087288

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-15.0f;
float rot = 0.0f;

int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4 Angel Mendoza Modelado geometrico", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 0.9f, 0.7f, 0.5f,//Front cabeza Steve color piel
		0.5f, -0.5f, 0.5f,  0.9f, 0.7f, 0.5f,
		0.5f,  0.5f, 0.5f,  0.9f, 0.7f, 0.5f,
		0.5f,  0.5f, 0.5f,  0.9f, 0.7f, 0.5f,
		-0.5f,  0.5f, 0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f, 0.5f, 0.9f, 0.7f, 0.5f,
		
	    -0.5f, -0.5f,-0.5f, 0.4f, 0.3f, 0.2f,//Back cabello color marron
		 0.5f, -0.5f,-0.5f, 0.4f, 0.3f, 0.2f,
		 0.5f,  0.5f,-0.5f, 0.4f, 0.3f, 0.2f,
		 0.5f,  0.5f,-0.5f, 0.4f, 0.3f, 0.2f,
	    -0.5f,  0.5f,-0.5f, 0.4f, 0.3f, 0.2f,
	    -0.5f, -0.5f,-0.5f, 0.4f, 0.3f, 0.2f,
		
		// cara derecha
		 0.5f, -0.5f,  0.5f, 0.4f, 0.3f, 0.2f,
		 0.5f, -0.5f, -0.5f, 0.4f, 0.3f, 0.2f,
		 0.5f,  0.5f, -0.5f, 0.4f, 0.3f, 0.2f,
		 0.5f,  0.5f, -0.5f, 0.4f, 0.3f, 0.2f,
		 0.5f,  0.5f,  0.5f, 0.4f, 0.3f, 0.2f,
		 0.5f,  -0.5f, 0.5f, 0.4f, 0.3f, 0.2f,
		
		 // cara izquierda
		-0.5f,  0.5f,  0.5f,  0.4f, 0.3f, 0.2f,
		-0.5f,  0.5f, -0.5f,  0.4f, 0.3f, 0.2f,
		-0.5f, -0.5f, -0.5f,  0.4f, 0.3f, 0.2f,
		-0.5f, -0.5f, -0.5f,  0.4f, 0.3f, 0.2f,
		-0.5f, -0.5f,  0.5f,  0.4f, 0.3f, 0.2f,
		-0.5f,  0.5f,  0.5f,  0.4f, 0.3f, 0.2f,
		
		// cara inferior
		-0.5f, -0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		0.5f, -0.5f, -0.5f,  0.9f, 0.7f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.9f, 0.7f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f,  0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		
		// cabello cara superior 
		-0.5f,  0.5f, -0.5f, 0.4f, 0.3f, 0.2f,
		0.5f,  0.5f, -0.5f,  0.4f, 0.3f, 0.2f,
		0.5f,  0.5f,  0.5f,  0.4f, 0.3f, 0.2f,
		0.5f,  0.5f,  0.5f,  0.4f, 0.3f, 0.2f,
		-0.5f,  0.5f,  0.5f, 0.4f, 0.3f, 0.2f,
		-0.5f,  0.5f, -0.5f, 0.4f, 0.3f, 0.2f,
	};

	// Vertices para el torso (camisa)
	float camisaVertices[] = {
		-0.5f, -0.5f, 0.5f, 0.055f, 0.682f, 0.682f, // Azul celeste
		0.5f, -0.5f, 0.5f,  0.055f, 0.682f, 0.682f,
		0.5f,  0.5f, 0.5f,  0.055f, 0.682f, 0.682f,
		0.5f,  0.5f, 0.5f,  0.055f, 0.682f, 0.682f,
		-0.5f,  0.5f, 0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f, -0.5f, 0.5f, 0.055f, 0.682f, 0.682f,

		-0.5f, -0.5f,-0.5f, 0.055f, 0.682f, 0.682f,
		 0.5f, -0.5f,-0.5f, 0.055f, 0.682f, 0.682f,
		 0.5f,  0.5f,-0.5f, 0.055f, 0.682f, 0.682f,
		 0.5f,  0.5f,-0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f,  0.5f,-0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f, -0.5f,-0.5f, 0.055f, 0.682f, 0.682f,

		 0.5f, -0.5f,  0.5f, 0.055f, 0.682f, 0.682f,
		 0.5f, -0.5f, -0.5f, 0.055f, 0.682f, 0.682f,
		 0.5f,  0.5f, -0.5f, 0.055f, 0.682f, 0.682f,
		 0.5f,  0.5f, -0.5f, 0.055f, 0.682f, 0.682f,
		 0.5f,  0.5f,  0.5f, 00.055f, 0.682f, 0.682f,
		 0.5f,  -0.5f, 0.5f, 0.055f, 0.682f, 0.682f,

		-0.5f,  0.5f,  0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f,  0.5f, -0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f, -0.5f, -0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f, -0.5f, -0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f, -0.5f,  0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f,  0.5f,  0.5f, 0.055f, 0.682f, 0.682f,

		-0.5f, -0.5f, -0.5f, 0.055f, 0.682f, 0.682f,
		0.5f, -0.5f, -0.5f,  0.055f, 0.682f, 0.682f,
		0.5f, -0.5f,  0.5f,  0.055f, 0.682f, 0.682f,
		0.5f, -0.5f,  0.5f,  0.055f, 0.682f, 0.682f,
		-0.5f, -0.5f,  0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f, -0.5f, -0.5f, 0.055f, 0.682f, 0.682f,

		-0.5f,  0.5f, -0.5f, 0.055f, 0.682f, 0.682f,
		0.5f,  0.5f, -0.5f,  0.055f, 0.682f, 0.682f,
		0.5f,  0.5f,  0.5f,  0.055f, 0.682f, 0.682f,
		0.5f,  0.5f,  0.5f,  0.055f, 0.682f, 0.682f,
		-0.5f,  0.5f,  0.5f, 0.055f, 0.682f, 0.682f,
		-0.5f,  0.5f, -0.5f, 0.055f, 0.682f, 0.682f,
	};

	// Vertices para los brazos
	float brazosVertices[] = {
		-0.5f, -0.5f, 0.5f, 0.9f, 0.7f, 0.5f, // Color piel
		0.5f, -0.5f, 0.5f,  0.9f, 0.7f, 0.5f,
		0.5f,  0.5f, 0.5f,  0.9f, 0.7f, 0.5f,
		0.5f,  0.5f, 0.5f,  0.9f, 0.7f, 0.5f,
		-0.5f,  0.5f, 0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f, 0.5f, 0.9f, 0.7f, 0.5f,

		-0.5f, -0.5f,-0.5f, 0.9f, 0.7f, 0.5f,
		 0.5f, -0.5f,-0.5f, 0.9f, 0.7f, 0.5f,
		 0.5f,  0.5f,-0.5f, 0.9f, 0.7f, 0.5f,
		 0.5f,  0.5f,-0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f,  0.5f,-0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f,-0.5f, 0.9f, 0.7f, 0.5f,

		 0.5f, -0.5f,  0.5f, 0.9f, 0.7f, 0.5f,
		 0.5f, -0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		 0.5f,  0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		 0.5f,  0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		 0.5f,  0.5f,  0.5f, 0.9f, 0.7f, 0.5f,
		 0.5f,  -0.5f, 0.5f, 0.9f, 0.7f, 0.5f,

		-0.5f,  0.5f,  0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f,  0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f,  0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f,  0.5f,  0.5f, 0.9f, 0.7f, 0.5f,

		-0.5f, -0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		0.5f, -0.5f, -0.5f,  0.9f, 0.7f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.9f, 0.7f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f,  0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f, -0.5f, -0.5f, 0.9f, 0.7f, 0.5f,

		-0.5f,  0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
		0.5f,  0.5f, -0.5f,  0.9f, 0.7f, 0.5f,
		0.5f,  0.5f,  0.5f,  0.9f, 0.7f, 0.5f,
		0.5f,  0.5f,  0.5f,  0.9f, 0.7f, 0.5f,
		-0.5f,  0.5f,  0.5f, 0.9f, 0.7f, 0.5f,
		-0.5f,  0.5f, -0.5f, 0.9f, 0.7f, 0.5f,
	};

	// Vertices para pantalones (azul oscuro)
	float pantalonVertices[] = {
		-0.5f, -0.5f, 0.5f, 0.286f, 0.275f, 0.592f, // Azul pantalon
		0.5f, -0.5f, 0.5f,  0.286f, 0.275f, 0.592f,
		0.5f,  0.5f, 0.5f,  0.286f, 0.275f, 0.592f,
		0.5f,  0.5f, 0.5f,  0.286f, 0.275f, 0.592f,
		-0.5f,  0.5f, 0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f, -0.5f, 0.5f, 0.286f, 0.275f, 0.592f,

		-0.5f, -0.5f,-0.5f, 0.286f, 0.275f, 0.592f,
		 0.5f, -0.5f,-0.5f, 0.286f, 0.275f, 0.592f,
		 0.5f,  0.5f,-0.5f, 0.286f, 0.275f, 0.592f,
		 0.5f,  0.5f,-0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f,  0.5f,-0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f, -0.5f,-0.5f, 0.286f, 0.275f, 0.592f,

		 0.5f, -0.5f,  0.5f, 0.286f, 0.275f, 0.592f,
		 0.5f, -0.5f, -0.5f, 0.286f, 0.275f, 0.592f,
		 0.5f,  0.5f, -0.5f, 0.286f, 0.275f, 0.592f,
		 0.5f,  0.5f, -0.5f, 0.286f, 0.275f, 0.592f,
		 0.5f,  0.5f,  0.5f, 0.286f, 0.275f, 0.592f,
		 0.5f,  -0.5f, 0.5f, 0.286f, 0.275f, 0.592f,

		-0.5f,  0.5f,  0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f,  0.5f, -0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f, -0.5f, -0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f, -0.5f, -0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f, -0.5f,  0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f,  0.5f,  0.5f, 0.286f, 0.275f, 0.592f,

		-0.5f, -0.5f, -0.5f, 0.286f, 0.275f, 0.592f,
		0.5f, -0.5f, -0.5f,  0.286f, 0.275f, 0.592f,
		0.5f, -0.5f,  0.5f,  0.286f, 0.275f, 0.592f,
		0.5f, -0.5f,  0.5f,  0.286f, 0.275f, 0.592f,
		-0.5f, -0.5f,  0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f, -0.5f, -0.5f, 0.286f, 0.275f, 0.592f,

		-0.5f,  0.5f, -0.5f, 0.286f, 0.275f, 0.592f,
		0.5f,  0.5f, -0.5f,  0.286f, 0.275f, 0.592f,
		0.5f,  0.5f,  0.5f,  0.286f, 0.275f, 0.592f,
		0.5f,  0.5f,  0.5f,  0.286f, 0.275f, 0.592f,
		-0.5f,  0.5f,  0.5f, 0.286f, 0.275f, 0.592f,
		-0.5f,  0.5f, -0.5f, 0.286f, 0.275f, 0.592f,
	};

	// Vertices para los zapatos
	float zapatoVertices[] = {
		-0.5f, -0.5f, 0.5f, 0.45f, 0.45f, 0.47f, // Gris
		0.5f, -0.5f, 0.5f,  0.45f, 0.45f, 0.47f,
		0.5f,  0.5f, 0.5f,  0.45f, 0.45f, 0.47f,
		0.5f,  0.5f, 0.5f,  0.45f, 0.45f, 0.47f,
		-0.5f,  0.5f, 0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f, -0.5f, 0.5f, 0.45f, 0.45f, 0.47f,

		-0.5f, -0.5f,-0.5f, 0.45f, 0.45f, 0.47f,
		 0.5f, -0.5f,-0.5f, 0.45f, 0.45f, 0.47f,
		 0.5f,  0.5f,-0.5f, 0.45f, 0.45f, 0.47f,
		 0.5f,  0.5f,-0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f,  0.5f,-0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f, -0.5f,-0.5f, 0.45f, 0.45f, 0.47f,

		 0.5f, -0.5f,  0.5f, 0.45f, 0.45f, 0.47f,
		 0.5f, -0.5f, -0.5f, 0.45f, 0.45f, 0.47f,
		 0.5f,  0.5f, -0.5f, 0.45f, 0.45f, 0.47f,
		 0.5f,  0.5f, -0.5f, 0.45f, 0.45f, 0.47f,
		 0.5f,  0.5f,  0.5f, 0.45f, 0.45f, 0.47f,
		 0.5f,  -0.5f, 0.5f, 0.45f, 0.45f, 0.47f,

		-0.5f,  0.5f,  0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f,  0.5f, -0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f, -0.5f, -0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f, -0.5f, -0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f, -0.5f,  0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f,  0.5f,  0.5f, 0.45f, 0.45f, 0.47f,

		-0.5f, -0.5f, -0.5f, 0.45f, 0.45f, 0.47f,
		0.5f, -0.5f, -0.5f,  0.45f, 0.45f, 0.47f,
		0.5f, -0.5f,  0.5f,  0.45f, 0.45f, 0.47f,
		0.5f, -0.5f,  0.5f,  0.45f, 0.45f, 0.47f,
		-0.5f, -0.5f,  0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f, -0.5f, -0.5f, 0.45f, 0.45f, 0.47f,

		-0.5f,  0.5f, -0.5f, 0.45f, 0.45f, 0.47f,
		0.5f,  0.5f, -0.5f,  0.45f, 0.45f, 0.47f,
		0.5f,  0.5f,  0.5f,  0.45f, 0.45f, 0.47f,
		0.5f,  0.5f,  0.5f,  0.45f, 0.45f, 0.47f,
		-0.5f,  0.5f,  0.5f, 0.45f, 0.45f, 0.47f,
		-0.5f,  0.5f, -0.5f, 0.45f, 0.45f, 0.47f,
	};

	// Vertices para los ojos
	float ojoVertices[] = {
		-0.1f, -0.1f, 0.1f, 1.0f, 1.0f, 1.0f, // blanco
		0.1f, -0.1f, 0.1f,  1.0f, 1.0f, 1.0f,
		0.1f,  0.1f, 0.1f,  1.0f, 1.0f, 1.0f,
		0.1f,  0.1f, 0.1f,  1.0f, 1.0f, 1.0f,
		-0.1f,  0.1f, 0.1f, 1.0f, 1.0f, 1.0f,
		-0.1f, -0.1f, 0.1f, 1.0f, 1.0f, 1.0f,
	};

	float cabelloVertices[] = {
		-0.1f, -0.1f, 0.1f, 0.4f, 0.3f, 0.2f, //cafe
		0.1f, -0.1f, 0.1f,  0.4f, 0.3f, 0.2f,
		0.1f,  0.1f, 0.1f,  0.4f, 0.3f, 0.2f,
		0.1f,  0.1f, 0.1f,  0.4f, 0.3f, 0.2f,
		-0.1f,  0.1f, 0.1f, 0.4f, 0.3f, 0.2f,
		-0.1f, -0.1f, 0.1f, 0.4f, 0.3f, 0.2f,
	};

	float bocaVertices[] = {
		-0.1f, -0.1f, 0.1f, 0.451f, 0.235f, 0.208f, //cafe boca
		0.1f, -0.1f, 0.1f,  0.451f, 0.235f, 0.208f,
		0.1f,  0.1f, 0.1f,  0.451f, 0.235f, 0.208f,
		0.1f,  0.1f, 0.1f,  0.451f, 0.235f, 0.208f,
		-0.1f,  0.1f, 0.1f, 0.451f, 0.235f, 0.208f,
		-0.1f, -0.1f, 0.1f, 0.451f, 0.235f, 0.208f,
	};

	float cuelloVertices[] = {
		-0.1f, -0.1f, 0.1f, 0.9f, 0.7f, 0.5f, //cafe boca
		0.1f, -0.1f, 0.1f,  0.9f, 0.7f, 0.5f,
		0.1f,  0.1f, 0.1f,  0.9f, 0.7f, 0.5f,
		0.1f,  0.1f, 0.1f,  0.9f, 0.7f, 0.5f,
		-0.1f,  0.1f, 0.1f, 0.9f, 0.7f, 0.5f,
		-0.1f, -0.1f, 0.1f, 0.9f, 0.7f, 0.5f,
	};

	GLuint VBO_cabeza, VAO_cabeza;
	glGenVertexArrays(1, &VAO_cabeza);
	glGenBuffers(1, &VBO_cabeza);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO_cabeza);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cabeza);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	// buffers para torso/camisa
	GLuint VBO_camisa, VAO_camisa;
	glGenVertexArrays(1, &VAO_camisa);
	glGenBuffers(1, &VBO_camisa);
	glBindVertexArray(VAO_camisa);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_camisa);
	glBufferData(GL_ARRAY_BUFFER, sizeof(camisaVertices), camisaVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	// buffers para extremidades
	GLuint VBO_brazo, VAO_brazo;
	glGenVertexArrays(1, &VAO_brazo);
	glGenBuffers(1, &VBO_brazo);
	glBindVertexArray(VAO_brazo);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_brazo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(brazosVertices), brazosVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// buffers para pantalon
	GLuint VBO_pantalon, VAO_pantalon;
	glGenVertexArrays(1, &VAO_pantalon);
	glGenBuffers(1, &VBO_pantalon);
	glBindVertexArray(VAO_pantalon);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pantalon);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pantalonVertices), pantalonVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// buffers para zapatos
	GLuint VBO_zapato, VAO_zapato;
	glGenVertexArrays(1, &VAO_zapato);
	glGenBuffers(1, &VBO_zapato);
	glBindVertexArray(VAO_zapato);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_zapato);
	glBufferData(GL_ARRAY_BUFFER, sizeof(zapatoVertices), zapatoVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// buffers para ojos
	GLuint VBO_ojo, VAO_ojo;
	glGenVertexArrays(1, &VAO_ojo);
	glGenBuffers(1, &VBO_ojo);
	glBindVertexArray(VAO_ojo);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ojo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ojoVertices), ojoVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// buffers para cabello
	GLuint VBO_cabello, VAO_cabello;
	glGenVertexArrays(1, &VAO_cabello);
	glGenBuffers(1, &VBO_cabello);
	glBindVertexArray(VAO_cabello);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cabello);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cabelloVertices), cabelloVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// buffers para boca
	GLuint VBO_boca, VAO_boca;
	glGenVertexArrays(1, &VAO_boca);
	glGenBuffers(1, &VBO_boca);
	glBindVertexArray(VAO_boca);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_boca);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bocaVertices), bocaVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// buffers para cuello
	GLuint VBO_cuello, VAO_cuello;
	glGenVertexArrays(1, &VAO_cuello);
	glGenBuffers(1, &VBO_cuello);
	glBindVertexArray(VAO_cuello);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cuello);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cuelloVertices), cuelloVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO_cabeza);
	
		// Cabeza de Steve 
	    model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f)); // ancho, grosor y profundidad del rostro
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Torso/playera de Steve
		glBindVertexArray(VAO_camisa);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // origen
		model = glm::scale(model, glm::vec3(2.0f, 3.0f, 1.0f)); // ancho, alto, profundidad del torso
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// hombro derecho
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // ancho, alto, profundidad del torso
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// hombro izquierdo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // ancho, alto, profundidad del torso
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// brazo derecho
		glBindVertexArray(VAO_brazo);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, -0.3f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 2.4f, 1.0f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// brazo izquierdo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, -0.3f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 2.4f, 1.0f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// pierna derecha
		glBindVertexArray(VAO_pantalon);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, -3.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.0f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// pierna izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, -3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.0f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ojo derecho azul
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.3f, 2.3f, 1.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.05f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// ojo izquierdo azul
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, 2.3f, 1.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.05f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// zapato derecho
		glBindVertexArray(VAO_zapato);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, -4.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.85f, 1.0f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// zapato izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, -4.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.85f, 1.0f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ojo derecho
		glBindVertexArray(VAO_ojo);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, 2.3f, 1.0f)); // mas adelante
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.05f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// ojo izquierdo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 2.3f, 1.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.05f)); // ancho, alto, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// cabello 
		glBindVertexArray(VAO_cabello);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 3.2f, 1.0));
		model = glm::scale(model, glm::vec3(10.2f, 3.2f, 0.02f)); // ancho, alto y profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// mecha derecha
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.92f, 2.8f, 1.0));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.05f)); // ancho, alto y profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// mechas izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.92f, 2.8f, 1.0));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.05f)); // ancho, alto y profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// boca
		glBindVertexArray(VAO_boca);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, 1.0));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 0.02f)); // ancho, alto y profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.8f, 1.0));
		model = glm::scale(model, glm::vec3(4.0f, 1.0f, 0.02f)); // ancho, alto y profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// Cuello
		glBindVertexArray(VAO_cuello);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.4f, 0.5));
		model = glm::scale(model, glm::vec3(4.0f, 1.0f, 0.02f)); // ancho, alto y profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, 0.5));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 0.02f)); // ancho, alto y profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO_cabeza);
	glDeleteBuffers(1, &VBO_cabeza);
	glDeleteVertexArrays(1, &VAO_camisa);
	glDeleteBuffers(1, &VBO_camisa);
	glDeleteVertexArrays(1, &VAO_brazo);
	glDeleteBuffers(1, &VBO_brazo);
	glDeleteVertexArrays(1, &VAO_pantalon);
	glDeleteBuffers(1, &VBO_pantalon);
	glDeleteVertexArrays(1, &VAO_zapato);
	glDeleteBuffers(1, &VBO_zapato);
	glDeleteVertexArrays(1, &VAO_ojo);
	glDeleteBuffers(1, &VBO_ojo);
	glDeleteVertexArrays(1, &VAO_cabello);
	glDeleteBuffers(1, &VBO_cabello);
	glDeleteVertexArrays(1, &VAO_boca);
	glDeleteBuffers(1, &VBO_boca);
	glDeleteVertexArrays(1, &VAO_cuello);
	glDeleteBuffers(1, &VBO_cuello);

	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.4f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.4f;
 }


