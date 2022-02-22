/*****************************************
** This is the code for the Alchemist.cpp file
** for The Alchemist game. It is 
** pretty much the backbone of the code
**
***********************************************/

#include "Alchemist.h" //Include for the element struct

  // Name: Alchemist() - Default Constructor
  // Desc: Used to build a new Alchemist object
  // Preconditions - Requires default values
  // Postconditions - Creates a new Alchemist
    Alchemist::Alchemist(){}


  // Name: Alchemist(name) - Overloaded constructor
  // Desc - Used to build a new Alchemist
  // Preconditions - Requires name
  // Postconditions - Creates a new Alchemist
  Alchemist::Alchemist(string name){
      m_myName=name;
      m_attempts=0;
      m_repeats=0;
      m_numElements=0;
    }


  // Name: GetName()
  // Desc - Getter for Alchemist name
  // Preconditions - Alchemist exists
  // Postconditions - Returns the name of the Alchemist
  string Alchemist::GetName(){
    return m_myName;
  }
  // Name: SetName(string)
  // Desc - Allows the user to change the name of the Alchemist
  // Preconditions - Alchemist exists
  // Postconditions - Sets name of Alchemist
  void Alchemist::SetName(string name){
    m_myName=name;
  }
  // Name: DisplayElements()
  // Desc - Displays a numbered list of all elements known by the Alchemist
  // Preconditions - Alchemist exist
  // Postconditions - None
  void Alchemist::DisplayElements(){
    int numElements=GetNumElements();
    Element currElement;
    //prints the elements in myElements
    for(int i=0;i<numElements;i++){
      currElement=m_myElements[i];
      cout<<i+1<<". "<<currElement.m_name<<endl;
    }
  }


  // Name: GetNumElements()
  // Desc - Returns number of elements known by the Alchemist
  // Preconditions - Alchemist exists
  // Postconditions - None
  int Alchemist::GetNumElements(){
    return m_numElements;
  }
  // Name: CheckElement(Element)
  // Desc - Checks to see if the Alchemist has an element
  // Preconditions - Alchemist already has elements
  // Postconditions - Returns true if Alchemist has element else false
  bool Alchemist::CheckElement(Element newEl){
    int numElements=GetNumElements();
    Element currElement;
    string currName=currElement.m_name;
    string newName=newEl.m_name;
    bool hasElement=false;
    //Checks if the element alreadt exists. If it does hasElements is changeds to true and it cannot be changed back
    //Adds a repeat if it was already made
    for(int i=0;i<numElements;i++){
      currElement=m_myElements[i];
      currName=currElement.m_name;
      if(newName==currName){
        hasElement=true;
        AddRepeat();
      }
    }
    return hasElement;
  }


  // Name: AddElement(Element)
  // Desc - Adds element to m_myElements if not known increases numElements
  // Preconditions - Alchemist exists and new element not already known
  // Postconditions - Adds element to m_myElements
  void Alchemist::AddElement(Element newElement){
    //dont add attempts if the user has less than 4 elements (Fire water earth air)
    if(m_numElements>4){
      AddAttempt();
    }
    m_myElements[m_numElements]=newElement;
    
    m_numElements++;
    }


  // Name: GetElement(int)
  // Desc - Checks to see if the alchemist has an element
  // Preconditions - Alchemist already has elements
  // Postconditions - Returns element at index
  Element Alchemist::GetElement(int elementNum){
    return m_myElements[elementNum];
  }
  // Name: AddAttempt
  // Desc - Increments attempts
  // Preconditions - Alchemist attempts a merge
  // Postconditions - Increments every time a merge is attempted
  void Alchemist::AddAttempt(){
    m_attempts++;
  }
  
  // Name: GetAttempts()
  // Desc - Returns number of attempts for that Alchemist
  // Preconditions - Alchemist exists
  // Postconditions - Returns total number of attempts
  int Alchemist::GetAttempts(){
    return m_attempts;
  }

  // Name: AddRepeat()
  // Desc - Increments repeats for every time an element has already been found
  // Preconditions - Alchemist attempts a merge
  // Postconditions - Increments every time a merge yields an element already found
  void Alchemist::AddRepeat(){
    m_repeats++;
  }
  

  // Name: GetRepeats()
  // Desc - Returns number of repeats for that Alchemist
  // Preconditions - Alchemist exists
  // Postconditions - Returns total number of repeats
  int Alchemist::GetRepeats(){
    return m_repeats;
  }