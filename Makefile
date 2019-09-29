CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=board.o heap.h puzzle_solver.o puzzle_heur.o puzzle_move.o puzzle.o

all: puzzle

puzzle: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

puzzle.o: puzzle_solver.o board.o puzzle_heur.o heap.h puzzle_move.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle.cpp

puzzle_solver.o: board.o puzzle_heur.o puzzle_move.h heap.h puzzle_solver.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_solver.cpp

puzzle_move.o: board.o puzzle_move.h puzzle_move.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_move.cpp


board.o: board.h board.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c board.cpp

puzzle_heur.o: board.h puzzle_heur.h puzzle_heur.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_heur.cpp


clean:
	rm -f *.o puzzle_solver
