#pragma once

class Shader {
    public: 

        //Constructors

        //Constructs a shader with source s and type t
        Shader(const char* s, int t);

        //Member functions

        //Compiles the shader
        void compile();

        //Getters

        //Returns the last compiled shader
        GLuint getCompiledShader();
        //Returns the shader's source code
        const char* getSource();
        //Returns the shader's type
        int getType();

    private:

        //Shader's source code
        const char* source;
        //Shader's type
        int type;
        //Compiled shader
        GLuint compiledShader;

};