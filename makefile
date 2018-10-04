all: poker     
	gcc poker.o -o poker
poker.o: 
	gcc -I . -c poker.c

clean:
	rm -rf *.o
	rm -rf poker
