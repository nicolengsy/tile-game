#include "puzzle_heur.h"
#include <cmath>


int PuzzleManhattanHeuristic::compute(const Board&b)
{
	int h = 0;
	int dim = b.dim();

	// Loops through board to sum up manhattan distances
	for (int i = 0; i < b.size(); ++i) {
		if (b[i] != i && b[i] != 0) {
			int x = abs(b[i]/dim - i/dim);
			int y = abs(b[i]%dim - i%dim);
			h += x + y;
		}
	}
	return h;
}

// Tiles-Out-Of-Place: counts the number of tiles out of place EXCLUDING the blank tile.
int PuzzleOutOfPlaceHeuristic::compute(const Board&b)
{
	int h = 0;
	for (int i = 0; i < b.size(); ++i) {
		if (b[i] != i && b[i] != 0) ++h;
	}
	return h;
}



int PuzzleBFSHeuristic::compute(const Board&b)
{
	return 0;
}