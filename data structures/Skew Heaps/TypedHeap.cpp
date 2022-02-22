/*****************************************
** This project simulates a TypedHeap and Balances 
** A string heap, int heap and a merge of both  
**
** 
***********************************************/
#include "TypedHeap.h"

  // Provide a vector of strings.  For each string, determine whether
  // it represents an integer; if so, insert it into the integer skew
  // heap.  Otherwise, insert it into the string skew heap.
  void TypedHeap::insertToHeaps(vector<string> vec){
    bool isString = false;
    char character;
    string newString;
    int newnum;
    for(int i=0; i<vec.size();i++){
      for(int x=0;x<vec.at(i).size();x++){
        character = vec.at(i).at(x);
        //check if a number
        if(character=='1'||
           character=='2'||
           character=='3'||
           character=='4'||
           character=='5'||
           character=='6'||
           character=='7'||
           character=='8'||
           character=='9'||
           character=='0'){}
        else{
          isString = true;
        }
      }
      //make a string node
      if(isString)
        stringHeap.insert(vec.at(i));
      else{
        //make an int node
        newString =vec.at(i);
        newnum = stoi(newString);
        cout<<newnum<<endl;
        intHeap.insert(stoi(vec.at(i)));
      }
      isString= false;
      //cout<<vec.at(i)<<endl;
    }
  }

  // Merge the integer and string heaps; save in totalHeap.
  void TypedHeap::combineHeaps(){
    totalHeap.skewHeapMerge(intHeap);
    totalHeap.skewHeapMerge(stringHeap);
  }

  // Print all three heaps (integer, string, total).
  void TypedHeap::printHeaps() const{
    cout<<"int heap holds:"<<endl;
    intHeap.dump();
    cout<<"string heap holds:"<<endl;
    stringHeap.dump();
    cout<<"total heap holds:"<<endl;
    totalHeap.dump();
  }

  // Change the priority function.
  void TypedHeap::changePriority(pri_fn pri){
    intHeap.setPriFn(pri);
    stringHeap.setPriFn(pri);
    totalHeap.setPriFn(pri);
  }