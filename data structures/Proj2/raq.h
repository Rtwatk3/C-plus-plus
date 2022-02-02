/*****************************************
** Header file for raq.cpp
** 
**
**  
***********************************************/
#ifndef _RAQ_H
#define _RAQ_H
#include <vector>
#include <array>
#include <iostream>
#include <math.h>

// RAQ Class implements the Dynamic Programming solution

class RAQ {
 public:
  
  // Create the RAQ object; perform precomputation
  RAQ(std::vector<float> data);

  // ******************************************************
  // **
  // ** IF NEEDED (depends on class variables),
  // **   constructor, destructor, assignment operator
  // **   go here
  // **
  // ******************************************************
  
  // Query the RAQ for interval [i, j]
  float query(int i, int j) const;
  
  // Dump the RAQ data structure to stdout
  void dump() const;
  
 private:
  float avg(int i, int j);
 	std::vector<float> m_data;
 	std::vector<std::vector<float>> m_preComp;

  // ******************************************************
  // **
  // **  Define the class variables here
  // **
  // ******************************************************

  // ******************************************************
  // **
  // ** Declare private helper functions here
  // **
  // ******************************************************  

};

// BlockRAQ class implements the Block Decomposition solution

class BlockRAQ {
public:
  // Create the BlockRAQ object; perform precomputation
  BlockRAQ(std::vector<float> data);

  // ******************************************************
  // **
  // ** IF NEEDED (depends on class variables),
  // **   constructor, destructor, assignment operator
  // **   go here
  // **
  // ******************************************************

  // Query the BlockRAQ for interval [i, j]
  float query(int i, int j) const;
  
  // Dump the BlockRAQ data structure to stdout
  void dump() const;
  
 private:
  std::vector<float> m_data;
  int m_leftovers;
  int m_blockNum;
  int m_blockCount;
  std::vector<float> m_blocks;

  // ******************************************************
  // **
  // **  Define the class variables here
  // **
  // ******************************************************

  // ******************************************************
  // **
  // ** Declare private helper functions here
  // **
  // ******************************************************  

};


#endif
