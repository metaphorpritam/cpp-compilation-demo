#pragma once

#include "constants.h"
#include "math_utils.h"

// Structure demonstration
struct Point {
    float x;
    float y;

    // Methods inside struct
    void print() const;
    float distance_to_origin() const;
};

// Class demonstration
class Circle {
public:
    Circle(float radius, float x = 0.0f, float y = 0.0f);
    float area() const;
    float circumference() const;
    void print() const;

private:
    float radius;
    Point center;
};
