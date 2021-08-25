#include "poly.h"

//Constructors

Poly::Poly(std::vector<std::array<float, 3>> vs, float c[4]) {
    verts = vs;
    color[0] = c[0];
    color[1] = c[1];
    color[2] = c[2];
    color[3] = c[3];
}

//Setters

//Sets the poly's vertices to those in vector vs
void Poly::setVerts(std::vector<std::array<float, 3>> vs) {
    verts = vs;
}

//Sets the poly's color to (r, g, b)
void Poly::setColor(float c[4]) {
    color[0] = c[0];
    color[1] = c[1];
    color[2] = c[2];
    color[3] = c[3];
}

//Sets the poly's fixedness to the screen (for hud purposes)
void Poly::setFixed(bool f) {
    fixed = f;
}

//Getters

//Returns the poly's vertices as a vector of floats in (x,y),(x,y)... format
std::vector<std::array<float, 3>> Poly::getVerts() {
    return verts;
}

//Sets pointer c to poly's color as an array of floats (r, g, b, t)
float *Poly::getColor() {
    static float c[4];
    c[0] = color[0];
    c[1] = color[1];
    c[2] = color[2];
    c[3] = color[3];
    return c;
}

//Gets the poly's fixedness to the screen (for hud purposes)
bool Poly::getFixed() {
    return fixed;
}

//Manipulators

void Poly::shiftVerts(float offset, int axis) {
    for (uint i = 0; i < verts.size(); i++) {
        verts.at(i).at(axis) += offset;
    }
}