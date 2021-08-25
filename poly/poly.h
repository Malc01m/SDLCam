#pragma once

#include <vector>
#include <tuple>

class Poly {

    public:

        //Constructors
        Poly(std::vector<std::array<float, 3>> vs, float c[4]);

        //Setters

        //Sets the poly's vertices to those in vector vs
        void setVerts(std::vector<std::array<float, 3>> vs);

        //Sets the poly's color to c, an array of floats in (r, g, b, t) format
        void setColor(float c[4]);

        //Sets the poly's fixedness to the screen (for hud purposes)
        void setFixed(bool f);

        //Getters

        //Returns the poly's vertices as a vector of floats in (x,y,z),(x,y,z)... format
        std::vector<std::array<float, 3>> getVerts();

        //Sets pointer c to poly's color as an array of floats in (r, g, b, t) format
        float *getColor();

        //Gets the poly's fixedness to the screen (for hud purposes)
        bool getFixed();

        //Manipulators

        //Shifts the vertices on axis by offset
        void shiftVerts(float offset, int axis);

    private:

        //Polygon's vertices in (x,y,z),(x,y,z)... format
        std::vector<std::array<float, 3>> verts;

        //Polygon's color in (r, g, b, t) format
        float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

        //Whether this polygon moves with the camera
        bool fixed = false;

};