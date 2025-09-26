// Practica 6
// Mendoza Rodriguez Angel Jesus
// Fecha de entrega: 26 de septiembre de 2025
// 319087288

// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;



int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Practica 6 Angel Mendoza Carga de modelos y camara sintetica", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    // Load models
    Model perro((char*)"Models/RedDog.obj"); // Cargar ruta del objeto (modelo)
    
    Model palmera((char*)"Models/Palmera/palmera.obj"); 
    Model arbol((char*)"Models/Arbol/arbol.obj");
    Model stego((char*)"Models/Stego/untitled.obj");
    Model creneo((char*)"Models/Craneo/craneo.obj");
    Model triceratop((char*)"Models/Triceratops/tripo_convert_81894be5-aabb-4d05-a9dc-458670a36a8b.obj"); 

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );



    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        // Draw perro
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        perro.Draw(shader);

        // Draw palmera 
        glm::mat4 modelPalmera = glm::mat4(1.0f); // matriz para la palmera
        modelPalmera = glm::translate(modelPalmera, glm::vec3(0.0f, 0.0f, -5.0f)); // detras del perrito
        modelPalmera = glm::rotate(modelPalmera, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar 90° en Y
        modelPalmera = glm::scale(modelPalmera, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPalmera));
        palmera.Draw(shader);

        // Draw arbol - Transformaciones independientes
        glm::mat4 modelArbol = glm::mat4(1.0f);
        modelArbol = glm::translate(modelArbol, glm::vec3(-2.0f, 0.0f, -1.0f)); // A la izquierda y atras del perro 
        modelArbol = glm::scale(modelArbol, glm::vec3(0.05f, 0.05f, 0.05f)); // escalando para obtener mejor vista
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelArbol));
        arbol.Draw(shader);

        // Draw stegosaurio
        glm::mat4 modelStego = glm::mat4(1.0f); 
        modelStego = glm::translate(modelStego, glm::vec3(-1.0f, -0.2f, 0.5f)); 
        modelStego = glm::rotate(modelStego, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar 270° en Y
        modelStego = glm::scale(modelStego, glm::vec3(0.003f, 0.003f, 0.003f)); // Escalando 
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelStego));
        stego.Draw(shader);

        // Draw craneo-dinosaurio
        glm::mat4 modelCreneo = glm::mat4(1.0f); 
        modelCreneo = glm::translate(modelCreneo, glm::vec3(-0.5f, -0.2f, 0.1f)); // colocar a un lado del perro
        modelCreneo = glm::scale(modelCreneo, glm::vec3(0.15f, 0.15f, 0.15f)); // Escalar 
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCreneo));
        creneo.Draw(shader);

        // Draw triceratop 
        glm::mat4 modelTriceratop = glm::mat4(1.0f); 
        modelTriceratop = glm::translate(modelTriceratop, glm::vec3(0.8f, -0.1f, 0.5f)); // del lado derecho del perrito
        modelTriceratop = glm::rotate(modelTriceratop, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar 180° en Y
        modelTriceratop = glm::scale(modelTriceratop, glm::vec3(0.9f, 0.9f, 0.9f)); // Escalar
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelTriceratop));
        triceratop.Draw(shader);

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

