#include <GLAD\glad.h>
#include <GLFW\glfw3.h>
#include "Learning\HelloTriangle\HelloTriangle.h"
#include "Learning\HelloTriangle\Exercises\Exercise1.h"
#include "Learning\HelloTriangle\Exercises\Exercise_2.h"
#include "Learning\HelloTriangle\Exercises\Exercise_3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


GLProgram *program;


int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Creamos el objeto ventana y lo asociamos como main context del main thread
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Registramos la funcion
    //Podemos registrar varios callbacks, siempre entre la creacion y el gameloop
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Inicializamos GLAD
    //Glad se encarga de proveer punteros a funciones de opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Podemos utilizar unas dimensiones menores que glfw. Opengl tomará en cuenta las dimensiones de glviewport
    glViewport(0, 0, 800, 600);

    program = new HelloTriangleExcercises::Exercise_2();

    program->init();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
       
        program->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    delete program;
    //Eliminamos y borramos los recursos creados de GLFW
    glfwTerminate();

    return 0;
}

/*
* Callback function para cambiar el tamaño de la ventana.
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}