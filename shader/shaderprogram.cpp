#include <stdio.h>

#include "shaderprogram.h"

//Constructors

ShaderProgram::ShaderProgram() {
    shaders = std::vector<Shader>();
};

//Member functions

void ShaderProgram::add(Shader s) {
    ShaderProgram::shaders.push_back(s);
};

void ShaderProgram::compile() {

    compiledShaderProgram = glCreateProgram();

    //For each shader in the shaders vector...
    for (unsigned int i = 0; i < shaders.size(); i++) {

        //Compile...
        shaders.at(i).compile();

        //And attach...
        glAttachShader(compiledShaderProgram, shaders.at(i).getCompiledShader());

    }

    //And finally, link the program.
    glLinkProgram(compiledShaderProgram);
    glUseProgram(compiledShaderProgram);

};

//Getters

GLuint ShaderProgram::getCompiledShaderProgram() {
    return compiledShaderProgram;
}