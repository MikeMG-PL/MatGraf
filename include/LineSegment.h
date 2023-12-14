#pragma once

#include "Line.h"

class LineSegment : public Line
{
public:
    LineSegment(const Vector& p, const Vector& v) : Line(p, v) {}
};
