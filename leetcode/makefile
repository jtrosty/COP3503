

CC=clang
CFLAGS=-g -Wall
OBJS=file1.o
BIN = main

all:$(BIN)

main: $(OBJS)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r main *.o *.dSYM

run: 
	./main
