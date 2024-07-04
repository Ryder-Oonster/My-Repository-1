# Makefile
# Compiler
CC := g++

# Compiler flags
CFLAGS := -std=c++0x -Wall -Wextra

# Source files
SRCS := GSensor.cpp GSensorMain.cpp DE1SoChps.cpp PIOControl.cpp DE1SoCfpga.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
TARGET := GSensorMain

.PHONY: all clean

all: $(TARGET)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
