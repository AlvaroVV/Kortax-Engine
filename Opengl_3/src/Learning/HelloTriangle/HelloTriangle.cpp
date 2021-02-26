#include "HelloTriangle.h"

HelloTriangle::HelloTriangle()
{
 
    vertices = {
        0.5f, 0.5f, 0.0f,     //top-right
        0.5f, -0.5f, 0.0f,     //bottom-right
        -0.5f, -0.5f, 0.0f,    //bottom-left
        -0.5f,  0.5f, 0.0f     //top-left
    };

    indices = {
        0, 1, 3,
        1, 2, 3
    };
}

HelloTriangle::~HelloTriangle()
{
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void HelloTriangle::init()
{

    //Creamos el vertex buffer para almacenar el vertex data
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    //Configuramos los vertex attributes 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Habilitamos el vertexAttrib porque por defecto están desactivados. 
    //Pasamos el location como argumento.
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void HelloTriangle::draw()
{
    useDefaultProgram();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Unbind current VAO
    glBindVertexArray(0);
}

