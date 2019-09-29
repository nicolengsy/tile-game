#include "puzzle_solver.h"
#include "heap.h"


using namespace std;

// Constructor (makes a copy of the Board and stores it in b_)
//  Also takes a PuzzleHeuristic which will score boards
PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph) :
	b_(b), expansions_(0), ph_(ph)
{
	run();
}

// Destructor
PuzzleSolver::~PuzzleSolver()
{

}

// Run the A* search and builds the solution and tracks
// the number of expansions
void PuzzleSolver::run()
{	
	PuzzleMoveScoreComp cScore;
	PuzzleMoveBoardComp cBoard;
	Heap<PuzzleMove*, PuzzleMoveScoreComp> open(2, cScore);
	PuzzleMoveSet closed(cBoard);
	Board* newB = new Board(b_);
	PuzzleMove* s = new PuzzleMove(newB);
	open.push(s);
	closed.insert(s);
	while (!open.empty()) {
		PuzzleMove* curr = open.top();
		open.pop();

		// If goal is reached, trace and enter into solution deque
		if (curr->b->solved()) {
			while (curr->prev != nullptr) {
				solution_.push_front(curr->tileMove);
				curr = curr->prev;
			}

			// Delete all PuzzleMoves in closed list
			for (PuzzleMoveSet::iterator i = closed.begin(); i != closed.end(); ++i) {
				delete *i;
			}
			return;
		}

		// Else, loop thruogh potential moves of curr, create PuzzleMoves
		map<int, Board*> potentials = curr->b->potentialMoves();
		for (map<int,Board*>::iterator it = potentials.begin(); it != potentials.end(); it++) {
			PuzzleMove* potenMove = new PuzzleMove(it->first, it->second, curr);

			// Finds whether potenMove is in closed list - if yes, don't add and deallocate the move
			bool inClosed = false;
			PuzzleMoveSet::iterator i = closed.begin();
			while (!inClosed && i != closed.end()) {
				if (!cBoard(potenMove, *i) && !cBoard(*i, potenMove)) {
					inClosed = true;
					delete potenMove;
				}
				++i;
			}
			// If potential move isn't in closed list, add to open and closed list
			if (!inClosed) {
				potenMove->h = ph_->compute(*(potenMove->b));
				potenMove->f = potenMove->g + potenMove->h;
				open.push(potenMove);
				closed.insert(potenMove);
				++expansions_;
			}
		}
	}
}

// Return the solution deque
std::deque<int> PuzzleSolver::getSolution()
{
	return solution_;
}

// Return how many expansions were performed in the search
int PuzzleSolver::getNumExpansions()
{
	return expansions_;
}
