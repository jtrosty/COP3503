

CC=g++
CFLAGS=-g -Wall
OBJS=main1.o
BIN = main

all:$(BIN)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r main *.o *.dSYM

run: 
	./main

cleanMakeRun:
	$(RM) -r main *.o *.dSYM
	$(CC) $(CFLAGS) main1.cpp -o main
	./main
