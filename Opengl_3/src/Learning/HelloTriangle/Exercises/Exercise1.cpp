#include "Exercise1.h"

using namespace HelloTriangleExcercises;

Exercise1::Exercise1()
{
    vertices = {
        0.0f, -0.5f, 0.0f,     
        -0.5f, 0.5f, 0.0f,     
        -1.0f, -0.5f, 0.0f,    
        0.0f, -0.5f, 0.0f, 
        1.0f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
    };
}

Exercise1::~Exercise1()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Exercise1::init()
{
    //Creamos el vertex buffer para almacenar el vertex data
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    //Configuramos los vertex attributes 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Habilitamos el vertexAttrib porque por defecto están desactivados. 
    //Pasamos el location como argumento.
    glEnableVertexAttribArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Exercise1::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    useDefaultProgram();

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
