#include <iostream>
#include <sstream>
#include <cstdlib>
#include <deque>
#include <exception>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

PuzzleHeuristic* makeHeur(int& heur)
{
	PuzzleHeuristic* h = nullptr;
	if (heur == 0) {
		h = new PuzzleBFSHeuristic();
	}
	else if (heur == 1) {
		h = new PuzzleOutOfPlaceHeuristic();
	}
	else if (heur == 2) {
		h = new PuzzleManhattanHeuristic();
	}
	return h;
}


int main(int argc, char *argv[])
{
	if(argc < 5){
		cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
		return 1;
	}

	// CHECK FOR ERRORS
	int n, initMoves, seed, heur;
	try {
		n = stoi(argv[1]);
		initMoves= stoi(argv[2]);
		seed = stoi(argv[3]);
		heur = stoi(argv[4]);		
	} catch(const invalid_argument& e) {
		return -1;
	} catch(const out_of_range& e) {
		return -1;
	}

	// Check dimension and init moves
	if (n <= 0 || n > 10 || initMoves < 0) {
		return -1;
	}

	// Make heuristic
	PuzzleHeuristic* h = nullptr;
	if (heur < 0 || heur > 2) {
		return -1;
	}
	else h = makeHeur(heur);

	Board b = Board(n, initMoves, seed);

	// Loops game until puzzle is solved
	while (!b.solved()) {
		cout << b << endl;
		cout << "Enter tile number to move or -1 for a cheat: ";
		int cmd = 0;
		cin >> cmd;
		cout << endl;

		//If user input is not an int, continue to next iteration
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			continue;
		}
		// If user asks for a cheat, print sequence
		if (cmd == -1) {
			PuzzleSolver ps = PuzzleSolver(b,h);
			deque<int> sol = ps.getSolution();
			cout << "Try this sequence: " << endl;
			for (int i = 0; i < (int)sol.size(); ++i) {
				cout << sol[i] << " ";
			}
			cout << "\n(Expansions = " << ps.getNumExpansions() << ")" << endl << endl;
		}

		else if (cmd == 0) {
			delete h;
			return 0;
		}
		// If user enters an int, try to move
		else {
			if (cmd < 1 || cmd >= b.size()) {
				continue;
			}
			try {
				b.move(cmd);
			} catch(const BoardMoveError& e) {
				cout << e.what() << endl;
				continue;
			}
		}
	}

	// Prints out solved board
	cout << b << endl;


	// Deletes dynamically allocated PuzzleHeuristic
	delete h;
	return 0;
}
