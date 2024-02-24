CC = gcc
CFLAGS = -Wall -pthread

miniproject: program1 program2

program1: program1.c
	$(CC) $(CFLAGS) program1.c -o program1

program2: program2.c
	$(CC) $(CFLAGS) program2.c -o program2

clean:
	rm -f program1 program2 /tmp/myfifo
