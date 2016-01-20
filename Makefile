##Start of the Makefile

connect-n: main.o player.o tools.o board.o node.o
	g++ -g -o Connect-N main.o player.o tools.o board.o node.o

main.o: main.cpp
	g++ -g -Wall -c main.cpp

player.o: player.cpp player.h
	g++ -g -Wall -c player.cpp

board.o: board.cpp board.h
	g++ -g -Wall -c board.cpp

node.o: node.cpp node.h
	g++ -g -Wall -c node.cpp

tools.o: tools.cpp tools.h
	g++ -g -Wall -c tools.cpp

run_sample:
	java -jar Referee.jar "./Connect-N" "./Connect-N" 6 7 3 10 10

clean:
	rm -f *.o ./Connect-N

##End of Makefile
