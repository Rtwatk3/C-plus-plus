/*****************************************
** This project simulates a battle- OF HORSES
**
** 
***********************************************/
#include "War.h"
//Enum for main menu
enum tasks{FRIENDLY=1,ENEMY,ACQUIRE,TRAIN,BATTLE};
// Default Constructor
  // Preconditions: None
  // Postconditions: Seeds srand only
  War::War(){}

  // Destructor
  // Preconditions: m_myStable and/or m_enemyStable is populated
  // Postconditions: Deallocates horse objects in all vectors
  War::~War(){
    //deletes all of the horses in the enemy stable
    for (int i =0; i<(int)m_enemyStable.size();i++){
        delete m_enemyStable.at(i);
    }
    //deletes all horses in my stable
    for (int i =0; i<(int)m_myStable.size();i++){
        delete m_myStable.at(i);
    }
    
  }

  // Name: loadHorses
  // Desc - Loads each horse into m_enemyStable from file
  // Preconditions - Requires file with valid horse data
  // Postconditions - m_enemyStable is populated with enemy horse pointers
  void War::loadHorses(char* file){
    //opens file
    ifstream myFile;
    myFile.open(file);
    string name;
    int size,health,speed;
    //while i can still read in the name
    Horse* newHorse;
    while(myFile>>name){
      //read in size health and speed
      myFile>>size>>health>>speed;
      //seperates the horses
      if(size==SMALL){
        Horse* temp;
        newHorse =new Untrained(name,SMALL,health,speed);
        temp=newHorse;
        newHorse=newHorse->specialize();
        //pushes the horse back
        delete temp;
        m_enemyStable.push_back(newHorse);
      }
      else if(size==MEDIUM){
        Horse* temp;
        newHorse =new Untrained(name,MEDIUM,health,speed);
        temp=newHorse;
        newHorse=newHorse->specialize();
        //pushes the horse back
        delete temp;
        m_enemyStable.push_back(newHorse);
      }
      else{
        Horse* temp;
        newHorse =new Untrained(name,LARGE,health,speed);
        temp=newHorse;
        newHorse=newHorse->specialize();
        //pushes the horse back
        delete temp;
        m_enemyStable.push_back(newHorse);
      }
        
      }
      //closes file
      myFile.close();

    }
    

  // Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - m_enemyStable has been populated from file
  // Postconditions - exits if user entered 6
  void War::mainMenu(){
    cout<<"Welcome to UMBC War"<<endl;
    int choice;
    do{
      //prints the main menu
      cout<<"What would you like to do?"<<endl
          <<"1. Display Friendly Stable"<<endl
          <<"2. Display Enemy Stable"<<endl
          <<"3. Acquire Horse"<<endl
          <<"4. Train Horse"<<endl
          <<"5. Battle"<<endl
          <<"6. Quit"<<endl;
          cin>>choice;
        //input validation
      while(choice<1||choice>6){
        cout<<"Invalid choice"<<endl;
        cin>>choice;
      }
      //do the option
      switch (choice)
        {
        case FRIENDLY: 
          displayMyHorses();
          break;
        case ENEMY:
          displayEnemyHorses();
          break;
        case ACQUIRE: 
          acquireHorse();
          break;
        case TRAIN:
          trainHorse();
          break;
        case BATTLE:
          startBattle();
          break;
        default:
          cout<<"Thank you for playing!"<<endl;
          break;
      }
    }while(choice!=6 && (int)m_enemyStable.size()!=0);
    //congragulates the winner
    if(choice!=6)
      cout<<"Congrats! you win"<<endl;
  }

  // Name: acquireHorse()
  // Desc - user randomly acquires a new untrained horse (random size)
  // Preconditions - none
  // Postconditions - new horse is added to m_myStable
  void War::acquireHorse(){
    string horseName;
    cout<<"What would you like to name your horse?"<<endl;
    cin>>horseName;
    //Random size
    srand(time(NULL));
    int size;
    //0-2
    //random size
    size= (rand() % LT_MAX_SPEED + LT_MIN_SPEED-1);
    size--;
    int health,speed;
    //seperates the horses, same deal as load horses
    if(size==SMALL){
      //min+max-min+1
        speed=LT_MIN_SPEED+(rand() % (LT_MAX_SPEED-LT_MIN_SPEED+1)) ;
        health=LT_MIN_HEALTH+(rand() % (LT_MAX_HEALTH-LT_MIN_HEALTH+1)) ;
        Horse* newHorse =new Untrained(horseName,SMALL,health,speed);
        m_myStable.push_back(newHorse);
      }
      else if(size==MEDIUM){
        //min+max-min+1
        speed=MD_MIN_SPEED+(rand() % (MD_MAX_SPEED-MD_MIN_SPEED+1)) ;
        health=MD_MIN_HEALTH+(rand() % (MD_MAX_HEALTH-MD_MIN_HEALTH+1));
        Horse* newHorse =new Untrained(horseName,MEDIUM,health,speed);
        m_myStable.push_back(newHorse);
      }
      else{
        //min+max-min+1
        speed=HV_MIN_SPEED+(rand() % (HV_MAX_SPEED-HV_MIN_SPEED+1)) ;
        health=HV_MIN_HEALTH+(rand() % (HV_MAX_HEALTH-HV_MIN_HEALTH+1)) ;
        Horse* newHorse =new Untrained(horseName,LARGE,health,speed);
        m_myStable.push_back(newHorse);
      }
    cout<<"You have acquired a new horse"<<endl;
  }

  // Name: trainHorse()
  // Desc - user randomly acquires a horse
  // Preconditions - none
  // Postconditions - new horse is added to m_stable
  void War::trainHorse(){
    int whatHorse=chooseHorse();
    whatHorse--;
    if(whatHorse==-1){
      cout<<"No horse was trained"<<endl;
    }  
    else{
      Horse* thisHorse = m_myStable.at(whatHorse);
      //calls warhorse's train
      //try to train the horse
      if(m_myStable.at(whatHorse)->train()){
        //50% chance to increase training
        if(m_myStable.at(whatHorse)->increaseTraining()){
          cout<<"Horse successfully trained!"<<endl;
        }
        else{
          cout<<"Horse is at the max level."<<endl;
        }
      }
      //if the horse is untrained
      else if(thisHorse->toString()=="Unknown"){
       Horse* newHorse=thisHorse->specialize();
       m_myStable.at(whatHorse)=newHorse;
       //horse is no longer untrained
       cout<<"Your horse is now a "<<thisHorse->toString()<<" warhorse"<<endl;
      }
      else{
        cout<<"Training failed"<<endl;
      }
    }
  }

  // Name: startBattle()
  // Desc - user selects a horse to battle with and fights first horse in enemy
  // m_enemyStable. Horse that loses is removed from their respective stable forever
  // User must have at least ONE specialized horse at least training level 2 or higher
  // Preconditions - Use has at least one horse and horse is specialized trained
  // Postconditions - m_myStable or m_enemyStable has loser removed
  void War::startBattle(){
    vector<Horse*> temp;
    int choice=0;
    Horse* playerHorse;
    Horse* enemyHorse=m_enemyStable.at(choice);
    bool playerWin=false;
      choice=chooseHorse();
      choice--;
      //if there are no horses
      if(choice==-1){
        cout<<"cannot battle without a horse"<<endl;
      }
      else{
        //cannot battle untrained horse
        if(m_myStable.at(choice)->getTraining()==UNTRAINED){
          cout<<"That horse is not ready for battle yet"<<endl;
        }
        else{
          //sets horse variables
          playerHorse=m_myStable.at(choice);
          playerWin=playerHorse->battle(enemyHorse);
          if(playerWin==true){
            //enemy horse is dead
            cout<<"Enemy horse perished in the battle"<<endl;
            delete m_enemyStable.at(0);
            m_enemyStable.erase(m_enemyStable.begin());
          }
          else{
            //Kills my horse
          cout<<"Your horse perished in the battle"<<endl;
          delete m_myStable.at(choice);
          m_myStable.erase(m_myStable.begin()+choice);
          }
        }
    }
  }

  // Name: displayMyHorses()
  // Desc - Displays all horses in m_myStable or empty message if no horses
  // Preconditions - m_myStable is populated
  // Postconditions - None
  void War::displayMyHorses(){
    //no horses 
    if((int)m_myStable.size()==0){
      cout<<"You have no horses"<<endl;
    }
    else{
      //prints the horses
      cout<<"Your horses"<<endl;
      cout<<"Num"<<"\t"<<"Name"<<"\t"<<"Size"<<"\t"<<"Health"<<"\t"
      <<"Speed"<<"\t"<<"Training"<<endl;
      for (int i =0; i<(int)m_myStable.size();i++){
        cout<<i+1<<"\t"<<*m_myStable.at(i)<<endl;
      }
    }
  }

  // Name: displayEnemyHorses()
  // Desc - Displays all horses in m_enemyStable or win message if empty
  // Preconditions - m_enemyStable is populated
  // Postconditions - None
  void War::displayEnemyHorses(){
    if(m_enemyStable.size()==0){
      cout<<"Congrats you won!"<<endl;
    }
    //Prints enemy horses
    else{
      cout<<"Enemy horses"<<endl;
      cout<<"Num"<<"\t"<<"Name"<<"\t"<<"Size"<<"\t"<<"Health"<<"\t"
      <<"Speed"<<"\t"<<"Training"<<endl;
      for (int i =0; i<(int)m_enemyStable.size();i++){
        cout<<i+1<<"\t"<<*m_enemyStable.at(i)<<endl;
      }
    }

  }

  // Name: chooseHorse
  // Desc - Helper that either displays that m_myStable is empty or allows user to
  //        choose a horse to use for training or battle. Returns index + 1
  // Preconditions - None
  // Postconditions - None
  int War::chooseHorse(){
    int choice;
    //theres no horses
    if(m_myStable.size()==0){
      cout<<"You have no horses"<<endl;
      choice =0;
    }
    else{
      //Lets player choose a horse as long as it is in the bounds
      do {cout<<"Choose a horse:"<<endl;
      displayMyHorses();
      cin>>choice;
    }while(choice<0 || choice>(int)m_myStable.size());
  }
    return choice;
  }