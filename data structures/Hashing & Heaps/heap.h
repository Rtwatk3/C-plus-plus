// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

/*****************************************
** This file simulates a heap stored in an array.  
**
** 
***********************************************/
#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.
  void bottomHeapify(int index);
  void topHeapify(int index);
  // *********************************************
  // Private helper function declarations go here!
  // *********************************************

};
template <class T>
Heap<T>::Heap(){
	_used = false;
	T d;
	//push junk data to the front
	_heap.push_back(d);
}

template <class T>
void Heap<T>::insert(const T& object){
	if(_used == false){
		_used = true;
  		//push the first object in
  		_heap.push_back(object);
	}
	else{
		//push a new object in
		_heap.push_back(object);
		//heapify from the bottom up
  		bottomHeapify(_heap.size()-1);
	}
}

template <class T>
void Heap<T>::bottomHeapify(int index){
	//cout<<"index "<<1<<endl;
	//parent = (index-1)/2
	int parentDex = (index - 1)/2;
	//if the parent is 0 then just make it 1
	if(parentDex==0)
		parentDex = 1;
	//cout<<"parentDex "<<parentDex<<endl;
	//if its past he root
    if (parentDex >= ROOT) {
    	//if the current index's priority> parent's priority swap it  
        if (_heap.at(index).priority() > _heap.at(parentDex).priority()) { 
            swap(_heap.at(index), _heap.at(parentDex)); 
            // Recursively heapify the parent node 
            bottomHeapify(parentDex); 
        } 
    } 
}

template <class T>
T Heap<T>::readTop() const {
	return _heap.at(ROOT);
}

template <class T>
void Heap<T>::removeTop(){
	//make the root the bottom element 
	_heap.at(ROOT) = _heap.at(_heap.size() - 1);
	//pop the back and then top heapify
	_heap.pop_back();
	topHeapify(ROOT);
}

template <class T>
void Heap<T>::dump() const{
	for(int i=ROOT; i<=size();i++)
		cout<<_heap.at(i)<<endl;
}

template <class T>
void Heap<T>::topHeapify(int index){
	//since the root is 1 we gotta use different numbers
	int leftChild = 2*index;
	int rightChild = 2*index+1;
	int max = index;
	//check if the left child isnt out of index
	//cout<<"Left child "<<leftChild<<" rightChild "<<rightChild<<" Size "<< _heap.size()-1<<endl;
	if(leftChild <= _heap.size()-1){
		//cout<<"Left child in range"<<endl;
		//check if left child is greater than the root and assign if it is
		if(_heap.at(leftChild).priority()>_heap.at(index).priority())
			max = leftChild;
	}
	if(rightChild <= _heap.size()-1){
		//cout<<"Right child in range"<<endl;
		//check if right child is greater than the root and assign if it is
		if(_heap.at(rightChild).priority()>_heap.at(index).priority())
			max = rightChild;
	}
	//if the new max is not the index then swap them
	if(max!= index){
		swap(_heap.at(max),_heap.at(index));
		//top heapify using the max index
		topHeapify(max);
	}

}

// ***************************************
// Templated function definitions go here!
// ***************************************

#endif
