#include "Lqueue.h"
// g++ -Wall Lqueue.cpp -o lque

  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  
template <class T> 
Lqueue(){
	m_head=nullptr;
	m_tail=nullptr;
}
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 template <class T> 
Lqueue<T>::~Lqueue(){
  Clear();
 }
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  template <class T> 
	Lqueue<T>::Lqueue(const Lqueue& copyLqueue){
		m_head=nullptr;
		Node<T>* currNode= copyLqueue.m_head;		
		T data;
		while(currNode!=nullptr){
			data=currNode->GetData();
			Push(data,true);
			m_size++;
			currNode=currNode->GetNext();
		}
	}
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  
  template <class T> 
  Lqueue<T>& Lqueue<T>::operator=(const Lqueue& copyLqueue){
    m_head=nullptr;
    Node<T>* currNode= copyLqueue.m_head;   
    T data;
    while(currNode!=nullptr){
      data=currNode->GetData();
      Push(data,true);
      m_size++;
      currNode=currNode->GetNext();
    }
    return *this;
  }
  
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: If the bool = true, adds to front else adds a new node to the
  //                 end of the lqueue.
  template <class T> 
  void Lqueue<T>::Push(const T& data, bool ifFront){
    Node<T>* newNode = new Node<T>(data);
    Node<T>* tempNode;//=m_head->GetNext();
    if(m_head==nullptr){
    		m_head=newNode;
    		m_head->SetNext(nullptr);
    		m_size=1;
        m_tail=newNode;
    	}
    else if(ifFront){
      tempNode=m_head;
        while(tempNode->GetNext()!=nullptr){
          tempNode=tempNode->GetNext();         
        }
        tempNode->SetNext(newNode);
        m_tail=newNode;
  	}
    else{
    	tempNode=m_head;
      m_head=newNode;
      m_head->SetNext(tempNode);
    }
    m_size++;
  }
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  template <class T>
  T Lqueue<T>::Pop(){
    T data=m_head->GetData();
    Node<T>* deleteThis=m_head;
    m_head=m_head->GetNext();
    delete deleteThis;
    deleteThis=nullptr;
    return data;
    m_size--;
  }
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  template <class T>
  void Lqueue<T>::Display(){
    Node<T>* currNode=m_head;
    int counter=1;
    while(currNode!=nullptr&& counter!=6){
      cout<<counter<<". "<<currNode->GetData()<<endl;
      currNode=currNode->GetNext();
      counter++;
    }
  }
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  template <class T>
  T Lqueue<T>::Front(){
    return m_head->GetData();
  }
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  template <class T>
  bool Lqueue<T>::IsEmpty(){
    if(m_size==0){
      return true;
    }
    else{
      return false;
    }
  }
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  template <class T>
  int Lqueue<T>::GetSize(){
    return m_size;
  }
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  template <class T>
  void Lqueue<T>::Swap(int position){
    //Need  4 nodes. position-1& position-2; 
    //copy of position-1 and position 
    Node<T>* prevNode=m_head;
    Node<T>* prePreNode;

    Node<T>* lastNode=m_head;
    Node<T>* preLastNode;
    if(m_size==2){
      Node<T>*temp=m_head;
      m_head=m_tail;
      m_tail=temp;
      m_head->SetNext(temp);
      m_tail->SetNext(nullptr);
    }
    else if(position==m_size){
      for(int i=0;i<position-1;i++){
        prePreNode=prevNode;
        prevNode=prevNode->GetNext();
      }
      for(int i=0;i<position;i++){
        preLastNode=lastNode;
        lastNode=lastNode->GetNext();
      }
      //10->11->12->13
      prePreNode->SetNext(lastNode);
      //10->12->13
      Node<T>* temp=lastNode->GetNext();
      //temp=13
      lastNode->SetNext(preLastNode);
      //10->12->11->12->11...
      preLastNode->SetNext(temp);
      //10->12->11->13
      m_tail=lastNode;
    }
    else{
      for(int i=0;i<position-1;i++){
        prePreNode=prevNode;
        prevNode=prevNode->GetNext();
      }
      for(int i=0;i<position;i++){
        preLastNode=lastNode;
        lastNode=lastNode->GetNext();
      }
      //10->11->12->13
      prePreNode->SetNext(lastNode);
      //10->12->13
      Node<T>* temp=lastNode->GetNext();
      //temp=13
      lastNode->SetNext(preLastNode);
      //10->12->11->12->11...
      preLastNode->SetNext(temp);
      //10->12->11->13
    }
  }
   // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  template <class T>
  void Lqueue<T>::Clear(){
    Node<T>* currNode =m_head;
    Node<T>* temp;
    while(currNode!=nullptr){
      temp=currNode->GetNext();
      delete currNode;
      currNode=temp;
    }
    m_head=nullptr;
    m_size=0;
  }
  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  template < class T>
  void Lqueue<T>::TestHeadTail(){
    Node<T>* head=m_head;
    cout<<"Head "<<head->GetData()<<endl;
    cout<<"Tail "<<m_tail->GetData()<<endl;
  }

  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  ostream& operator<<(ostream& output, const Lqueue<U>& thisLqueue){
  	Node<U>* currNode=thisLqueue.m_head;
  	U data;
    while(currNode!=nullptr){
  		data=currNode->GetData();
  		currNode=currNode->GetNext();
  		output<<data<<endl;
    }
  	return output;
  }
  
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  
  //Fix this one
  template <class T>
  T& Lqueue<T>::operator[](int index){
    Node<T>* currNode=m_head;
    for(int i=0;i<index;i++){
      currNode=currNode->GetNext();
    }
    return currNode->GetData();
  }

//*****************************************************************
//Implement Lqueue here


//****************************************************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue (try valgrind too!)

//fix push
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10, 1);
  newLQ1.Push(11, 1);
  newLQ1.Push(12, 1);
  newLQ1.Push(13, 1);
  cout << endl;

  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);
  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ1;
  cout << endl;
  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1;
  cout << "newLQ2" << endl;
  cout << newLQ2;
  cout << "newLQ3" << endl;
  cout << newLQ3;
  cout << endl;
  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;
  
  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;
  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  newLQ2.TestHeadTail();
  cout << "Should display head 10 and tail 13" << endl;
  cout << endl;  
  return 0;
}