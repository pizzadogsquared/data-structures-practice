# Define the compiler and the flags constants
CC = gcc
CFLAGS = -Wall

# Define the target executable
TARGET = mosaic_restoration

# Define the object files
OBJ = mosaic_lib.o mosaic_main.o

# Build the target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Explicit rule to create object files from .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Creates a cleanup routine to remove object and target files
clean:
	rm -f $(OBJ) $(TARGET)

# Creates a run routine to run your program
run: $(TARGET)
	$(TARGET).exe