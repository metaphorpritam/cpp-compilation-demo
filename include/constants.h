#pragma once

// Preprocessor directives and constants demonstration
#define PI 3.14159265358979323846
#define SQUARE(x) ((x) * (x))

// Conditional compilation demonstration
#ifdef DEBUG
    #define DEBUG_PRINT(x) printf("[DEBUG] %s\n", x)
#else
    #define DEBUG_PRINT(x) // Does nothing when DEBUG is not defined
#endif

// Macro with multiple statements (note the use of do-while(0))
#define SAFE_DELETE(p) do { if(p) { delete (p); (p) = nullptr; } } while(0)
