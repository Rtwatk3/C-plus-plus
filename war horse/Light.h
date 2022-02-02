//Description: Header for Light, child of Warhorse, grandchild of Horse

#ifndef LIGHT_H
#define LIGHT_H

#include "Warhorse.h"

class Light: public Warhorse {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Light();

  // Overloaded Constructor
  // Preconditions: Valid inputs (name, align, size, health, speed)
  // Postconditions: None
  Light(string, Size, int, int);
  
  // attack(string, int) - Returns amount of damage from attack
  // Damage is calculated as health/6 + training level (0-5)
  // Also, displays actual attack
  // Preconditions: passed string name of target and attacker's health
  // Postconditions: returns damage as integer
  int attack(string, int);

  // toString() - a string representation of the child class
  // Preconditions: all variables are set valid
  // Postconditions: returns a string of the name of the subclass (return "Light")
  string toString();
};

#endif /* LIGHT_H */
