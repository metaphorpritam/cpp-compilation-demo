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
