#pragma once
#include "GLProgram.h"
#include <vector>


/*
* Create two shader programs where the second program uses a different fragment shader that outputs the color yellow; draw both triangles again where one outputs the color yellow
*/
namespace HelloTriangleExcercises
{
    class Exercise_3 :
        public GLProgram
    {
    private:

        std::vector<float> firstTriangle;
        std::vector<float> secondTriangle;

        unsigned int VAOs[2], VBOs[2];

        unsigned int shaderProgram_2;

    public:

        Exercise_3();
        ~Exercise_3();

        void init() override;
        void draw() override;
    };

}

