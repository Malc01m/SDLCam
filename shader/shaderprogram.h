#pragma once

#include <vector>

#include <GL/glew.h>

#include "shader.h"

class ShaderProgram {

    public:

        //Constructors

        //Constructs a shader program object
        ShaderProgram();

        //Member functions

        //Adds a shader to the shaders vector
        void add(Shader s);
        //Compiles the shaders in the shaders vector as a shader program
        void compile();

        //Getters

        //Returns the last compiled shader program
        GLuint getCompiledShaderProgram();

    private:

        //The last compiled shader program
        GLuint compiledShaderProgram;
        //Objects of shaders to be included in the program
        std::vector<Shader> shaders;

};