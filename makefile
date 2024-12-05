CC = gcc
CFLAGS = -g -Wall
TARGET = test_heap_manager

all: system version

# Compile with system's malloc/free
system:
	$(CC) $(CFLAGS) -o $(TARGET) test_heap_manager.c

# Compile with custom heap manager
version:
	$(CC) $(CFLAGS) -DCUSTOM_ALLOCATOR -o $(TARGET) test_heap_manager.c heap_manager.c

clean:
	rm -f $(TARGET)
