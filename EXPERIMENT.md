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

An Experiment: Using A Static Heuristic
---------------------------------------

To see how the game would perform differently, a game ran
