#include "BusCompany.h"

/*****************************************
** This file creates a new bus company and populates the bus company's routes.
** This also serves as a main menu
**
**
** 
***********************************************/

// Name: BusCompany (default constructor)
  // Preconditions: None
  // Postconditions: A new bus company is created.
  BusCompany::BusCompany(){

  }

  // Name: BusCompany (overloaded constructor)
  // Desc: Calls ReadFile and then MainMenu
  // Preconditions: Filename is included
  // Postconditions: A new bus company is created and routes are created from a passed file
  BusCompany::BusCompany(string fileName){ 
    ReadFile(fileName);
    int numRoutes=m_routes.size();
    for(int i=0; i<numRoutes;i++){
      //Grabs each route
      cout<<"Route "<<i+1<<" loaded with "<<m_routes.at(i)->GetSize()<<" stops."<<endl;
    }
    cout<<endl;
    cout<<"*********************************"<<endl;
    cout<<"Welcome to UMBC Transit Simulator"<<endl;
    MainMenu();
  }
  // Name:  BusCompany (destructor)
  // Preconditions: None
  // Postconditions: All linked lists are destroyed.
  BusCompany::~BusCompany(){
    int numRoutes=m_routes.size();
    for(int i=0; i<numRoutes;i++){
      delete m_routes.at(i);
    }

  }
  // Name:  readFile
  // Desc: Populates a vector of linked lists (m_routes of Routes)
  // Preconditions: Valid file name of routes
  // Postconditions: Creates one route as described (file may have multiple routes)
  void BusCompany::ReadFile(string fileName){
    ifstream myFile;
    myFile.open(fileName);
    string stopName;
    int location,riders;
    double cost;
    string whitespace;
    m_newRoute = new Route();
    //gets each line pto the comma
    while (getline(myFile,stopName,','))
    {
      //makes a new route if its end route.
      //pushes the current one to the vector
    	if(stopName=="End Route"){
        m_routes.push_back(m_newRoute);
        m_newRoute = new Route();
    	}
    	else{

    		//Need to use this to make a stop. gotta figure out how 
    		//route.h is included so just make a stop
    		//the vector is a vector of pointers so the stop needs to point to something else.
    		myFile>>location>>riders>>cost;
        getline(myFile,whitespace);
        //adds a stop
    		m_newRoute->InsertAt(stopName,location,riders,cost);
    	}
      
    }
    delete m_newRoute;
    myFile.close();
  }
  
  // Name:  mainMenu
  // Preconditions: None
  // Postconditions: None
  void BusCompany::MainMenu(){
    int choice;
    do{
      do{
        //makes the main menu
        cout<<"1. Display Routes"<<endl;
        cout<<"2. Display Earnings vs Expenses By Route"<<endl;
        cout<<"3. Optimize Route"<<endl;
        cout<<"4. Exit"<<endl;
        cin>>choice;
        //validation
    }while(choice>4||choice<1);
    //does thea function based on the choice
    switch (choice)
        {
        case 1: 
          DisplayRoutes();
          break;
        case 2:
          DisplayRouteData();
          break;
        case 3: 
          OptimizeRoute();
          break;
        default:
          cout<<"Thank you for using the UMBC Transit Simulator"<<endl;
          break;
      }
      //input validation
      }while(choice!=4);
        }
  
  // Name:  DisplayRoutes
  // Desc: Iterates over the vector and calls the overloaded << operator for each route
  // Preconditions: At least one route in m_routes;
  // Postconditions: Displays each route in m_routes
  void BusCompany::DisplayRoutes(){
    int numRoutes=m_routes.size();
    //prints the routes
    for(int i=0; i<numRoutes;i++){
      cout<<"*** Route "<<i+1<<" ***"<<endl;
      m_routes.at(i)->DisplayRoute();
    }
  }
  
  // Name:  OptimizeRoute
  // Desc: Goes through a specific route and removes profit losing stops (3.25 per rider)
  //       Profit is riders * fare per rider vs stop cost
  // Preconditions: Has route
  // Postconditions: Removes up to all stops in a route that lose money
  void BusCompany::OptimizeRoute(){
    int choice;
    int numRoutes=m_routes.size();
    if(numRoutes==1){
      m_routes.at(0)->OptimizeRoute(RIDER_FARE);
    }
    else{
        do{
          //optimize the first one if its only one route
          cout<<"Which route would you like to optimize?"<<endl;
          for(int i=0;i<numRoutes;i++){
            cout<<"Route "<<i+1<<endl;
          }
          cout<<"Enter 1 - "<<numRoutes<<" inclusive:"<<endl;
          cin>>choice;
          //validation
        }while(choice<1||choice>numRoutes);
        m_routes.at(choice-1)->OptimizeRoute(RIDER_FARE);
      }
  }

  // Name:  DisplayRouteData()
  // Desc: Displays total earnings and total expenses per route
  //       Displays earnings/expenses by individual stop by route
  // Preconditions: Has route
  // Postconditions: Displays route with stop data
  void BusCompany::DisplayRouteData(){
    int numRoutes=m_routes.size();
    //prints the route data
    for(int i=0; i<numRoutes;i++){
      cout<<"*** Route "<<i+1<<" ***"<<endl;
      m_routes.at(i)->DisplayStopData(RIDER_FARE);
    }
  }