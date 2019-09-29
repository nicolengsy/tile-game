
# Tile Game Puzzle Solver
- **Name**: Shin Ying (Nicole) Ng
- **USC ID**: 6499343148
- **Email**: shinyinn@usc.edu


## Description
This project's main file lies in puzzle.cpp, which is a tile game on a n x n board. When user wants a cheat, a sequence of moves to reach the goal is calculated using the A* algorithm. Heuristics are chosen by the user at the last argument of the command line, with choices of either the BFS (0), Tiles-Out-Of-Place (1), or Manhattan (2) heuristic. A priority queue / binary heap is utilized to prioritize low f-scores in the algorithm.

### To compile:
make

### To run:
./puzzle size initMoves seed heur

### Known issues:
No known issues.

### Assumptions made:
None; makes any assumptions already made by skeleton code.

