/*****************************************
** This project is the code for the game.cpp file
** for The Alchemist game. It is 
** the code that allows the game to run
***********************************************/
#include "Game.h"
//Constants
  const int HUNDO = 100;
  const int FOUR =4;
  const int ONE = 1;
  const int NEGONE=-1;
  int validateInput(int max, int min, int choice, int exceptipon=1);
  /* Name: Game() Default Constructor
  // Desc - Builds a new game by: 
  // 1. Loads all Alchemy recipes into m_elements (by making elements)
  // 2. Asks user for their alchemist's name (store in m_myAlchemist as m_myName)
  // 3. Adds fire, water, air, and earth to m_myElements (in m_myAlchemist)
  // Preconditions - None
  // Postconditions - m_elements is populated
  */ 
  
  Game::Game(){
  	GameTitle();
    LoadElements();
    Element air,water,fire,earth;
    //For loop to make Make the 4 base elements and then add them to m_myAlchemist
    for(int i=0; i<PROJ2_SIZE;i++){

      Element currElement=m_elements[i];
      if(currElement.m_name=="Air"){
        air= m_elements[i];
        m_myAlchemist.AddElement(air);}
      else if(currElement.m_name=="Earth"){
      	earth=m_elements[i];
      	m_myAlchemist.AddElement(earth);
      }
      else if(currElement.m_name=="Fire"){
      	fire=m_elements[i];
      	m_myAlchemist.AddElement(fire);
      }
      else if(currElement.m_name=="Water"){
        water=m_elements[i];
        m_myAlchemist.AddElement(water);
      }
    }
    //Set the alchemist name
    string alchemistName;
    cout<<"What is the name of the Alchemist?"<<endl;
    getline(cin,alchemistName);
    m_myAlchemist.SetName(alchemistName);
  } //Default Constructor

  //Input validator
  int validateInput(int max, int min, int choice, int exceptipon){
    if(exceptipon ==ONE){
      while(choice>max || choice<min){
      cout<<"Please enter a valid choice"<<endl;
      cin>>choice;
    }
    }
    else{
      while((choice<min && choice!=exceptipon)||choice>max){
      cout<<"Invalid choice, please enter another."<<endl;
      cin>>choice;
    }
    }
    return choice;
  }



  // Name: LoadElements
  // Desc - Loads each element into m_elements from file
  // Preconditions - Requires file with valid element data
  // Postconditions - m_elements is populated with element structs
  void Game::LoadElements(){
    ifstream myFile;
    myFile.open(PROJ2_DATA);
    string fileName,fileEl1,fileEl2;
    //Since theres only 390 elements, we only need to read 390 lines.
    //For loop for 390 lines
    //Name ',' element1 ',' element2 '/n'
    for (int i=0;i<PROJ2_SIZE;i++){
      getline(myFile,fileName,',');
      getline(myFile,fileEl1,',');
      getline(myFile,fileEl2,'\n');
      Element myElement(fileName,fileEl1,fileEl2);
      m_elements[i]=myElement;
    }
    cout<<"Loaded "<<PROJ2_SIZE<<" elements."<<endl;
    myFile.close();


  }


  // Name: StartGame()
  // Desc - Manages the game itself including win conditions continually
  //         calling the main menu 
  // Preconditions - Player is placed in game
  // Postconditions - Continually checks to see if player has entered 5
  void Game::StartGame(){
    int choice=MainMenu();
    
    int myElementNumber=m_myAlchemist.GetNumElements();
    //While 4 is not entered and the max has not been made
    while(choice!=FOUR && myElementNumber<PROJ2_SIZE){
      if(choice==ONE)
        DisplayElements();
      else if(choice==2)
        CombineElements();
      else if(choice==3)
        CalcScore();
      choice=MainMenu(); //validate input
      myElementNumber=m_myAlchemist.GetNumElements();
    }
    cout<<"Thanks for playing the Alchemist"<<endl;
    if(myElementNumber==PROJ2_SIZE){
    	cout<<"Congrats! You have created all the elements!"<<endl;
    }
  }


  // Name: DisplayMyElements()
  // Desc - Displays the current elements
  // Preconditions - Player has elements
  // Postconditions - Displays a numbered list of elements
  void Game::DisplayElements(){
    cout<<"Current Elements: "<<endl;
    //Just call the DisplayElements in Alchemist
    m_myAlchemist.DisplayElements();
    cout<<endl;
  }
  // Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - Player has an Alchemist
  // Postconditions - Returns number including exit
  int Game::MainMenu(){
    int choice;
    //Print those instructions!
    cout<<"What would like to do?"<<endl;
    cout<<"1. Display the Alchemist's Elements"<<endl;
    cout<<"2. Attempt to Merge Elements"<<endl;
    cout<<"3. See Score."<<endl;
    cout<<"4. Quit"<<endl;
    cin>>choice;
    //Validate it!
    choice=validateInput(FOUR, ONE,choice);
    //Return it B)
    return choice;
  }
  
  // Name: CombineElements()
  // Desc - Attempts to combine known elements
  // Preconditions - Alchemist is populated with elements
  // Postconditions - May add element to Alchemist's list of elements
  void Game::CombineElements(){
  	//Big function oof

    int index1=0,index2=0;
    //Request elements has a pass by reference parameter so the index changes without a return
    RequestElement(index1);
    RequestElement(index2);
    //Make element objects using ^ those indexes
    Element element1=m_myAlchemist.GetElement(index1-1);
    Element element2=m_myAlchemist.GetElement(index2-1);
    //Makes a new element creation, (used later)
   	Element creation;
   	//Self explanitory
    string elementName1=element1.m_name;
    string elementName2=element2.m_name;
    //Set the index of the of the element whose recipie is elementName1 & elementName2
    int index=SearchRecipes(elementName1, elementName2);
    m_myAlchemist.AddAttempt();

    bool hasElement;
    //Index can be -1. If it isnt then add the element. If it is dont add anything bc the element doesnt exist
    if(index!=-1){
    	creation=m_elements[index];
      hasElement=m_myAlchemist.CheckElement(creation);
      //Check if player already made the element
      if(!hasElement){
        cout<<elementName1<<" has combined with "<<elementName2<<" to combine "<<creation.m_name<<"!"<<endl;
        m_myAlchemist.AddElement(creation);
      }
    }
    else{
        cout<<"Nothing happened when you tried to combine "<<elementName1<<" and "<<elementName2<<"."<<endl;
      }
  }

  // Name: RequestElement()
  // Desc - Requests element to use to merge
  // Preconditions - Alchemist has elements to try and merge
  // Postconditions - Returns int index of matching recipe
  void Game::RequestElement(int &choice){
    int max=m_myAlchemist.GetNumElements();
    
    cout<<"Which elements would you like to merge?"<<endl;
    cout<<"To list known elements enter -1"<<endl;
    cin>>choice;
    //validate choice
    choice=validateInput(max, ONE,choice,NEGONE);
    //print the elements and instructions while the choice is negative one
    while(choice==NEGONE){
      DisplayElements();
      cout<<"Which elements would you like to merge?"<<endl;
      cout<<"To list known elements enter -1"<<endl;
      cin>>choice;
      choice=validateInput(max, ONE,choice,NEGONE);
    }
}

  // Name: SearchRecipes()
  // Desc - Searches recipes for two strings
  // Preconditions - m_elements is populated
  // Postconditions - Returns int index of matching recipe
  int Game::SearchRecipes(string el1, string el2){
  	Element currElement;
  	string recipe1,recipe2;
  	int index=-1;
  	//For loop to check the recipies of each index of the big array. Returns -1 if the recipie does not exist
  	for(int i=0;i<PROJ2_SIZE;i++){
  		currElement=m_elements[i];
  		recipe1=currElement.m_element1;
  		recipe2=currElement.m_element2;
  		//Check for both cases of the recipie
  		if(((el1==recipe1 && el2==recipe2)||(el2==recipe1 && el1==recipe2))&&index==NEGONE){
  			index=i;
  		}
  	}
    return index;
	}

  // Name: CalcScore()
  // Desc - Displays current score for Alchemist
  // Preconditions - Alchemist is populated with elements
  // Postconditions - None
  void Game::CalcScore(){
  	//Gets values for the big print out statement
    string myName=m_myAlchemist.GetName();
    int myTotal=m_myAlchemist.GetNumElements();
    double percent=myTotal/(double)PROJ2_SIZE;
    percent*=HUNDO;
    //for precision
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    //Big Ol' cout statement
    cout<<myName<<endl<<
    "The Great Alchemist "<<myName<<endl<<
    myName<< " has tried to combine "<< m_myAlchemist.GetAttempts()<<" elements."<<endl<<
    myName<< " has repeated attempts "<< m_myAlchemist.GetRepeats()<<" times."<<endl<<
    myName<< " has found "<<myTotal<<" out of "<<PROJ2_SIZE<<" elements."<<endl<<
    myName<< " You have completed "<<percent<<" % "<< "of the elements."<<endl;
  }