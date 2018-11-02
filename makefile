all: Poker.o 
    gcc Poker.o -o poker
Poker.o: Poker.c Poker.h
    gcc -I . -c Poker.c

clean:
    rm -rf *.o
    rm target_bin
