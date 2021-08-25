#include <GL/glew.h>
#include <stdio.h>

#include "shader.h"

//Constructors

//Constructs a shader with source s and type t
Shader::Shader(const char* s, int t) {
    source = s;
    type = t;
};

//Member functions

//Compiles the shader
void Shader::compile() {

    //Compile...
    compiledShader = glCreateShader(type); 
    const char* c = source;
    glShaderSource(compiledShader, 1, &c, NULL);
    glCompileShader(compiledShader);

    //Report errors...
    GLint status;
    glGetShaderiv(compiledShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        fprintf(stderr, "Failed to compile shader of type %i\n", type);
    }

}

//Getters

//Returns the last compiled shader
GLuint Shader::getCompiledShader() {
    return compiledShader;
}
//Returns the shader's source code
const char* Shader::getSource() {
    return source;
}
//Returns the shader's type
int Shader::getType() {
    return type;
}
