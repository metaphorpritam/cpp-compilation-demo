#pragma once

#include "constants.h"

// Function declarations
float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);

// Function to get the calculation count
int get_calculation_count();

// Function to calculate square (exposed for educational purposes)
float squared(float x);
