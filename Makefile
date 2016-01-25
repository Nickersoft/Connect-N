##Start of the Makefile

connect-n: main.o player.o tools.o board.o
	g++ -g -o Connect-N main.o player.o tools.o board.o

main.o: main.cpp
	g++ -g -Wall -c main.cpp

player.o: player.cpp player.h
	g++ -g -Wall -c player.cpp

board.o: board.cpp board.h
	g++ -g -Wall -c board.cpp

tools.o: tools.cpp tools.h
	g++ -g -Wall -c tools.cpp

run_sample:
	make clean && make
	rm -f ./referee/*.class
	cd ./referee && javac Referee.java Board.java
	java referee.Referee "./Connect-N" "./Connect-N" 6 7 3 10 10

clean:
	rm -f *.o ./Connect-N

##End of Makefile
