/*****************************************
** This project simulates a battle- OF HORSES
**
** 
***********************************************/
 #include "Heavy.h"
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Heavy::Heavy(){}

  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Heavy::Heavy(string name, Size mySize, int health, int speed):Warhorse(name,mySize,health,speed){

  }
  
  // attack(string, int) - Returns amount of damage from attack
  // Damage is calculated as health/6 + training level (0-5)
  // Also, displays actual attack
  // Finally, the heavy warhorse calls kick from attack (special attack for heavy)
  // Preconditions: passed string name of target and attacker's health
  // Postconditions: returns damage as integer
  int Heavy::attack(string targetName, int attackerHealth){
    //Prints enemy attack
    cout<<"The heavy warhorse "<<getName()<<" hits "<<targetName<<endl;
    //calcs damage
    int damage=(attackerHealth/6)+getTraining()+kick();
    return damage;
  }

  // toString() - a string representation of the child class
  // Preconditions: all variables are set valid
  // Postconditions: returns a string of the name of the subclass (return "Heavy")
  string Heavy::toString(){
    return "Heavy";
  }

  // kick() - a special attack by heavy warhorses
  // Preconditions: all variables are set valid
  // Postconditions: returns an int between 1 and 3 of additional damage
  int Heavy::kick(){
    //random damage
    srand(time(NULL));
    int damage = rand() % 3 + 1;
    cout<<"The heavy warhorse spins and kicks the enemy!"<<endl;
    return damage;
  }