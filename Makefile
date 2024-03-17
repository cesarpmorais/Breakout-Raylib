# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# Files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
MAIN_FILE := main.cpp
EXECUTABLE := $(BIN_DIR)/breakout

# Raylib flags
RAYLIB_FLAGS := -lraylib -ldl -lpthread -lm -lX11

# Target: All
all: $(EXECUTABLE)

# Target: Executable
$(EXECUTABLE): $(OBJ_FILES) $(MAIN_FILE)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(RAYLIB_FLAGS)

# Target: Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Target: Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
