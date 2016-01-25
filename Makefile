##Start of the Makefile

all:
	make clean
	cd ./referee && javac Referee_User.java Board.java
	make connect-n

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

play_computer:
	make clean && make
	rm -f ./referee/*.class
	cd ./referee && javac Referee_Computer.java Board.java
	java referee.Referee_Computer "./Connect-N" "./Connect-N" 6 7 3 10 10

play_user:
	make clean && make
	rm -f ./referee/*.class
	cd ./referee && javac Referee_User.java Board.java
	java referee.Referee_User "./Connect-N" "./Connect-N" 6 7 3 10 10

clean:
	rm -f ./referee/*.class
	rm -f *.o ./Connect-N

##End of Makefile
