/*****************************************
** This project simulates a battle- OF HORSES
**
** 
***********************************************/
#include "Horse.h"
//enumerated type for size
  // Default Constructor
  // Preconditions: None
  // Postconditions: A horse is created
  Horse::Horse(){}

  //Use erase or create a temp vector when deleting a horse

  // Overloaded Constructor
  // Preconditions: Valid inputs (name, align, size, health, speed)
  //                Training always 0
  // Postconditions: None
  Horse::Horse(string name, Size horseSize, int health, int speed){
  	m_name=name;
  	m_size=horseSize;
  	m_health=health;
  	m_speed=speed;
    m_training=UNTRAINED;
  }
  
  // Destructor - virtual (implement in child classes)
  // Preconditions: Horse object in memory
  // Postconditions: Deallocates horse object in memory
  //Horse::~Horse(){}

  // getName() - returns the name of horse
  // Preconditions: m_name is set
  // Postconditions: returns a string name of the horse
  string Horse::getName(){
  	return m_name;
  }
  
  // getSize() - returns the size of horse
  // Preconditions: m_size is set
  // Postconditions: returns an enum Size referring to the size of the horse
  Size Horse::getSize(){
  	return m_size;
  }
 
  // getHealth() - returns the health of horse
  // Preconditions: m_health is set
  // Postconditions: returns an int referring to health from (1 - MAX_HEALTH)
  int Horse::getHealth(){
  	return m_health;
  }
  
  // getSpeed() - returns the speed of the horse
  // Preconditions: m_speed is set
  // Postconditions: returns an int referring to speed from (1 - MAX_SPEED)
  int Horse::getSpeed(){
  	return m_speed;
  }

  // getTraining() - returns the training level of horse
  // Preconditions: m_training is set
  // Postconditions: returns an enum Training referring to training level of the horse
  Training Horse::getTraining(){
  	return m_training;
  }
  
  // setHealth() - updates the health of the horse
  // Preconditions: m_health is set
  // Postconditions: updates m_health
  void Horse::setHealth(int health){
  	m_health=health;
  }
  
  // increaseTraining() - increase training by one, up to max
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool (true if increased, false if at max)
  bool Horse::increaseTraining(){
  	bool increased;
    //increases the training depending on what the current training is

  	switch(getTraining()){
  		case UNTRAINED:
  			m_training=SADDLE;
  			increased=true;
  			break;
  		case SADDLE:
  			m_training=GREEN;
  			increased=true;
  			break;
  		case GREEN:
  			m_training=INTERMEDIATE;
  			increased=true;
  			break;
  		case INTERMEDIATE:
  			m_training=EXPERT;
  			increased=true;
  			break;
  		case EXPERT:
  			m_training=MASTER;
  			increased=true;
  			break;
  		default:
  			increased=false;
  	   break;
  	}
    //only retuns false if it is maxed on training
  	return increased;
  }
  
  // specialize() - Attempts to converts an Untrained horse to
  //                a war horse (light, medium, or heavy)
  //                Only Untrained type of horses can be specialized
  // Preconditions: all variables are set valid
  // Postconlditions: returns a pointer to a new warhorse or NULL
  
  Horse* Horse::specialize(){
  }

  // battle() - Sends a horse to battle another horse
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether horse won the battle or not
  bool Horse::battle(Horse* otherHorse){
  return true;
  }
  
  // Overloaded << - Prints the details of a horse
  // Preconditions: all variables are set valid
  // Postconditions: returns an ostream with output of horse
  ostream& operator<<(ostream &output, Horse& thisHorse){
    //prints the horse out
  	output<<thisHorse.getName()<<"\t"<<thisHorse.toString()<<"\t"<<
  	thisHorse.getHealth()<<"\t"<<thisHorse.getSpeed()<<"\t"<<
  	thisHorse.trainingString(thisHorse.getTraining());
  	return output;
  }
  // randomPercentBased (Helper function)
  // Precondition: Given int to "pass"
  // Description: This function is used to see if a certain random event occurs
  //              A random number 1-100 is compared to the int passed
  //              If the random number is less than the passed value, return true
  //              Else return false (30 = 30%, 70 = 70%)
  // Postcondition: Returns boolean

  bool Horse::randomPercentBased(int chance){
  	bool pass;
    //gets a random number. If it is less, return true
  	srand(time(NULL));
  	int percent = rand() % 100 + 1;
  	if(chance<percent){
  		pass=false;
  	}
  	else{
  		pass=true;
  	}
  	return pass;
  }

  // trainingString() - a string representation of a training level enum
  // UNTRAINED = 0, SADDLE = 1, GREEN = 2, INTERMEDIATE = 3, EXPERT = 4, MASTER = 5
  // Preconditions: Pass a training level to the function
  // Postconditions: Returns the string of the enum
  string Horse::trainingString(Training horseLevel){
  	string level;
    //returns the horse training level as a string
  	switch(horseLevel){
  		case UNTRAINED:
  			level="Untrained";
  			break;
  		case SADDLE:
  			level="Saddle";
  			break;
  		case GREEN:
  			level="Green";
  			break;
  		case INTERMEDIATE:
  			level="Intermediate";
  			break;
  		case EXPERT:
  			level="Expert";
  			break;
  		default:
  			level="Master";
  	  
  }
  return level;
}