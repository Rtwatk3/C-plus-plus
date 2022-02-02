/*****************************************
** This project simulates a SkewHeap and performs 
** inserts and removes while keeping the heap balanced.  
**
** 
***********************************************/
#include "SkewHeap.h"

// Defines pri_fn as a function pointer
  //typedef int (*pri_fn)(Node *);

  // Constructor.  Must specify priority function.
  SkewHeap::SkewHeap(pri_fn pri){
    //make everything the default
    priority = pri;
    m_heap = nullptr;
  }

  // Destructor, copy constructor, assignment operator
  SkewHeap::~SkewHeap(){
    destroyEmAll(m_heap);
  }

  void SkewHeap::destroyEmAll(Node *temp){
    //inorder deconstructor delete at the leaf
    if(temp){
      destroyEmAll(temp->left);
      destroyEmAll(temp->right);
      delete temp;
    }
  }

  SkewHeap::SkewHeap(const SkewHeap& rhs){
    //Mheap is set to be the copy helper
    m_heap = copyHelper(rhs.m_heap);
    priority = rhs.priority;
  }

  Node* SkewHeap::copyHelper(Node *temp){
    if(temp == nullptr)
      return nullptr;

    Node *newNode;
    //if its an int make an int node
    if(temp->tagged_union==ISINT){
        newNode = new Node(temp->data_int);
        //cout<<newNode->data_int<<endl;
    }
    //if its a string make a string node
    else{
      newNode = new Node(temp->data_string);
      //cout<<newNode->data_string<<endl;
    }
    //inorder traverse
    newNode->left = copyHelper(temp->left);
    newNode->right = copyHelper(temp->right);
    return newNode;
  }


  const SkewHeap& SkewHeap::operator=(const SkewHeap& rhs){
    //delete it
    destroyEmAll(m_heap);
/*
    if ( rhs.m_heap == nullptr ) {
      m_heap = nullptr;
    }
    else{*/
    //remake it
      m_heap = copyHelper(rhs.m_heap);
      priority = rhs.priority;
    //}
    return *this;
  }

  // Priority function get and set
  pri_fn SkewHeap::getPriFn() const{
    return priority;
  }

  void SkewHeap::setPriFn(pri_fn pri){
    //Makes a new skewheap using the priority 
    SkewHeap other(pri);
    Node* temp;
    while(!empty()){
      temp = front();
      if(temp->tagged_union == ISSTRING)
        other.insert(temp->data_string);
      else
        other.insert(temp->data_int);
      removeTop();
    }
    //set this skew heap to the new one
    *this = other;
  } 

  // Return true if the skew heap is empty
  bool SkewHeap::empty() const{
    if(m_heap == nullptr){
      return true;
    }
    else
      return false;
  }

  // Overloaded insertion operators.  One for string data, one for
  // integer data.
  void SkewHeap::insert(string data){
    Node *newNode = new Node(data);
    //Inserts it as the head if empty
    if(empty()){
      m_heap = newNode;
    }else if(priority(m_heap)<priority(newNode))
    {
      //makes it the new head if its greater
      newNode->left= m_heap;
      m_heap = newNode;
    }
    else{
      mergeHelper(m_heap,newNode);   
    }
  }

  void SkewHeap::insert(int data){
    Node *newNode = new Node(data);
    //Inserts it as the head if empty
    if(empty()){
      m_heap = newNode;
    }
    else if(priority(m_heap)<priority(newNode))
    {
      //makes it the new head if its greater
      newNode->left= m_heap;
      m_heap = newNode;
    }
    else
    	mergeHelper(m_heap,newNode);   
  }

  // Access highest priority element in the skew heap.
  Node* SkewHeap::front() const{
    return m_heap;
  }

  // Remove the highest priority element from the skew heap.
  void SkewHeap::removeTop(){
    //delete top and then merge left and right
    Node *leftNode = m_heap->left;
    Node *rightNode = m_heap->right;
    Node *temp = m_heap;
    delete temp;
    m_heap = mergeHelper(leftNode,rightNode);
  }

  // Merge two heaps.  Merged heap in *this; sh is empty afterwards.
  void SkewHeap::skewHeapMerge(SkewHeap& sh){
    if(sh.priority!=priority){
      throw std::domain_error("SkewHeap::skewHeapMerge: Cannot merge two different priorities");
      return;
    }
    if(priority>sh.priority){
      m_heap = mergeHelper(m_heap,sh.m_heap);
    	//mergeHelper(*this,sh);
    }
    else{
      m_heap = mergeHelper(sh.m_heap,m_heap);
    	sh.m_heap= nullptr;
    }

  }

  Node* SkewHeap::mergeHelper(Node *left, Node *right){
  	// If either heap is empty, return the other
     if (left == nullptr){ 
     	return right;
     }
     if (right == nullptr){ 
     	return left;}
     // Ensure p1 has higher priority root
     if( priority(left) < priority(right)){
        swap(left,right);
     }

     // Swap the left and right children of p1      
     swap(left->left, left->right);

     // Recursively merge p1's left child with p2; make the
     // merged heap the new left child of p1		       
     left->left = mergeHelper( left->left, right );
     return left;
  }
  /*void SkewHeap::swap(Node *left, Node *right){
    Node *temp = left;
    left = right;
    right = temp;
  }*/
  // Print inorder traversal.
  void SkewHeap::inorder() const{
    Node *temp = m_heap;
    inOrderHelper(temp);
  }
  
  // Dump the contents of the heap in decreasing priority order.
  void SkewHeap::dump() const{
    //make deep copy
    SkewHeap other(*this);
    Node *temp = other.m_heap;
    //while its not empty
    while(temp != nullptr){
      //make the node data right
      if(temp->tagged_union==ISINT){
        cout << "Data: "<<temp->data_int;
        //cout << " Priority is: "<<priority(temp);
      }
      else{
        cout << "Data: "<<temp->data_string;
      }
      cout << " Priority is: "<<priority(temp)<<endl;
      //pop the top
      other.removeTop();
      temp=other.m_heap;
    }
  }

  void SkewHeap::inOrderHelper(Node *heapNode) const{
    if (heapNode==nullptr) return ;
    //inorder traversal 
    cout << "("; 
    inOrderHelper(heapNode->left);
    if(heapNode->tagged_union==ISINT)
    	cout << heapNode->data_int;
    else
    	cout << heapNode->data_string;
    inOrderHelper(heapNode->right);
    cout << ")" ;

    return ;
  }