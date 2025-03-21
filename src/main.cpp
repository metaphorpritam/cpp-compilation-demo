#include <stdio.h>
#include "../include/constants.h"
#include "../include/math_utils.h"
#include "../include/geometry.h"

int main() {
    printf("C++ Compilation Demo\n");
    printf("====================\n\n");

    // Using preprocessor constants
    printf("Value of PI: %.5f\n", PI);
    printf("SQUARE(5) = %d\n\n", SQUARE(5));

    // Using math functions
    printf("Math Operations:\n");
    float a = 10.0f, b = 5.0f;
    printf("a = %.1f, b = %.1f\n", a, b);
    printf("a + b = %.1f\n", add(a, b));
    printf("a - b = %.1f\n", subtract(a, b));
    printf("a * b = %.1f\n", multiply(a, b));
    printf("a / b = %.1f\n", divide(a, b));
    printf("a² = %.1f\n", squared(a));  // Using the squared function
    printf("Total calculations: %d\n\n", get_calculation_count());

    // Using struct
    printf("Geometry - Point:\n");
    Point p = {3.0f, 4.0f};
    p.print();
    printf("Distance to origin: %.2f\n\n", p.distance_to_origin());

    // Using class
    printf("Geometry - Circle:\n");
    Circle c(5.0f, 1.0f, 2.0f);
    c.print();
    printf("Area: %.2f\n", c.area());
    printf("Circumference: %.2f\n\n", c.circumference());

    // Debug macro demonstration
#ifdef DEBUG
    DEBUG_PRINT("This is a debug message");
#endif

    return 0;
}
