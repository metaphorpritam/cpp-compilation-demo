#include "../include/geometry.h"
#include <stdio.h>
#include <math.h>

// Point struct method implementations
void Point::print() const {
    printf("Point(%.2f, %.2f)\n", x, y);
}

float Point::distance_to_origin() const {
    return sqrt(SQUARE(x) + SQUARE(y));
}

// Circle class implementation
Circle::Circle(float radius, float x, float y)
    : radius(radius), center{x, y} {
}

float Circle::area() const {
    return PI * SQUARE(radius);
}

float Circle::circumference() const {
    return 2 * PI * radius;
}

void Circle::print() const {
    printf("Circle with radius %.2f at ", radius);
    center.print();
}
