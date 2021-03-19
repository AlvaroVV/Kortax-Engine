#include "GLProgram.h"
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

GLProgram::GLProgram()
{
    std::cout << "GLProgram: Constructor" << std::endl;
    mDefaultShader = loadDefaultShaderProgram();
}


GLProgram::~GLProgram()
{
	std::cout << "GLProgram: Destructor" << std::endl;
    if(mDefaultShader > 0)
        glDeleteProgram(mDefaultShader);
}

void GLProgram::init()
{
    std::cout << "GLProgram: Init" << std::endl;
    loadDefaultShaderProgram();
}

void GLProgram::draw()
{
    std::cout << "GLProgram: Draw" << std::endl;
}

unsigned int GLProgram::loadDefaultShaderProgram()
{
    return loadShaderProgram(vertexShaderSource, fragmentShaderSource);
}

unsigned int GLProgram::loadShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode)
{
    unsigned int shaderProgram;
    //Creamos el vertex shader y compilamos
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    //Nos aseguramos de que no contiene errores de compilacion
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    //Shader program
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //Comprobamos la compilacion
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}