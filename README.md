Connect-N
=========

Connect-N is a terminal-based game similar to Connect 4, with the exception of the there being a variable number of checkers that can be matched in a row.

The game uses a Java-based referee to interact with the game, which can play against other users or against itself. It uses the Minimax algorithm with alpha-beta pruning to figure out the best moves to play against its opponent.

Prerequisites
-------------

- [g++ Compiler](https://www.gnu.org/software/gcc/releases.html)
- [Java](https://www.java.com/en/download/) and the [Java SE Development Kit](http://www.oracle.com/technetwork/java/javase/downloads/index.html)
- [GNU Make](https://www.gnu.org/software/make/)

Why C++ AND Java?
-----------------

This program was originally meant to be written in Java, however, an individual who originally collaborated with me on the project was more fluent in C, so C++ was chosen as a happy medium. That collaborator left the project shortly thereafter, now leaving us with this strange hybrid of C++ and Java code.

Setup For Windows
-----------------

Special instructions are required in order to run Connect-N on Windows. If you are using Linux or OS X, the prerequisites listed above can be installed using a package manager (`apt-get` on Linux or [Homebrew](http://brew.sh/)/[MacPorts](https://www.macports.org/) on OS X).

However, if you do have Windows, you'll need [Cygwin](https://cygwin.com/install.html) to compile and run the game. Once you have downloaded the Cygwin installer package, run it and begin following the setup wizard. Eventually, you will be presented with a list of packages to install.

Expand "Devel". Find and check the following three packages.

1. gcc-core: GNU Compiler Collection (C, OpenMP) (v. 5.3.0-1)
2. gcc-g++: GNU Compiler Collection (C++) (v. 5.3.0-1)
3. make: The GNU version of the 'make utility' (v. 4.1-1)

Clicking "Skip" will cycle through the installation options. If the package isn't currently installed, the only other options will be version numbers to install. If the package is installed, "Keep" and "Uninstall" will be among the other options. If a version number is displayed, it means that the package is marked for installation.

**Important:** although the version numbers do not necessarily matter for this program (you should still try to shoot for the most recent versions), gcc-core and gcc-g++ *must* have the same version number, otherwise you will run into issues while compiling. As of January 25, 2016, the most recent version of gcc-core and gcc-g++ is 5.3.0-1.

Once Cygwin is installed, open up the Cygwin terminal. Run the following command:

	export PATH=$PATH:'<PATH-TO-JDK>'

where PATH-TO-JDK is the directory of your JDK `bin` directory. This command allows Cygwin to access `javac`, which is required to compile the referee.

*Note*: This is usually located at C:\Program Files\Java\jdk.x.x.x_xx\bin on most default installations, the x's representing version and build numbers.

Now you can continue to compile and run the program as outlined below.  

Running the Game
----------------

### The Easy Way

It is extremely simple to use the game. If you wish to run the game against itself, simply `cd` into the source directory and run:

	make play_computer

If you wish to play the game yourself, just run:

	make play_user

Keep in mind that while playing the game on your own, you must input your moves in the following format:

	<column> <operation>

where the columns are zero-based (i.e. the first column is 0, the second is 1, etc.) and the operations that can be performed are either 1 (drop), which drops a checker in the column from the top, or 0 (pop out), which pops a checker out from the bottom of the given column. Please note that you can only play 1 pop out move per game.

### The (Not So) Hard Way

If you wish to customize the game, you can run the original commands yourself:

	make
	java referee.Referee_User "./Connect-N" "./Connect-N" 6 7 3 10 10

where the last five arguments are as follows:

1. Height of the board
2. Width of the board
3. Number of checkers to match in a row ('N')
3. Time limit for players to announce their names
4. Time limit for players to make a move

The above command is for playing against the computer by yourself. If you wish to have the computer play itself, simply replace `Referee_User` with `Referee_Computer`.

To use the original, untampered version of the referee (which plays the computer against itself), run:

	make
	java -jar ./referee/Referee.jar "./Connect-N" "./Connect-N" 6 7 3 10 10

Empirical Valuation
-------------------

An empirical valuation was performed on this game in order to test the significance of the heuristic function. For more info, click [here](EXPERIMENT.md).

Debugging
---------

The source directory comes with a nifty Tools class, which can be used for debugging purposes. Two noticeable functions are `log()` and `error()`, which write to `debug.log` and `error.log`, respectively. Both functions can also take in an extra integer parameter (in addition to a string), which will format the string using the integer provided (like printf).

Known limitations
-----------------

Due to time constraints, this implementation of Connect-N is not perfect. Connect-N does not go out of its way to avoid timeouts. Implementing such a feature involves multithreading in C++ and the raw handling of shared memory, which could not be achieved by this project's deadline. As a result, timeouts must be avoid by manually changing the MAXDEPTH constant found in board.h.
