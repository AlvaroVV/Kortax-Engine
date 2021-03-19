#include "Exercise_2.h"

using namespace HelloTriangleExcercises;

Exercise_2::Exercise_2()
{
    firstTriangle = {
       0.0f, -0.5f, 0.0f,
       -0.5f, 0.5f, 0.0f,
       -1.0f, -0.5f, 0.0f
    };

    secondTriangle = {
       0.0f, -0.5f, 0.0f,
       1.0f, -0.5f, 0.0f,
       0.5f, 0.5f, 0.0f
    };
}

Exercise_2::~Exercise_2() 
{
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    //glDeleteProgram(shaderProgram);
}

void Exercise_2::init()
{
    GLProgram::init();
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * firstTriangle.size(), firstTriangle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * secondTriangle.size(), secondTriangle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.5f, 0.1f, 0.6f, 1.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


}

void Exercise_2::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mDefaultShader);

    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glBindVertexArray(0);
}
