Testing Different Heuristics
============================

How The Heuristic Works
-----------------------

The heuristic evaluation function can be described by the following pseudocode:

	function calcHeuristic(Board)
		where C is a constant 100 / N:

		for each user play and opponent play of length x on the board:
			heuristic += (C * x)(user play * x) - (C * x)(opponent play * x)

		if the user will win or block the opponent
			heuristic = +∞

		if the opponent will win
			heuristic = -∞

		return heuristic

An Experiment: Using Static Heuristics
---------------------------------------

Throughout the development of this game, a recurring question I had was: "just how important are heuristic functions?" In order to find out, I decided to test the game against two non-calculated heuristics: zero and a random number. The hypothesis made for each was as follows:

- **Zero:** Minimax will either pick the first move it finds or the last. If the rest of the tree is pruned, it will select the first move. If not, the last seeing it was the last move in memory. The game will win by repetition.
- **Random Number:** With the lack of strategy, the game will win by chance eventually, however, this may take an extremely long time.

### Testing Zero
The hypothesis behind zero was seen immediately after the game was run. The game would play the first move it found, which was always the first column. Once the first column filled, it would overflow. The game would continue to add checkers in a linear fashion until it happened to connect N by chance. This is due to alpha-beta pruning cutting of the remainder of the tree once it becomes apparent that the remaining heuristics are all zero.

### Testing Random
To test random, the return statement of heuristic method was replaced with a call to rand_from_range(), which generates a random number given a range. The range given during this experiment was 0 to 100. Surprisingly, the game performed similarly to how the zero test performed. This was most likely attributed to issues in the seeding of the system's rand() function, as any repetition among its output could cause the game to perform similarly to how it performs when purely static heuristics, such as zero, are given.
