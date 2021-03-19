#pragma once
#include "GLProgram.h"
#include <vector>

/*
* Create the same 2 triangles using two different VAOs and VBOs for their data
*/
namespace HelloTriangleExcercises
{

	class Exercise_2 :public GLProgram
	{

    private:

        std::vector<float> firstTriangle;
        std::vector<float> secondTriangle;

        unsigned int VAOs[2], VBOs[2];

    public:
        Exercise_2();
        ~Exercise_2();

        void init() override;
        void draw() override;
    
	};


}

