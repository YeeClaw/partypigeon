CC = gcc
CFLAGS = -Wall -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
DEP = $(SRC:src/%.c=build/%.d)
TARGET = build/partypigeon

.PHONY: all clean

# Default target
all: $(TARGET)

# Link the object files into the target executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^

# Compile each .c file to .o file in the build/ directory
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Generate dependency files (.d) for header file tracking
build/%.d: src/%.c
	$(CC) $(CFLAGS) -M $< > $@

# Include the dependency files for automatic rebuilding
-include $(DEP)

# Clean target: remove the build/ directory
clean:
	rm -rf build/

