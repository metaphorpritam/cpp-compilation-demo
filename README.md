# C++ Compilation Demo

This project demonstrates key C++ compilation concepts:
- Preprocessor directives and constants
- Functions, structs, and classes
- Static variables and functions
- Object files and linking
- Debugging with GDB
- Makefiles

## Building the Project

Standard build:
```
make
```

Debug build (includes debug symbols and enables DEBUG macro):
```
make debug
```

Clean build files:
```
make clean
```

Rebuild everything:
```
make rebuild
```

Examine object files:
```
make objdump
```

## Running the Program

Standard version:
```
./bin/cpp_demo
```

Debug version:
```
./bin/cpp_demo_debug
```

## Project Structure

- `include/`: Header files
- `src/`: Source files
- `obj/`: Object files (created during build)
- `bin/`: Executables (created during build)
