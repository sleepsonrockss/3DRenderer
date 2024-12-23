# Compiler and flags
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

# Source and object files
SRCS = src/assg.c src/vector.c src/spheres.c src/color.c
OBJS = $(SRCS:.c=.o)

# Default target to build all executables
all: MS1 MS2 FS

# Target to build MS1 executable
MS1: CFLAGS += -DMS1
MS1: $(OBJS)
	$(CC) $(CFLAGS) -o MS1_assg $(OBJS) $(LDFLAGS)

# Target to build MS2 executable
MS2: CFLAGS += -DMS2
MS2: $(OBJS)
	$(CC) $(CFLAGS) -o MS2_assg $(OBJS) $(LDFLAGS)

# Target to build FS executable
FS: CFLAGS += -DFS
FS: $(OBJS)
	$(CC) $(CFLAGS) -o FS_assg $(OBJS) $(LDFLAGS)

# Rule to compile object files
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove compiled files
clean:
	rm -f $(OBJS) MS1_assg MS2_assg FS_assg
