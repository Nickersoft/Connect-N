##Start of the Makefile

connect-n: main.o board.o
	g++ -o Connect-N main.o board.o

main.o: main.cpp main.h
	g++ -Wall -c main.cpp

board.o: board.cpp board.h
	g++ -Wall -c board.cpp

clean:
	rm -f *.o ./Connect-N

##End of Makefile
