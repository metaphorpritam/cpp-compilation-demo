# C++ Compilation Guide: From Source to Executable

This guide demonstrates the C++ compilation process in a practical way, covering fundamental concepts like preprocessor directives, functions, structs, classes, static variables, object files, linking, debugging, and makefiles.

## Directory Structure

```.txt
cpp-demo/
├── include/
│   ├── constants.h       # Contains preprocessor directives and constants
│   ├── math_utils.h      # Function declarations for math operations
│   └── geometry.h        # Struct and class declarations for geometric shapes
├── src/
│   ├── main.cpp          # Program entry point
│   ├── math_utils.cpp    # Implementation of math functions
│   └── geometry.cpp      # Implementation of geometry structures and classes
├── Makefile              # Build instructions
└── README.md             # Project documentation
```

## The Code Files

Let's examine each file in detail:

### include/constants.h

```c
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
```

### include/math_utils.h

```c
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
```

### include/geometry.h

```c
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
```

### src/math_utils.cpp

```c
#include "../include/math_utils.h"
#include <stdio.h>

// Static variable demonstration - properly defined in the implementation file
static int calculation_count = 0;

// Implementation of squared function
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
```

### src/geometry.cpp

```c
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
```

### src/main.cpp

```c
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
```

## Makefile

```makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
DEBUG_FLAGS = -g -DDEBUG

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Executable names
EXECUTABLE = $(BIN_DIR)/cpp_demo
DEBUG_EXECUTABLE = $(BIN_DIR)/cpp_demo_debug

# Default target
all: directories $(EXECUTABLE)

# Debug target
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: directories $(DEBUG_EXECUTABLE)

# Create directories if they don't exist
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Link executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Link debug executable
$(DEBUG_EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Show object file contents
.PHONY: objdump
objdump: $(OBJECTS)
	@echo "Displaying symbols in math_utils.o:"
	@objdump -t $(OBJ_DIR)/math_utils.o
	@echo "\nDisplaying disassembly of math_utils.o:"
	@objdump -d $(OBJ_DIR)/math_utils.o

# Target to clean and rebuild
rebuild: clean all

# Phony targets (not associated with files)
.PHONY: all debug clean rebuild directories
```

## Understanding the Compilation Process

### 1. Preprocessing

The preprocessor handles directives like `#include`, `#define`, and `#ifdef`. It processes the source files before actual compilation.

Example:

```bash
# Preprocess main.cpp and save the output
g++ -E src/main.cpp -I include > main.preprocessed.cpp
```

This will expand all the includes and macros, showing what the compiler actually sees.

### 2. Compilation

The compiler converts C++ source code into object files. Each source file is compiled separately.

```bash
# Compile math_utils.cpp to object file
g++ -c src/math_utils.cpp -I include -o obj/math_utils.o
```

### 3. Linking

The linker combines all object files and libraries to create the final executable.

```bash
# Link all object files to create executable
g++ obj/main.o obj/math_utils.o obj/geometry.o -o bin/cpp_demo
```

## Examining Object Files with objdump

`objdump` is a powerful utility to inspect object files. Here's how to use it:

### Displaying Symbol Table

```bash
objdump -t obj/math_utils.o
```

Sample output:

```.txt
obj/math_utils.o:     file format elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*  0000000000000000 math_utils.cpp
0000000000000000 l    d  .text  0000000000000000 .text
...
0000000000000000 g     F .text  000000000000001e _Z3addff
000000000000001e g     F .text  000000000000001e _Z8subtractff
000000000000003c g     F .text  000000000000001e _Z8multiplyff
000000000000005a g     F .text  000000000000003a _Z6divideff
0000000000000094 g     F .text  000000000000000c _Z20get_calculation_countv
0000000000000000 g     O .bss   0000000000000004 calculation_count
```

### Disassembling the Code

```bash
objdump -d obj/math_utils.o
```

Sample output:

```.txt
obj/math_utils.o:     file format elf64-x86-64

Disassembly of section .text:

0000000000000000 <_Z3addff>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   ...
```

### Understanding Name Mangling

Notice that function names are "mangled" (e.g., `_Z3addff`). This is C++'s way of implementing function overloading. You can demangle them:

```bash
# Using c++filt to demangle symbols
objdump -t obj/math_utils.o | c++filt
```

### Comparing Debug vs Release Object Files

Debug builds contain more information for debugging:

```bash
# Compare size of debug vs release object files
make clean
make
du -h obj/math_utils.o
make clean
make debug
du -h obj/math_utils.o
```

## Debugging with GDB

To debug the program:

1. Build with debug flags: `make debug`
2. Run gdb: `gdb bin/cpp_demo_debug`
3. Basic GDB commands:
   - `break main` - Set breakpoint at main
   - `run` - Start the program
   - `next` or `n` - Execute next line (step over)
   - `step` or `s` - Step into function calls
   - `print variable` - Print variable value
   - `continue` - Continue execution
   - `quit` - Exit GDB

## Understanding Static Variables and Functions

- Static variables like `calculation_count` in `math_utils.cpp` maintain their values between function calls
- Each translation unit (compiled source file) gets its own copy of static variables
- Static variables and functions in header files can lead to issues when the header is included in multiple source files (each file gets its own copy)
- For demonstration purposes, we've moved the static variable and function to the implementation file
- Static functions defined in a .cpp file are only visible within that file, even though they can be declared in the header

## Makefiles Explained

The Makefile contains rules that define how to build the project:

- **Targets**: The things to be built (e.g., `all`, `debug`)
- **Prerequisites**: Files needed to build targets (e.g., object files)
- **Recipes**: Commands to build targets from prerequisites (e.g., compiler commands)

Key Makefile concepts:

- **Variables**: `CXX`, `CXXFLAGS`, etc. hold reusable values
- **Pattern Rules**: `$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp` defines how to build any object file
- **Functions**: `wildcard`, `patsubst` manipulate file lists
- **Phony Targets**: Targets not associated with files (`.PHONY: clean`)

## Compilation Stages Explained

1. **Preprocessing**: Expands macros, includes header files
   - Affected by: `#include`, `#define`, `#ifdef`, etc.

2. **Compilation**: Converts preprocessed code to assembly
   - Affected by: Syntax errors, type errors, compiler flags

3. **Assembly**: Converts assembly to machine code (object files)
   - Result: `.o` files with machine code but unresolved symbols

4. **Linking**: Combines object files to create executable
   - Resolves symbols between object files
   - Links with system libraries
   - Creates the final executable

## Practical Exercises for Students

1. **Modify the code**: Add a new math function and observe changes in the object file
2. **Experiment with macros**: Add a new macro in `constants.h` and use it in the program
3. **Inspect object files**: Compare object files with and without optimization flags
4. **Debug the program**: Set breakpoints and watch variable changes
5. **Modify the Makefile**: Add a new build target with different compiler flags

## Conclusion

This project demonstrates the fundamental concepts of C++ compilation, from source code to executable. By understanding these concepts, you'll have a solid foundation for more advanced C++ development.
