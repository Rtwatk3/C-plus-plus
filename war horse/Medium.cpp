/*****************************************
** This project simulates a battle- OF HORSES
**
** 
***********************************************/
#include "Medium.h"

  Medium::Medium(){}

  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Medium::Medium(string name, Size mySize, int health, int speed):Warhorse(name,mySize,health,speed){

  }
  
  // attack(string, int) - Returns amount of damage from attack
  // Damage is calculated as health/6 + training level (0-5)
  // Also, displays actual attack
  // Preconditions: passed string name of target and attacker's health
  // Postconditions: returns damage as integer
  int Medium::attack(string targetName, int attackerHealth){
        //prints attack
    cout<<"The medium warhorse "<<getName()<<" hits "<<targetName<<endl;
    //calcs damage
    int damage=(attackerHealth/6)+getTraining();
    return damage;
  }

  // toString() - a string representation of the child class
  // Preconditions: all variables are set valid
  // Postconditions: returns a string of the name of the subclass (return "Medium")
  string Medium::toString(){return "Medium";}
