all: Poker     
	gcc Poker.o -o Poker
Poker.o: 
	gcc -I . -c Poker.c

clean:
	rm -rf *.o
	rm -rf Poker
