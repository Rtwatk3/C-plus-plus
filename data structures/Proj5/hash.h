// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator
/*****************************************
** 
** This file simulates a hHash table that uses linear probing.  
**
** 
***********************************************/
#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  
};
template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash){
  //Make all values what they should be
  _N = size;
  _n=0;
  _hash = hash;
  _table = new Heap<T> [size];
}

template <class T>
HashTable<T>::~HashTable(){
  //delete the table
	delete [] _table;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht){
  //make all values the the same as ht's
    _N = ht._N;
  	_hash = ht._hash;
	  _table = new Heap<T> [_N];
    //loop thru and make them the same
	  for(int i=0;i<_N;i++){
		  if(!(ht._table[i].empty()))
        _table[i] = ht._table[i];
	  }
}

template <class T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht){
  //same as copy but delete the current table and make it a new one
  	_N = ht._N;
  	_hash = ht._hash;
  	delete [] _table;
	_table = new Heap<T> [_N];
	for(int i=0;i<_N;i++){
		if(!(ht._table[i].empty()))
			_table[i] = ht._table[i];
	}
  //als, return this
	return *this;
}

template <class T>
bool HashTable<T>::insert(const T& object){
  //return false if it is full
  if(lambda() == 1 ){
    cout<<"Table full!"<<endl;
      return false;
  }

  int index;
  int counter = 0;
  //linear probing = has%size +counter until its available
  index = ((_hash(object.key()))%_N) + counter;
  while(index<_N){
    //if its not used then its also not empty so insert here
  	if(!(_table[index].used())){
  		_table[index].insert(object);
  		_n++;
  		return true;
  	}
    //if its used
    else if(_table[index].used()){
    	//if the current one is empty then insert
      if(_table[index].empty()){
        	_table[index].insert(object);
        	_n++;
        	return true;
      	}
      //if its not then check if its the same key
    	else if(object.key() == _table[index].readTop().key()){
    		_table[index].insert(object);
    		//_n++;
    		return true;
    	}
      	
    }
    counter++;
    index = ((_hash(object.key()))%_N) + counter;
  }
  return false;
}

template <class T>
bool HashTable<T>::getNext(string key, T& obj){
  //loop until you find the one you want
	for(int i = 0; i<_N;i++){
		if(!(_table[i].empty())){
			if(_table[i].readTop().key()==key){
				obj = _table[i].readTop();
				_table[i].removeTop();
				if(_table[i].empty()){
					_n--;
				}
				return true;
			}
		}
	}
  //if its not in there then return false
	return false;
}

template <class T>
void HashTable<T>::dump() const{
  for(int i=0; i<_N;i++){
  	cout<<"["<<i<<"]: "<<endl;
    if(_table[i].used())
      _table[i].dump();

  }
}
// *****************************************
// Templated function definitions go here! *
// *****************************************

#endif
