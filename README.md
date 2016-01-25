# Connect-N

Connect-N is a terminal-based game similar to Connect 4, with the exception of the there being a variable number of checkers that can be matched in a row. 

The game uses a Java-based referee to interact with the game, which can play against other users or against itself. It uses the Minimax algorithm with alpha-beta pruning to figure out the best moves to play against its opponent.

## Prerequisites 

- [g++ Compiler](https://www.gnu.org/software/gcc/releases.html)
- [The Java Runtime](https://www.java.com/en/download/) (any recent version)
- [GNU Make](https://www.gnu.org/software/make/)

## Running the Game

### The Easy Way

It is extremely simple to use the game. If you wish to run the game against itself, simply `cd` into the source directory and run:

	make play_computer
	
If you wish to play the game yourself, just run:

	make play_user
	
### The (Not So) Hard Way	
	
If you wish to customize the game, you can run the original commands yourself:

	make clean && make
	java referee.Referee_User "./Connect-N" "./Connect-N" 6 7 3 10 10
	
where the last five arguments are as follows:

1. Height of the board
2. Width of the board
3. Number of checkers to match in a row ('N')
3. Time limit for players to announce their names
4. Time limit for players to make a move

The above command is for playing against the computer by yourself. If you wish to have the computer play itself, simply replace `Referee_User` with `Referee_Computer`.

To use the original, untampered version of the referee (which plays the computer against itself), run:

	make clean && make
	java -jar ./referee/Referee.jar "./Connect-N" "./Connect-N" 6 7 3 10 10	
## Debugging

The source directory comes with a nifty Tools class, which can be used for debugging purposes. Two noticeable functions are `log()` and `error()`, which write to `debug.log` and `error.log`, respectively. Both functions can also take in an extra integer parameter (in addition to a string), which will format the string using the integer provided (like printf). 