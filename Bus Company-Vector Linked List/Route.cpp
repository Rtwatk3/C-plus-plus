/*****************************************
** This file reads creates a route and populates the linked list.
** it also adds and deletes nodes.
** 
***********************************************/

#include "Route.h"

// Name: Route() - Default Constructor
  // Desc: Used to build a new bus route (which is a linked list)
  // Preconditions: None
  // Postconditions: Creates a new bus route where m_start and m_end point to NULL
  Route::Route(){
  	m_start=NULL;//head
  	m_size=0;

  	}
  // Name: ~Route() - Destructor
  // Desc: Used to destruct a route (which is a linked list)
  // Preconditions: There is an existing route with at least one stop
  // Postconditions: A route is deallocated (including all dynamically allocated stops)
  //                 to have no memory leaks!
 Route::~Route(){
    Clear();

		}
  // Name: InsertAt
  // Preconditions: Takes in a name, location, number of riders,
  //                and a cost (in dollars).
  //                Creates new stop.
  //                Inserts each Stop based on their integer location.
  //                Requires a route.
  // Postconditions: Adds a new stop to the route at a unique location.
  void Route::InsertAt(string name, int location, int riders, double cost){
    bool test=IsEmpty();
    Stop *temp = new Stop(name,location,riders,cost);
    Stop *previous;
    Stop *current;
    //empty list
    //insert at head
    if(test){
      m_start = temp;
    }
    else{
      //insert after head
      //insert at the end
      current=m_start;
      previous=nullptr;
      while(current!=nullptr && current->m_location<location){
            previous=current;
            current=current->m_next;
      }
      //insert at the head
      if(current==m_start){
        temp->m_next=m_start;
        m_start=temp;
      }
      //insert between the head and the end
      else{
        temp->m_next=current;
        previous->m_next=temp;
      }
      //insert at end?
    }
        m_size++;
}
 
  // Name: DisplayRoute
  // Preconditions: Outputs the route.
  // Postconditions: Returns a numbered list of all stops on a route.
  void Route::DisplayRoute(){
    if(IsEmpty()){
    cout << "There are no stops on this route." << endl;
  }else{
      Stop *currStop = m_start;
    for(int i = 0; i < m_size; i++){
      cout<< "Stop "<<i+1<<" - "<<currStop->m_name<<" ("<<currStop->m_location<<")"<<endl;
      currStop = currStop->m_next;
    }
    cout << "END" << endl;
      }
  }
  
  
  // Name: IsEmpty
  // Preconditions: Requires a route
  // Postconditions: Returns if the route is empty.
  bool Route::IsEmpty(){
    bool empty=false;
    if(m_start==nullptr){
      empty=true;
    }
    
    return empty;
  }
  // Name: GetRouteEarnings
  // Preconditions: Requires a bus route
  // Postconditions: Iterates over complete route and sums total earnings per month
  //                 Fare per rider * riders per stop (Fare is a constant in BusCompany.h)
  double Route::GetRouteEarnings(double riderFare){
   double total=0.0,earnings;
   Stop *currStop = m_start;
   for(int i = 0; i < m_size; i++){
      total+=currStop->m_riders;
      currStop = currStop->m_next;
    }
    earnings=total*riderFare;
    return earnings;
  }
  // Name: GetRouteExpenses
  // Preconditions: Requires a Bus Route
  // Postconditions: Iterates over route and sums total cost per station per month
  double Route::GetRouteExpenses(){
    double total=0.0;
    Stop *currStop = m_start;
    //iterateds through the list and adds to the total
    for(int i = 0; i < m_size; i++){
      total+=currStop->m_cost;
      currStop = currStop->m_next;
    }
    return total;
  }
  // Name: Clear
  // Preconditi cons: Requires a route
  // Postconditions: Removes all stops in a route
  void Route::Clear(){
    Stop *currStop = m_start; 
    Stop * temp; 

    while(currStop !=nullptr){
      temp=currStop->m_next;
      delete currStop;
      currStop = temp;
    }
    m_start = nullptr;
    }

  // Name: OptimizeRoute
  // Desc: Iterates over a bus route. If a specfic stop earns less than it's cost, it is removed
  //       from the route by calling RemoveStop.
  //       Earning = fare * number of riders and cost = m_cost
  // Preconditions: Requires a Bus Route
  // Postconditions:  Removes stops where (fare * riders) < monthly cost for station
  void Route::OptimizeRoute(double riderFare){
    
    int counter=1;
    
    double total;
    //for loop that runs until cyurrent is nullptr
    for (Stop *current = m_start; current != nullptr; current = current->m_next){

      total = riderFare * current->m_riders;
      //if statement works
      if(total < current->m_cost){
        cout << "removed " << current->m_name << " " << counter << endl;
        RemoveStop(counter);
        //counter=1;
        //current=m_start;
      }
      else{
   counter++;
   //current=current->m_next;
    }

    //current = nullptr; 

  }
      }
  // Name: RemoveStop
  // Preconditions: Requires a Bus Route
  // Postconditions: Removes a specific bus stop
  void Route::RemoveStop(int stopLocation){
    //to delete, link n's pointer to what m_next is pointing to and then delete the one you removed
    //delete the end is in the linked 2.cpp
    bool test=IsEmpty();
    Stop *previous;
    Stop *current;
    int counter=1;
    //empty list
    /*      Note to self,                   *
    *       STOP TOUCHING THIS FUNCTION     *
    *     -From me :)                       */
    if(test){
      cout<<"List empty"<<endl;
    }
    else{
    current=m_start;
    previous=nullptr;
    //while loop ends when we are at the end or we are at the spot
    while(current!=nullptr && counter!=stopLocation){
      previous=current;
      current=current->m_next;
      counter++;
    }
    //traversed through the whole list and its not there
    if(current==nullptr){
      cout<<"No pointer"<<endl;
    } 
    if(m_size==1){
      delete m_start;
      m_start=nullptr;
    }
    //delete the head
    else if(current==m_start){
      m_start=m_start->m_next;
      delete current;
    }
    //its anyehere else
    else{
      previous->m_next=current->m_next; 
      delete current;
    }
    

    m_size--;
    }
  }

  // Name: GetStopData
  // Desc: Displays name, earnings and expenses for stop
  // Preconditions: Requires a bus route passed riderFare (from constant in BusCompany.h)
  // Postconditions: None
  void Route::DisplayStopData(double riderFare){
    Stop *currStop = m_start;
    double earnings=GetRouteEarnings(riderFare);
    double expenses=GetRouteExpenses();
    cout<<"Earnings: "<<earnings<<endl;
    cout<<"Expenses: "<<expenses<<endl;
    //iterates through the list and prints the earnings and expenses
    for(int i = 0; i < m_size; i++){
      cout<<currStop->m_name<<endl;
      earnings=riderFare*currStop->m_riders;
      cout<<"Earnings: "<<currStop->m_riders<<"@$"<<riderFare<<" = $"<<earnings<<endl;
      expenses=currStop->m_cost;
      cout<<"Expenses: $"<<expenses<<endl;
      cout<<"Total: $"<<earnings-expenses<<endl;
      currStop = currStop->m_next;
      cout<<endl;
    }
  }
  // Name: GetSize
  // Precondition: Requires a bus route
  // Postcondition: Returns the number of stops in the route as an integer
  int Route::GetSize(){
    return m_size;
  }

  ostream &operator<<(ostream &output, Route &myRoute){
    if(myRoute.IsEmpty()){
    output << "There are no stops on this route." << endl;
  }else{
      Stop *currStop = myRoute.m_start;
    for(int i = 0; i < myRoute.m_size; i++){
      output<< "Stop "<<i+1<<" - "<<currStop->m_name<<" ("<<currStop->m_location<<")"<<endl;
      currStop = currStop->m_next;
    }
    output<< "END" << endl;
      }
      return output;
  }