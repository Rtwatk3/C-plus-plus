//Description: This is the header file for the parent class Horse

#ifndef HORSE_H
#define HORSE_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

//enumerated type for size
enum Size { SMALL, MEDIUM, LARGE};

//enumerated type for horse training level
enum Training {UNTRAINED, SADDLE, GREEN, INTERMEDIATE, EXPERT, MASTER};

//Constants
const int MAX_TRAINING = 5;
const int MAX_SIZE = 2;

class Horse {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: A horse is created
  Horse();

  // Overloaded Constructor
  // Preconditions: Valid inputs (name, align, size, health, speed)
  //                Training always 0
  // Postconditions: None
  Horse(string name, Size, int health, int speed);
  
  // Destructor - virtual (implement in child classes)
  // Preconditions: Horse object in memory
  // Postconditions: Deallocates horse object in memory
  virtual ~Horse(){};

  // getName() - returns the name of horse
  // Preconditions: m_name is set
  // Postconditions: returns a string name of the horse
  string getName();
  
  // getSize() - returns the size of horse
  // Preconditions: m_size is set
  // Postconditions: returns an enum Size referring to the size of the horse
  Size getSize();
  
  // getHealth() - returns the health of horse
  // Preconditions: m_health is set
  // Postconditions: returns an int referring to health from (1 - MAX_HEALTH)
  int getHealth();
  
  // getSpeed() - returns the speed of the horse
  // Preconditions: m_speed is set
  // Postconditions: returns an int referring to speed from (1 - MAX_SPEED)
  int getSpeed();

  // getTraining() - returns the training level of horse
  // Preconditions: m_training is set
  // Postconditions: returns an enum Training referring to training level of the horse
  Training getTraining();
  
  // setHealth() - updates the health of the horse
  // Preconditions: m_health is set
  // Postconditions: updates m_health
  void setHealth(int);
  
  // increaseTraining() - increase training by one, up to max
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool (true if increased, false if at max)
  bool increaseTraining();
  
  // specialize() - Attempts to converts an Untrained horse to
  //                a war horse (light, medium, or heavy)
  //                Only Untrained type of horses can be specialized
  // Preconditions: all variables are set valid
  // Postconditions: returns a pointer to a new warhorse or NULL
  virtual Horse* specialize();

  // attack(string, int) - Virtual function for light/medium/heavy to attack
  // Preconditions: all variables are set valid
  // Postconditions: Child class will return the number of points of damage
  virtual int attack(string, int)=0;
  
  // train() - Tests if horse was successfully trained
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether horse trained or not
  virtual bool train() = 0;

  // battle() - Sends a horse to battle another horse
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether horse won the battle or not
  virtual bool battle(Horse*);
  
  // Overloaded << - Prints the details of a horse
  // Preconditions: all variables are set valid
  // Postconditions: returns an ostream with output of horse
  friend ostream& operator<<(ostream&, Horse&);

  // randomPercentBased (Helper function)
  // Precondition: Given int to "pass"
  // Description: This function is used to see if a certain random event occurs
  //              A random number 1-100 is compared to the int passed
  //              If the random number is less than the passed value, return true
  //              Else return false (30 = 30%, 70 = 70%)
  // Postcondition: Returns boolean
  static bool randomPercentBased(int); 

  // toString() - a string representation of the horse
  // Preconditions: all variables are set valid
  // Postconditions: returns an string describing the horse
  virtual string toString() = 0;

protected:
  // trainingString() - a string representation of a training level enum
  // UNTRAINED = 0, SADDLE = 1, GREEN = 2, INTERMEDIATE = 3, EXPERT = 4, MASTER = 5
  // Preconditions: Pass a training level to the function
  // Postconditions: Returns the string of the enum
  string trainingString(Training);
private:
  string m_name;        //Horse's name
  Size m_size;          //SMALL, MEDIUM, LARGE, HUGE
  int m_health; 	//MIN_HEALTH to MAX_HEALTH - Higher is better and 0 is dead
  int m_speed;		//MIN_SPEED to MAX_SPEED - Lower is better (1 would be best)
  Training m_training;  //UNTRAINED, SADDLE, GREEN, INTERMEDIATE, EXPERT, MASTER
};

#endif /* HORSE_H */


