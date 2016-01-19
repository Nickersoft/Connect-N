##Start of the Makefile

connect-n: main.o player.o tools.o board.o node.o
	g++ -o Connect-N main.o player.o tools.o board.o node.o

main.o: main.cpp main.h
	g++ -Wall -c main.cpp

player.o: player.cpp player.h
	g++ -Wall -c player.cpp

board.o: board.cpp board.h
	g++ -Wall -c board.cpp

node.o: node.cpp node.h
	g++ -Wall -c node.cpp

tools.o: tools.cpp tools.h
	g++ -Wall -c tools.cpp

clean:
	rm -f *.o ./Connect-N

##End of Makefile
