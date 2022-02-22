// File: treap.cpp
/*****************************************
** 
** This project simulates a treap and performs inserts and removes.  
**
** 
***********************************************/

using namespace std ;

#include "treap.h"

Treap::Treap() {
  _nptr = nullptr ;
}

Treap::Treap(const Treap& other) {
  //
  // Implement copy constructor
  // 
  //
	if ( other._nptr == nullptr ) {
    _nptr = nullptr;
  }
  else{
    TreapNode *newTreap = new TreapNode(*other._nptr);
    _nptr = newTreap;
  }


}

Treap::~Treap() {
  //
  // Implement destructor
  //delete nptr which calls destructor for all nodes cascadinf down
  delete _nptr;
  _nptr = nullptr;
}

const Treap& Treap::operator=(const Treap& rhs) {
  //
  // Implement assignment operator
  //
  delete _nptr;
  //if its empty make it empty
  if ( rhs._nptr == nullptr ) {
    _nptr = nullptr;
  }
  else{
    //make a new treapnode and set _nptr = to it using the other's pointer
    TreapNode *newTreap = new TreapNode(*rhs._nptr);
    _nptr = newTreap;
  }
  return *this;
}

// Return -1 if the treap is empty; otherwise, return value in _height.
int Treap::height() const {
  return _nptr ? _nptr->_height : -1 ;
}

// Return the priority of the root node of a Treap.
// Note: numeric_limits<priority_t>::min() returns the minimum value
// of the priority type.  We will only use int priorities, so this is
// the minimum integer value.
priority_t Treap::priority() const {
  return _nptr ? _nptr->_pri : numeric_limits<priority_t>::min() ;
}

const data_t* Treap::find(const data_t& x) {
  //
  // Implement find function
  //
  //if its empty return null
	if(_nptr==nullptr){
   		return nullptr;
  	}
    //found it
	if(_nptr->_data==x){
		return &_nptr->_data;
	}
  //if its less than the current value go left
	else if(_nptr->_data>x){
		_nptr->_left.find(x);
	}
  //if its greater than the current value go right
	else if(_nptr->_data<x){
    	_nptr->_right.find(x);
	}
}

// Inorder traversal.  Recommend you NOT change this!!!
void Treap::inorder() {

  if ( empty() ) return ;

  cout << "(" ;
  _nptr->_left.inorder() ;

  cout << _nptr->_data << ":" << priority() << ":" << height() ;

  _nptr->_right.inorder() ;
  cout << ")" ;

  return  ;
}

// Used for debugging and grading.  Interprets the characters in
// position[] as directions in the tree.  E.g., "RLR" means, "starting
// from root, go right, then left, then right."  If position[] is an
// empty string, then it just locats the value a the root.
// See project description for details.
bool Treap::locate (const char position[], data_t& x, priority_t& p, int& h, int offset) {

  if (_nptr == nullptr) return false ;

  if (position[offset] == '\0') {
    x = _nptr->_data ;
    p = _nptr->_pri ;
    h = _nptr->_height ;
    return true ;
  }

  if (position[offset] == 'L') {
    return _nptr->_left.locate(position, x, p, h, offset+1) ;
  }

  if (position[offset] == 'R') {
    return _nptr->_right.locate(position, x, p, h, offset+1) ;
  }

  cerr << "Bad position character!\n" ;
  exit(17) ;

  return false ; 
}


