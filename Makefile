# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -Iinclude -std=c++17

# Directories
SRCDIR = src
INCDIR = inc
OBJDIR = obj
BINDIR = bin

# Target executable
TARGET = $(BINDIR)/cRush

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Object file rule
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if not exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean the build directory
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
