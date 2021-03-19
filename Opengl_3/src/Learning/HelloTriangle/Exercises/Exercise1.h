#pragma once
#include "GLProgram.h"
#include <vector>


// ----------------
//Draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data
//----------------

namespace HelloTriangleExcercises
{
    class Exercise1 :public GLProgram
    {
        std::vector<float> vertices;
    
    private:
        unsigned int VAO, VBO;

    public:
        Exercise1();
        virtual ~Exercise1();

        void init() override;
        void draw() override;
    };
}


