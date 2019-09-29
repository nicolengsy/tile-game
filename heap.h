#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <cmath>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
	/// Constructs an m-ary heap for any m >= 2
	Heap(int m, PComparator c = PComparator());

	/// Destructor as needed
	~Heap();

	/// Adds an item
	void push(const T& item);

	/// returns the element at the top of the heap 
	///  max (if max-heap) or min (if min-heap)
	T const & top() const;

	/// Removes the top element
	void pop();

	/// returns true if the heap is empty
	bool empty() const;

 private:
	/// Add whatever helper functions and data members you need below
	int m_;
	std::vector<T> heap_;
	PComparator c_;

	void trickleUp(int loc);
	void trickleDown(int loc);
	void swap(T& item1, T& item2);



};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) :
	m_(m), c_(c)
{

}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
	heap_.push_back(item);
	trickleUp(heap_.size()-1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap_[0];
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }

  if (heap_.size() == 1) {
  	heap_.pop_back();
  	return;
  }

  heap_[0] = heap_[heap_.size()-1];
  heap_.pop_back();
  trickleDown(0);

}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
	return heap_.empty();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int loc)
{
	int parent = (loc-1)/m_;
	while (parent >= 0 && c_(heap_[loc], heap_[parent])) {
		swap(heap_[loc], heap_[parent]);
		loc = parent;
		parent = (loc-1)/m_;
	}
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(int loc)
{
	// If location is leaf node, return
	// if (log(loc+1) == log(heap_.size())) return;
	if (m_*loc+1 >= (int)heap_.size()) return;

	// Finds the best child
	int first = m_*loc + 1;
	int best = first;
	for (int i = 1; i < m_; ++i) {
		// If child is out of bounds, break
		if (first+i >= (int)heap_.size()) break;

		// Updates best child if needed
		if (c_(heap_[first + i], heap_[best])) {
			best = first + i;
		}
	}

	// Compares current loc with best child
	// If curr loc isn't better than the best, trickle down
	if (c_(heap_[best], heap_[loc])) {
		swap(heap_[loc], heap_[best]);
		trickleDown(best);
	}
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::swap(T& item1, T& item2)
{
	T temp = item1;
	item1 = item2;
	item2 = temp;
}


#endif