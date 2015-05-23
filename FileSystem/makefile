CC := gcc
CFLAGS := -Wall -fmessage-length=0 -lcommons

OBJS := FileSystem.o consola.o
HDRS := consola.h

# All
all: filesystem

# FileSystem
filesystem: $(OBJS)
	$(CC) $(CFLAGS) -o FileSystem $(OBJS)

FileSystem.o: FileSystem.c $(HDRS)
	$(CC) -c $(CFLAGS) FileSystem.c

consola.o: consola.c consola.h
	$(CC) -c $(CFLAGS) consola.c


# Clean
clean:
	rm $(OBJS)