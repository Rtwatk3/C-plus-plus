/*****************************************
** This project tests Destructors, 
** copy constructors and assignment opperators.  
**
** 
***********************************************/

#include <iostream>
#include <stdexcept>
#include "my_array.h"

using namespace std;
//Destructor
my_array::~my_array(){
	delete [] m_data;
}

// Copy constructor
my_array::my_array( const my_array& arr ){
	m_size = arr.m_size;
	m_data = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		m_data[i] = arr.m_data[i];
	}
}

// Default constructor (size has default value of 1; see .h file)
my_array::my_array( unsigned int size ) {
  if (size < 1) {
    throw range_error("my_array(): array must have at least one element");
  }
  m_data = new int[size];
  m_size = size;
}

// Assignment operator
my_array& my_array::operator=( const my_array& arr ){
	delete [] m_data;
	m_size = arr.m_size;
	m_data = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		m_data[i] = arr.m_data[i];
	}
	return *this;
}

my_array::my_array(int* data, int len) {

  // if data array is empty, throw range_error exception
  if ( len < 1 ) {
    throw range_error("my_array(): input data must have at least one element");
  }

  m_data = new int[len];
  m_size = len;
  
  // copy data to m_data
  for (int i = 0; i < len; i++) {
    m_data[i] = data[i];
  }
}

int my_array::size() const { return m_size; }

int& my_array::at(unsigned int indx) {
  if (indx >= m_size) {
    throw range_error("at(): index is out-of-range");
  }
  return m_data[indx];
}

