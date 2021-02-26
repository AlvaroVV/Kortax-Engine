#pragma once
#include "GLProgram.h"
#include <vector>

class HelloTriangle : public GLProgram
{

public:

    std::vector<float> vertices;
    std::vector<unsigned int>indices;

private:
    unsigned int VAO, VBO, EBO;

public:
    HelloTriangle();
    ~HelloTriangle();

    void init() override;
    void draw() override;
};

