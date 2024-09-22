# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRC = genTree.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = genTree

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to build the object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
