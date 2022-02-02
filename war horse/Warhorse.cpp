/*****************************************
** This project simulates a battle- OF HORSES
**
** 
***********************************************/
#include "Warhorse.h"
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Warhorse::Warhorse(){}
  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Warhorse::Warhorse(string name, Size mySize, int health, int speed):Horse(name,mySize,health,speed){
  }
  // train() - Gives a 50% of increasing training up to maximum.
  // Preconditions: all variables are set valid
  // Postconditions: returns true if successfully trained
  bool Warhorse::train(){
    int chance=50;
    //calculates random percent
    bool doTrain=randomPercentBased(chance);
    return doTrain;
  }
  
  // battle(Horse*) - passed enemy horse
  // turns are based on speed - counter starts at 0 and if counter % speed == 0 then
  // that horse attacks counter%getSpeed()==0, attacks. If attack leaves at or below 0
  // then that horse loses battle.
  // Preconditions: enemy horse has been defined
  // Postconditions: returns a bool of who won battle between two horses
  bool Warhorse::battle(Horse* enemy){
    bool playerWin=false;
    int playerHeath=getHealth();
    int counter=0;
    //get player and enemy health
    int enemyHeatlh=enemy->getHealth();
    enemyHeatlh-=attack(enemy->getName(),enemy->getHealth());
    //while the player and enemy healths are above 0
    do{
      //make player attack if the counter % speed is 0
      if(counter%getSpeed()==0){
        enemyHeatlh-=attack(enemy->getName(),enemy->getHealth());
      }
      //make enemy attack if the counter % speed is 0
      else if(counter%enemy->getSpeed()==0){
        playerHeath=enemy->attack(getName(),getHealth());
      }
      //set healths
      setHealth(playerHeath);
      enemy->setHealth(enemyHeatlh);
      counter++;
    }while(playerHeath>0&&enemyHeatlh>0);
    if(playerHeath==0){
      playerWin=false;
    }
    else{
      playerWin=true;
    }
    return playerWin;
  }