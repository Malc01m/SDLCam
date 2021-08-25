#include <vector>
#include <tuple>
#include "math.h"
#include "assert.h"

/*

//Extrema

//Returns the minimum or maximum value of the set of vertices in (x, y, z), (x, y, z)... format vs
//int axis: x=0, y=1, or z=2
//bool max: true for maximum, false for minimum
float getExtrema(std::vector<float[3]> vs, int axis, bool max) {

    //The size of vs
    static int s = vs.size();

    //Check that we have a good axis
    assert(((axis == 0) || (axis == 1) || (axis == 2)) && "getExtrema: Bad axis");

    //The current min/max found, set to first value initially
    float m = vs.at(0)[axis];

    //Are there more to compare to?
    if (s > 1) {
        //Start from the second, iterate through the last
        for (int i = 1; i < s; i++) {
            if (max == true) {
                if (vs.at(i)[axis] > m) {
                    m = vs.at(i)[axis];
                }
            } else {
                if (vs.at(i)[axis] < m) {
                    m = vs.at(i)[axis];
                }
            }
        }
    }

    return m;
}

//Dimensions

//Returns the dimensions of vertices in (x, y, z), (x, y, z)... format vs on an axis
float getDimensions(std::vector<float[3]> vs, int axis) {
    return (getExtrema(vs, axis, true) - getExtrema(vs, axis, false));
}

//Center

//Returns the value of the center of vertices in (x, y, z), (x, y, z)... format vs on an axis
float getCenter(std::vector<float[3]> vs, int axis) {
    return (getExtrema(vs, axis, false) + (getDimensions(vs, axis) / 2));
}

//Returns vertices in (x, y, z), (x, y, z)... format vs centered on an axis around a center value
std::vector<float[3]> centerAt(std::vector<float[3]> vs, int axis, float center) {
    float origCenter = getCenter(vs, axis);
    //Check that there are a nonzero number of float arrays in the poly's vertices
    if (vs.size() > 0) {
        for (uint i = 1; i < vs.size(); i++) {
            vs.at(i)[axis] = vs.at(i)[axis] - origCenter + center;
        }
        return vs;
    }
}
*/

//Returns distance between points (a1, b1) and (a2, b2)
float getDist(float a1, float b1, float a2, float b2) {
    return (sqrt(pow(a1 - a2, 2) + pow(b1 - b2, 2)));
}

//Returns distance between points (a1, b1) and (0, 0)
float getDistFromOrigin(float a1, float b1) {
    return (sqrt(pow(a1, 2) + pow(b1, 2)));
}