#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL_opengl.h>

#include <memory>
#include <math.h>

#include "quits.cpp"
#include "draws.cpp"
#include "shader/source.cpp"

#include "shader/shaderprogram.h"
#include "poly/poly.h"

int main (int argc, char* argv[]) {

    //Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Failed to start SDL, error #: %s\n", SDL_GetError());
        quit(1);
    }

    //Configure OpenGl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Get window dimensions
    SDL_DisplayMode dispmode;
    SDL_GetCurrentDisplayMode(0, &dispmode);
    int width, height;
    width = dispmode.w;
    height = dispmode.h;
    float whratio = (width / static_cast<float>(height));

    //Create window
    SDL_Window *window = SDL_CreateWindow("Traveller", 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        fprintf(stderr, "Failed to start the window, error: %s\n", SDL_GetError());
        quit(1, window);
    }

    //Create OpenGl context
    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    if (ctx == NULL) {
        fprintf(stderr, "Failed to start the OpenGl context, error: %s\n", SDL_GetError());
        quit(1, window, ctx);
    }

    //Start GLEW
    GLenum glewstatus = glewInit();
    if (glewstatus != GLEW_OK) {
        fprintf(stderr, "Failed to start GLEW, error: %s\n", glewGetErrorString(glewstatus));
        quit(1, window, ctx);
    }

    if (SDL_GL_SetSwapInterval(-1) != 0) {
        if (SDL_GL_SetSwapInterval(1) != 0) {
            fprintf(stderr, "Couldn't set the swap interval, screen tearing may occur.\n");
            SDL_ClearError();
        }
    }

    //Shaders
    ShaderProgram sp;
    sp.add(Shader(shadersrc::vertsrc, GL_VERTEX_SHADER));
    sp.add(Shader(shadersrc::fragsrc, GL_FRAGMENT_SHADER));
    sp.compile();

    //Transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    //Buffers, arrays, uniforms, and attributes
    GLuint vbo;
    GLuint vao;
    GLint color;
    GLint transparency;
    GLint pos;
    GLint shaderProgram = sp.getCompiledShaderProgram();

    color = glGetUniformLocation(shaderProgram, "triangleColor");
    transparency = glGetUniformLocation(shaderProgram, "transparency");
    pos = glGetAttribLocation(shaderProgram, "position");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //Clear
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Create test box
    std::vector<std::array<float, 3>> boxSideOneVs = {{0.2, 0.2, 0.2}, {0.2, -0.2, 0.2}, {-0.2, 0.2, 0.2}, {-0.2, -0.2, 0.2}};
    std::vector<std::array<float, 3>> boxSideTwoVs = {{0.2, 0.2, 0.2}, {0.2, 0.2, -0.2}, {-0.2, 0.2, 0.2}, {-0.2, 0.2, -0.2}};
    std::vector<std::array<float, 3>> boxSideThreeVs = {{0.2, 0.2, 0.2}, {0.2, -0.2, 0.2}, {0.2, 0.2, -0.2}, {0.2, -0.2, -0.2}};
    std::vector<std::array<float, 3>> groundVs = {{1, -0.2, 1}, {-1, -0.2, 1}, {1, -0.2, -1}, {-1, -0.2, -1}};
    std::vector<std::array<float, 3>> cursorVs = {{0.0, 0.01, 0.0}, {0.01, 0.0, 0.0}, {-0.01, 0.0, 0.0}, {0.0, -0.01, 0.0}, {0.0, 0.01, 0.0}, {-0.01, 0.0, 0.0}, {0.01, 0.0, 0.0}, {0.0, -0.01, 0.0}, {-0.01, 0.0, 0.0}};
    
    float col1[] = {1.0, 1.0, 0.6, 0.6};
    float col2[] = {1.0, 0.6, 1.0, 0.6};
    float col3[] = {0.6, 1.0, 1.0, 0.6};
    float groundCol[] = {1.0, 1.0, 1.0, 1.0};
    float cursorCol[] = {1.0, 1.0, 0.8, 0.2};

    Poly boxSideOnePoly(boxSideOneVs, col1);
    Poly boxSideTwoPoly(boxSideTwoVs, col2);
    Poly boxSideThreePoly(boxSideThreeVs, col3);
    Poly groundPoly(groundVs, groundCol);
    Poly cursorPoly(cursorVs, cursorCol);

    std::vector<std::shared_ptr<Poly>> polyptrs;
    std::shared_ptr<Poly> boxSideOne = std::make_shared<Poly>(boxSideOnePoly);
    std::shared_ptr<Poly> boxSideTwo = std::make_shared<Poly>(boxSideTwoPoly);
    std::shared_ptr<Poly> boxSideThree = std::make_shared<Poly>(boxSideThreePoly);
    std::shared_ptr<Poly> ground = std::make_shared<Poly>(groundPoly);
    std::shared_ptr<Poly> cursor = std::make_shared<Poly>(cursorPoly);

    cursor->setFixed(true);

    polyptrs.push_back(ground);
    polyptrs.push_back(boxSideOne);
    polyptrs.push_back(boxSideTwo);
    polyptrs.push_back(boxSideThree);
    polyptrs.push_back(cursor);

    //Camera position values
    float camx = 1.0;
    float camy = 0.0;
    float camz = 0.0;
    float shiftBy = 0.02; //Portion of the screen moved per keypress
    //Camera rotation values
    float camRotDir = 0.0;
    float camRotAlt = 0.0;
    float camrz = 0.0;
    float rotBy = 0.005; //Portion of the circle rotated per keypress

    //Event variables
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    SDL_Event event;

    //Initial draw
    clear();
    draw(whratio, polyptrs, color, transparency, camx, camy, camz, camRotDir, camRotAlt, camrz, window);

    bool jump = false;
    float jumpinity = 0;
    int jumpinitveloc = 2;
    float jumptime = 0;

    //Mouse position
    int mouseX, mouseY;
    int mouseCenterX = (width / 2);
    int mouseCenterY = (height / 2);
    SDL_WarpMouseGlobal(mouseCenterX, mouseCenterY);

    //Pi
    float halfPi = M_PI / 2;
    float twoPi = M_PI * 2;

    while (true) {

        bool redraw = false;
        bool mouseMoved = false;

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit(0, window, ctx);
            }
            if (event.type == SDL_MOUSEMOTION) {
                SDL_GetGlobalMouseState(&mouseX, &mouseY);
                mouseMoved = true;
            }
        }

        if (keyStates[SDL_SCANCODE_ESCAPE]) {
            quit(0, window, ctx);
        }

        //Camera rotation
        if (mouseMoved) {
            if (mouseX < mouseCenterX) {
                camRotDir -= (rotBy * (mouseCenterX - mouseX));
                if (camRotDir < -M_PI) {
                    camRotDir += twoPi;
                }
                SDL_WarpMouseGlobal(mouseCenterX, mouseCenterY);
                redraw = true;
            }
            if (mouseX > mouseCenterX) {
                camRotDir += (rotBy * (mouseX - mouseCenterX));
                if (camRotDir > M_PI) {
                    camRotDir -= twoPi;
                }
                SDL_WarpMouseGlobal(mouseCenterX, mouseCenterY);
                redraw = true;
            }
            if (mouseY < mouseCenterY) {
                if (camRotAlt >= -halfPi) {
                    camRotAlt -= (rotBy * (mouseCenterY - mouseY));
                    SDL_WarpMouseGlobal(mouseCenterX, mouseCenterY);
                } else {
                    camRotAlt = -halfPi;
                }
                redraw = true;
            }
            if (mouseY > mouseCenterY) {
                if (camRotAlt <= halfPi) {
                    camRotAlt += (rotBy * (mouseY - mouseCenterY));
                    SDL_WarpMouseGlobal(mouseCenterX, mouseCenterY);
                } else {
                    camRotAlt = halfPi;
                }
                redraw = true;
            }
        }

        //Camera position
        if (keyStates[SDL_SCANCODE_A]) {
            camx -= (sin(camRotDir) * (shiftBy));
            camz -= (cos(camRotDir) * (shiftBy));
            redraw = true;
        }
        if (keyStates[SDL_SCANCODE_D]) {
            camx += (sin(camRotDir) * (shiftBy));
            camz += (cos(camRotDir) * (shiftBy));
            redraw = true;
        }
        if (keyStates[SDL_SCANCODE_S]) {
            camx += (sin(camRotDir + halfPi) * (shiftBy));
            camz += (cos(camRotDir + halfPi) * (shiftBy));
            redraw = true;
        }
        if (keyStates[SDL_SCANCODE_W]) {
            camx -= (sin(camRotDir + halfPi) * (shiftBy));
            camz -= (cos(camRotDir + halfPi) * (shiftBy));
            redraw = true;
        }
        if (keyStates[SDL_SCANCODE_SPACE]) {
            if (!jump) {
                jump = true;
                jumpinity = camy;
                jumptime = 0;
            }
            redraw = true;
        }

        //Jump movement
        if (jump) {
            jumptime += 0.01;
            camy = (jumpinity + (jumpinitveloc * jumptime) + (.5 * -9.5 * jumptime * jumptime));
            if (camy <= 0) {
                jump = false;
                camy = 0;
            }
            redraw = true;
        }

        if (redraw) {
            clear();
            draw(whratio, polyptrs, color, transparency, camx, camy, camz, camRotDir, camRotAlt, camrz, window);
        }
        
    }

    //Odd exit
    quit(1, window, ctx);
    return 0;
}
