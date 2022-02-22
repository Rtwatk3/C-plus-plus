/*****************************************
** This project simulates a battle- OF HORSES
**
** 
***********************************************/
#include "Untrained.h"
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Untrained::Untrained(){}

  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Untrained::Untrained(string name, Size mySize, int health, int speed):Horse(name,mySize,health,speed){
  }


  // specialize() - if an horse successfully produces specializes it is replaced
  //           by a corresponding warhorse
  // Preconditions: all variables are set valid
  // Postconditions: returns an pointer to a new warhorse or NULL
  Horse* Untrained::specialize(){
    Horse* myHorse;
    Size size=getSize();
    int speed=getSpeed();
    string name=getName();
    int health=getHealth();
    //makes new horse depending on the size
    switch(size){
      case SMALL:
        myHorse= new Light(name,size,health,speed);
        break;
      case MEDIUM:
        myHorse= new Medium(name,size,health,speed);
        break;
      default:
        myHorse= new Heavy(name,size,health,speed);
        break;
    }
    return myHorse;
  }

  // train() : attempts to train an untrained horse
  // Preconditions: all variables are set valid
  // Postconditions: says that horses cannot be trained
  bool Untrained::train(){
    return false;
  }
  // toString() - a string representation of the untrained horse
  // Preconditions: all variables are set valid
  // Postconditions: returns an string describing the horse
  string Untrained::toString(){
    return "Unknown";
  }

  // attack(string, int) - only light, medium, and heavy can attack
  // Preconditions: target passed and health of attacker
  // Postconditions: displays that untrained horses can't attack
  int Untrained::attack(string targetName, int attackerHealth){
    //print that untrained warhorses cant attack
    cout<<"Untrained horses cannot attack"<<endl;
    return 0;
  }