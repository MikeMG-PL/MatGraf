#pragma once

#include <vector>

#include "Line.h"
#include "Matrix.h"
#include "Plane.h"

class Cube
{
public:
    Cube(Vector center, float width, float height, float depth);

    bool intersects(Line line) const;

    void rotate(float angle, Vector axis);

    Matrix transformMatrix;
    Vector center;

private:
    float width;
    float height;
    float depth;

    std::vector<Plane> faces;
};

