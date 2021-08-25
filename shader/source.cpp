namespace shadersrc {

    const char vertsrc[] = R"glsl(

                        #version 150 core                                       
                                                                                
                        in vec2 position;                                       
                                                                                
                        void main() {                                           
                            gl_Position = vec4(position, 0.0, 1.0);             
                        }                                                       
                                                                                
                        )glsl";

    const char fragsrc[] = R"glsl(

                        #version 150 core

                        uniform vec3 triangleColor;
                        uniform float transparency;

                        out vec4 outColor;

                        void main() {
                            outColor = vec4(triangleColor, transparency);
                        }

                        )glsl";
                        
}