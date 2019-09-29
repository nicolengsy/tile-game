#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;

void swap(int& num1, int& num2);

Board::Board(int dim, int numInitMoves, int seed )
{
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::Board(const Board& b)
{
  size_ = b.size();
  tiles_ = new int[size_];
  for (int i = 0; i < size_; ++i) {
    tiles_[i] = b[i];
  }
}

Board::~Board()
{
  delete[] tiles_;
}


void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    stringstream ss;
    ss << "Invalid move of tile " << tile << " at ";
    ss << tr << "," << tc << " and blank spot at ";
    ss << br << "," << bc << endl;
    throw BoardMoveError(ss.str());
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  int blank = 0;

  // Finds index of blank space
  while (blank < size_ && tiles_[blank] != 0) {
    ++blank;
  }

  // Creates map
  map<int, Board*> pMoves;

  // Slides top piece: when blank is on row >0
  if (blank/dim() > 0) {
    Board* b1 = new Board(*this);
    b1->move((*b1)[blank-dim()]);
    pMoves[(*b1)[blank]] = b1;
  }

  // Slides bottom piece: when blank is on row <maxRow
  if (blank/dim() < dim()-1) {
    Board* b2 = new Board(*this);
    b2->move((*b2)[blank+dim()]);
    pMoves[(*b2)[blank]] = b2;
  }

  // Slides left piece: when blank is on col >0
  if (blank%dim() > 0) {
    Board* b3 = new Board(*this);
    b3->move((*b3)[blank-1]);
    pMoves[(*b3)[blank]] = b3;
  }

  // Slides right piece: when blank is on col 
  if (blank%dim() < dim()-1) {
    Board* b4 = new Board(*this);
    b4->move((*b4)[blank+1]);
    pMoves[(*b4)[blank]] = b4;
  } 

  return pMoves;
}

// Complete this function
bool Board::solved() const
{
  for (int i = 0; i < size_; ++i) {
    if (tiles_[i] != i) return false;
  }
  return true;
}


const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc];
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}


// Checks if this board is less-than another.  
// We define less than as a "string-style" comparison 
// of the tile array (i.e. Starting by comparing
// the 0-th tile in this Board and the other.
// If this board's tile is less than the other board's
// tile value, return true. If they are equal,
// continue with the next tile location and repeat).
bool Board::operator<(const Board& rhs) const
{
  for (int i = 0; i < size_; ++i) {
    if (tiles_[i] < rhs[i]) return true;
    else if (tiles_[i] > rhs[i]) return false;
  }
  return false;
}

// Prints the board in the desired 2D format
//  You MUST utilize printRowBanner() so we have
//  a common output format.
ostream& operator<<(std::ostream &os, const Board &b)
{
  b.printRowBanner(os);

  for (int i = 0; i < b.size(); ++i) {
    // Prints blank for zeros
    if (b[i] == 0) {
      os << "|  ";
    }

    // Prints w/o space for two digit nums
    else if (b[i] > 9) {
      os << "|" << b[i];
    }

    // Prints w/ space for one digit nums
    else {
      os << "| " << b[i];
    }
    if (i%b.dim() == b.dim()-1) {
      os << "|" << endl;
      b.printRowBanner(os);
    }
  }

  return os;
}