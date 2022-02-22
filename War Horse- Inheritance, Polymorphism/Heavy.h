//Description: This is the header file for the parent class Heavy
#ifndef HEAVY_H
#define HEAVY_H

#include "Warhorse.h"

class Heavy: public Warhorse {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Heavy();

  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Heavy(string, Size, int, int);
  
  // attack(string, int) - Returns amount of damage from attack
  // Damage is calculated as health/6 + training level (0-5)
  // Also, displays actual attack
  // Finally, the heavy warhorse calls kick from attack (special attack for heavy)
  // Preconditions: passed string name of target and attacker's health
  // Postconditions: returns damage as integer
  int attack(string, int);

  // toString() - a string representation of the child class
  // Preconditions: all variables are set valid
  // Postconditions: returns a string of the name of the subclass (return "Heavy")
  string toString();

  // kick() - a special attack by heavy warhorses
  // Preconditions: all variables are set valid
  // Postconditions: returns an int between 1 and 3 of additional damage
  int kick();
};

#endif /* HEAVY_H */