// Basic BST insertion.  Does not allow duplicate values.
//
// Complete this function to do Treap insertion.
//
void Treap::insert(const data_t& x, const priority_t& p) {
	/*
	IT HAS FINNALLY BEEN FIXED DO NOT TOUCH IT EVER AGAIN

	*/
  //do nothing if it is already in there 
	if(find(x)!=nullptr)
		return;
  if ( empty() ) {

    _nptr = new TreapNode(x, p) ;
  }

  if (_nptr->_data < x) { 
    _nptr->_right.insert(x, p) ;
    //insetr right
    
  } else if (x < _nptr->_data ) {
    _nptr->_left.insert(x, p) ;
    //insert left
  }
    //update heights
  int leftHeight = _nptr->_left.height();
  int rightHeight = _nptr->_right.height();
  _nptr->_height = 1 + ( leftHeight > rightHeight ? leftHeight : rightHeight );
  if(_nptr->_left.priority()>priority()){
    	//cout<<" right rotate :"<<endl;
    	//right rotate
    	TreapNode *temp = _nptr;
  		TreapNode *y = temp->_left._nptr; //left = y
  		TreapNode *b = y->_right._nptr; //left right = b
  		y->_right._nptr = temp; //y right points to _nptr
      //_nptr left points to b
  		temp->_left._nptr = b;
      //update heights
  		_nptr->_height = 1 + ( _nptr->_left.height() > _nptr->_right.height()
  							 ? _nptr->_left.height() : _nptr->_right.height() );
  		y->_height = 1 + ( y->_left.height() > y->_right.height()
  							 ? y->_left.height() : y->_right.height() );
  		//move nptr
      _nptr = y;

  		//cout<<endl<<"End right rotate;"<<endl;
  	}
  if(_nptr->_right.priority()>priority()){

  		TreapNode *temp = _nptr;

  		TreapNode *y = temp->_right._nptr; //left = y
  		TreapNode *b = y->_left._nptr; //left right = b

  		y->_left._nptr = temp; // left points to nptr
      //temp right = b
  		temp->_right._nptr = b;
      //update height
  		_nptr->_height = 1 + ( _nptr->_left.height() > _nptr->_right.height()
  							 ? _nptr->_left.height() : _nptr->_right.height() );
  		y->_height = 1 + ( y->_left.height() > y->_right.height()
  							 ? y->_left.height() : y->_right.height() );
  		//move nptr
      _nptr = y;
  		
  	}
}

bool Treap::remove(const data_t& x) {
  //if its not in here return false
  if(_nptr==nullptr){
   		return false;
  	}//go left if its less
	if(_nptr->_data>x){
		_nptr->_left.remove(x);
	}
  //go right if its greater
	else if(_nptr->_data<x){
    	_nptr->_right.remove(x);
	}
	else{
    //if its a leaf
		if(_nptr->_left._nptr==nullptr && _nptr->_right._nptr==nullptr){
			
			delete _nptr;
			_nptr = nullptr;
		}
    //if it has 2 children
		else if(!_nptr->_left.empty()&&!_nptr->_right.empty()){
			if(_nptr->_left._nptr->_data > _nptr->_right._nptr->_data){
				//right rotate
				TreapNode *temp = _nptr;
  				TreapNode *y = temp->_left._nptr; //left = y
  				TreapNode *b = y->_right._nptr; //left right = b
  				y->_right._nptr = temp; //
  				temp->_left._nptr = b;
          //update heights
  				_nptr->_height--;
          y->_height --;
  				_nptr = y;
          //keep pushing it down
  				y->_right.remove(x);

  				//cout<<"Right roate"<<endl;
			}
			else{
				//left rotate
				TreapNode *temp = _nptr;
  				TreapNode *y = temp->_right._nptr; //left = y
  				TreapNode *b = y->_left._nptr; //left right = 
  				y->_left._nptr = temp; //
  				temp->_right._nptr = b;
  				//update heights
  				_nptr->_height--;
          y->_height--;
  				_nptr = y;
          //keep pushing it down
  				y->_left.remove(x);
  				//cout<<"Left roate"<<endl;
			}
		}
		else{
      //one child
			//cout<<"One child"<<endl;
			//inorder();
			TreapNode *straggler = _nptr->_left._nptr;
      //find if which one is the child
			if(!_nptr->_left.empty())
				straggler = _nptr->_left._nptr;
			else
				straggler = _nptr->_right._nptr;
			TreapNode *temp = _nptr;
			_nptr = straggler;
			
			//delete temp;
      free(temp);
		}

		return true;		
	}
  //update all the heights
  _nptr->_height = 1 + ( _nptr->_left.height() > _nptr->_right.height()
                 ? _nptr->_left.height() : _nptr->_right.height() );
}
// Treap::dump() just calls TreapNode::dump()
void Treap::dump() {
  if ( !empty() ) _nptr->dump() ;
}

ostream& operator<< (ostream& os, const Treap& T) {
  os << T._nptr ; 
  return os ;
}


TreapNode::TreapNode() : _height(0) {
  // Empty constructor body
}

TreapNode::TreapNode(const data_t& x, const priority_t& p) 
  : _data(x), _pri(p), _height(0) { 
  // Empty constructor body
}

TreapNode::~TreapNode() {
  // Empty destructor
  // Retained for debugging
}

// Dump the contents of a node
void TreapNode::dump() {
  cout << "===== TreapNode::dump()\n" ;
  cout << "      this = " << this << endl ; 
  cout << "      left = " << _left << endl ; 
  cout << "      right= " << _right << endl ; 
  cout << "      data = " << _data << endl ;
  cout << "      height = " << _height << endl ;
  _left.dump() ;
  _right.dump() ;
}

