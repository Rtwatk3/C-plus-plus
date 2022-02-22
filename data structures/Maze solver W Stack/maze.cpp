/*****************************************
** This project Solves a maze using a stack.  
**
** 
***********************************************/
#include <stdexcept>
#include "maze.h"

Maze::Maze(int ncell) {
  if (ncell < 1) {
    throw std::invalid_argument("Maze::Maze(): ncell must be >= 1");
  }

  _ncell = ncell;
  _maze = new cell_t[_ncell];
}

Maze::~Maze() {
  // IMPLEMENT DESTRUCTOR
	delete [] _maze;
}

void Maze::readFile(std::string fileName) {
  int numCells;
  int cell, n1, n2, n3, n4; 
  std::ifstream dataFile;
  
  dataFile.open(fileName);

  if (dataFile.is_open()) {
    dataFile >> numCells;
    this->reset(numCells);

    for (int i = 0; i < numCells; i++) {
      dataFile >> cell >> n1 >> n2 >> n3 >> n4;
      this->insert(cell_t(cell, n1, n2, n3, n4));
    }
  }
}

int Maze::getNcell() const {
  return _ncell;
}

void Maze::reset(int ncell) {
  if (ncell < 1) {
    throw std::invalid_argument("Maze::reset(): ncell must be >= 1");
  }

  if (_maze != nullptr) {
    delete [] _maze;
  }
  
  _ncell = ncell;
  _maze = new cell_t[_ncell];
}

void Maze::insert(cell_t cell) {
  if (_maze == nullptr) {
    throw std::domain_error("Maze::insert(): attempt to insert into uninitialized Maze object");
  }
  if (cell.cellNum < 0 || cell.cellNum >= _ncell) {
    throw std::invalid_argument("Maze:insert(): invalid cell number");
  }
  _maze[cell.cellNum] = cell;
}
  
cell_t Maze::retrieve(int nc) const {
  if (_maze == nullptr) {
    throw std::domain_error("Maze::retrieve(): attempt to retrieve from an uninitialized Maze object");
  }
  if (nc < 0 || nc >= _ncell) {
    throw std::invalid_argument("Maze:retrieve(): invalid cell index");
  }
  
  return _maze[nc];
}

void Maze::dump() const {

  std::cout << "[*] Dumping the maze cells..." << std::endl;
  
  for (int i = 0; i < _ncell; i++) {
    int nc = _maze[i].cellNum;
    if (nc != i) {
      std::cerr << "Warning: maze cell at index " << i
		<<" has cellNum of " << nc << std::endl;
    }
    std::cout << "Cell " << i << " has neighbor cells: ";
    neighbor_t nbs = _maze[i].neighbors;
    int n0, n1, n2, n3;
    if ( nbs[0] >= 0 ) std::cout << nbs[0] << " ";
    if ( nbs[1] >= 0 ) std::cout << nbs[1] << " ";
    if ( nbs[2] >= 0 ) std::cout << nbs[2] << " ";
    if ( nbs[3] >= 0 ) std::cout << nbs[3] << " ";
    std::cout << std::endl;
  }
}

std::vector<int> Maze::solve() const {
  // IMPLEMENT THE SOLVE METHOD
	SolveStack stack;
	if (_ncell==0) {
    	throw std::domain_error("Maze::solve(): attempt to solve uninitialized Maze object");
  	}
  	//deepcopy of maze object
  	Maze newMaze(_ncell);
  	for (int i=0;i<_ncell;i++){
  		newMaze._maze[i]=_maze[i];
  	}
  	//Variable setup
  	std::vector<int> path;
  	int currentIndex=0;
  	int moveTo,badIndex,from;
  	src_dest_t fromTo=std::pair<int,int>(VACANT, 0);
  	cell_t currCell=newMaze.retrieve(0);
  	//push the first index in
  	stack.push(fromTo);
  	path.push_back(currentIndex);
  	from=0;
  	//while CURRENT index is not at the last index AND we at the front of the maze 
  	while(currentIndex != _ncell-1 && currentIndex > VACANT && !stack.empty()){
  		//retrieve cell and establish neigbors
  		currCell=newMaze.retrieve(currentIndex);
  		neighbor_t nbs = currCell.neighbors;
  		//check if theres neighbors and find which one it is
  		if(nbs[0]!=VACANT||nbs[1]!=VACANT||nbs[2]!=VACANT||nbs[3]!=VACANT){
  			if(nbs[0]>=0){
  				moveTo=currCell.neighbors[0];
  				}
  			else if(nbs[1]!=VACANT) {
  				moveTo=currCell.neighbors[1];
  				}
  			else if(nbs[2]!=VACANT){
  				moveTo=currCell.neighbors[2];
  				}
  			else {
  				moveTo=currCell.neighbors[3];
  				}
  				//push the data to the stack
  			fromTo.first = currentIndex;
  			fromTo.second = moveTo;
  			stack.push(fromTo);
  			from=currentIndex;
  			currentIndex=moveTo;
  			currCell=newMaze.retrieve(currentIndex);
  			//Find where the previous cell's location is in the next cell's neighbor list
  			//then set it to vacant to prevent it from going back there
  			for (int x = 0; x < currCell.neighbors.size(); x++) {
  				if(from == currCell.neighbors.at(x)){
  					newMaze._maze[currentIndex].neighbors.at(x)=VACANT;
  				}
  			}

  			currCell=newMaze.retrieve(currentIndex);
  			path.push_back(currentIndex);
  		}
  		//if theres no neighbor, pop it off the stack
  		else{
  			fromTo = stack.pop();
  			currentIndex = fromTo.first;
  			if(currentIndex!=VACANT){
  				//find the cell that we were just at in the new cell's neigbor list
  				//set it to vacant. 
  			  	currCell=newMaze.retrieve(currentIndex);
  			  	from=fromTo.second;
  			  	currCell=newMaze.retrieve(currentIndex);
  			  	for (int x = 0; x < currCell.neighbors.size(); x++) {
  			  		if(from == currCell.neighbors.at(x)){
  			  			newMaze._maze[currentIndex].neighbors.at(x)=VACANT;
  			  		}
  			  	}}
  			path.pop_back();
  		}
  	}
  	if(path.size()>0)
  		std::cout <<"Solution Found!"<< std::endl;
  	else
  		std::cout <<"No Solution Found."<< std::endl;
  	return(path);
  }

Maze::SolveStack::SolveStack() {
  _stack = nullptr;//top
}

Maze::SolveStack::~SolveStack() {
  // IMPLEMENT DESTRUCTOR

	while(!empty()){
		pop();
	}

}

bool Maze::SolveStack::empty() const {
  return _stack == nullptr;
}
				   
void Maze::SolveStack::push(src_dest_t src_dest) {
  // IMPLEMENT PUSH METHOD
	// Makes a new node using overloaded constructor
	
	StackEntry *newNode = new StackEntry(src_dest.first,src_dest.second);
	newNode->next=_stack;
	_stack=newNode;
}

src_dest_t Maze::SolveStack::pop() {
  // Pops it off
	if (empty()) {
    	throw std::domain_error("Maze::SolveStack::pop(): attempt to pop from an uninitialized Maze object");
  	}
	src_dest_t tempData= _stack->src_dest;
	StackEntry *node = _stack;
	_stack=node->next;
	delete node;
	return tempData;

}

src_dest_t Maze::SolveStack::read() const {
  // IMPLEMENT READ METHOD
	if (empty()) {
    	throw std::domain_error("Maze::SolveStack::read(): attempt to read from an uninitialized Maze object");
  	}
	return _stack->src_dest;
}
