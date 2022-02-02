//Description: This is the header file for the Untrained horses

#ifndef UNTRAINED_H
#define UNTRAINED_H

#include "Horse.h"
#include "Light.h"
#include "Medium.h"
#include "Heavy.h"

class Untrained: public Horse {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Untrained();

  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Untrained(string, Size, int, int);

  // specialize() - if an horse successfully produces specializes it is replaced
  //           by a corresponding warhorse
  // Preconditions: all variables are set valid
  // Postconditions: returns an pointer to a new warhorse or NULL
  Horse* specialize();

  // train() : attempts to train an untrained horse
  // Preconditions: all variables are set valid
  // Postconditions: says that horses cannot be trained
  bool train();

  // toString() - a string representation of the untrained horse
  // Preconditions: all variables are set valid
  // Postconditions: returns an string describing the horse
  string toString();

  // attack(string, int) - only light, medium, and heavy can attack
  // Preconditions: target passed and health of attacker
  // Postconditions: displays that untrained horses can't attack
  int attack(string, int );
};

#endif /* UNTRAINED_H */
