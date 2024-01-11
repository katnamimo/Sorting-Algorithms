CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -gdwarf-4
OBJS = batcher.o stats.o shell.o heap.o quick.o set.o
LFLAGS = -lm
EXEC = sorting

all: $(EXEC)
sorting: sorting.o $(OBJS)
	$(CC) -o sorting sorting.o $(OBJS) $(LFLAGS)
	
sorting.o :sorting.c $(OBJS)
	$(CC) $(CFLAGS) -c sorting.c
	
batcher.o: batcher.c batcher.h
	$(CC) $(CFLAGS) -c batcher.c
	
stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c
	
set.o: set.c set.h
	$(CC) $(CFLAGS) -c set.c

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c
	
heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

quick.o: quick.c quick.h
	$(CC) $(CFLAGS) -c quick.c

clean:
	rm -f $(EXEC) $(OBJS)
format:
	clang-format -i -style=file *.[ch]
