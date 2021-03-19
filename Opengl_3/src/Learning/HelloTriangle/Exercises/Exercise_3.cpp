#include "Exercise_3.h"

using namespace HelloTriangleExcercises;

const char* vertexShaderSource_2 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource_2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

Exercise_3::Exercise_3()
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

Exercise_3::~Exercise_3()
{
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram_2);
}

void Exercise_3::init()
{
    shaderProgram_2 = loadShaderProgram(vertexShaderSource_2, fragmentShaderSource_2);

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


}

void Exercise_3::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mDefaultShader);

    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgram_2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glBindVertexArray(0);
}