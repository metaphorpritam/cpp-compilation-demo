#include "../include/math_utils.h"
#include <stdio.h>

// Static variable demonstration - properly defined in the implementation file
static int calculation_count = 0;

// Static function implementation for educational use in main.cpp
float squared(float x) {
    return SQUARE(x); // Using the macro defined in constants.h
}

float add(float a, float b) {
    calculation_count++;
    return a + b;
}

float subtract(float a, float b) {
    calculation_count++;
    return a - b;
}

float multiply(float a, float b) {
    calculation_count++;
    return a * b;
}

float divide(float a, float b) {
    calculation_count++;
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return a / b;
}

int get_calculation_count() {
    return calculation_count;
}
