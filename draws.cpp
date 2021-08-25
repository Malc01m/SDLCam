#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL_opengl.h>

#include <vector>
#include <memory>

#include "poly/poly.h"
#include "poly/vertices.cpp"

void clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void draw(float whratio, std::vector<std::shared_ptr<Poly>> polyptrs, GLint color, GLint transparency, float camx, float camy, float camz, float camdirang, float camaltang, float camrotang, SDL_Window* window) {

    if (polyptrs.size() > 0) {

        for (int i = 0; i < static_cast<int>(polyptrs.size()); i++) {

            bool visible = true;
            std::vector<std::array<float, 2>> posverts;

            for (int j = 0; j < static_cast<int>(polyptrs.at(i)->getVerts().size()); j++) {

                //Get vertex position values
                float vertx = polyptrs.at(i)->getVerts().at(j)[0];
                //fprintf(stderr, "Original x: %f\n", vertx);
                float verty = polyptrs.at(i)->getVerts().at(j)[1];
                //fprintf(stderr, "Original y: %f\n", verty);
                float vertz = polyptrs.at(i)->getVerts().at(j)[2];

                if (polyptrs.at(i)->getFixed()) {
                    
                    //The camera doesn't affect fixed polygons. Push vertx and verty without cam transforms.
                    posverts.push_back({vertx, verty * whratio});

                } else {

                    //Relative-to-camera coordinates
                    float relx = (vertx - camx);
                    float rely = (verty - camy);
                    float relz = (vertz - camz);

                    float floorDist = sqrt(pow(relx, 2) + pow(relz, 2));
                    float distFromCam = sqrt(pow(rely, 2) + pow(floorDist, 2));

                    float dirang = camdirang + atan2(relz, relx);
                    float altang = camaltang + atan2(rely, floorDist);

                    float finalx = sin(dirang) * floorDist;
                    float finaly = sin(altang) * distFromCam;

                    float persp = (distFromCam / 3);
                    finalx /= persp;
                    finaly /= persp;
                    finaly *= whratio;

                    posverts.push_back({finalx, finaly});

                }

            }

            if (visible) {

                glBufferData(GL_ARRAY_BUFFER, posverts.size() * 2 * sizeof(posverts[0][0]), posverts.data(), GL_DYNAMIC_DRAW);

                //Set colors
                float r = polyptrs.at(i)->getColor()[0];
                float g = polyptrs.at(i)->getColor()[1];
                float b = polyptrs.at(i)->getColor()[2];
                float t = polyptrs.at(i)->getColor()[3];
                glUniform3f(color, r, g, b);
                glUniform1f(transparency, t);
                
                //Draw
                glDrawArrays(GL_TRIANGLE_STRIP, 0, posverts.size());

            }

        }
        SDL_GL_SwapWindow(window);
    }
}
