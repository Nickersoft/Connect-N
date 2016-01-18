##Start of the Makefile

connect-n: main.o player.o tools.o
	g++ -o Connect-N main.o player.o tools.o

main.o: main.cpp main.h
	g++ -Wall -c main.cpp

player.o: player.cpp player.h
	g++ -Wall -c player.cpp

tools.o: tools.cpp tools.h
	g++ -Wall -c tools.cpp

clean:
	rm -f *.o ./Connect-N

##End of Makefile
