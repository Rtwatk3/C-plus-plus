/*****************************************
** File:    light.cpp
** Project: CMSC 202 Project 4, Spring 2019
** Author:  Ryan Watkins
** Date:    4/18/19
** Section: 21
** E-mail:  ryanw3@umbc.edu 
** 
** This project simulates a battle- OF HORSES
**
** 
***********************************************/
#include "Light.h"

  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Light::Light(){}

  // Overloaded Constructor
  // Preconditions: Valid inputs (name, align, size, health, speed)
  // Postconditions: None
  Light::Light(string name, Size mySize, int health, int speed):Warhorse(name,mySize,health,speed){

  }
  
  // attack(string, int) - Returns amount of damage from attack
  // Damage is calculated as health/6 + training level (0-5)
  // Also, displays actual attack
  // Preconditions: passed string name of target and attacker's health
  // Postconditions: returns damage as integer
  int Light::attack(string targetName, int attackerHealth){
    //prints attack
    cout<<"The light warhorse "<<getName()<<" hits "<<targetName<<endl;
    //calcs damage
    int damage=(attackerHealth/6)+getTraining();
    return damage;  }

  // toString() - a string representation of the child class
  // Preconditions: all variables are set valid
  // Postconditions: returns a string of the name of the subclass (return "Light")
  string Light::toString(){
    return "Light";
  }