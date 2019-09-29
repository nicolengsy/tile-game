#include "puzzle_move.h"

using namespace std;

PuzzleMove::PuzzleMove(Board* board) :
  tileMove(0), b(board), g(0), h(0), f(0), prev(nullptr)
{

}

// Constructor for subsequent search boards 
// (i.e. those returned by Board::potentialMoves() )
PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent) :
  tileMove(tile), b(board), h(0), f(0), prev(parent)
{
  g = prev->g + 1;
}

// Destructor
PuzzleMove::~PuzzleMove()
{
  delete b;
}
