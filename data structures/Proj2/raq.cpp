/*****************************************
** This project simulates a range average query.
** It constructs both a RAQ and BlockRAQ object 
** That shortens runtime of queries
**
**  
***********************************************/
#include "raq.h"

// RAQ Class implements the Dynamic Programming solution

  // Create the RAQ object; perform precomputation
  RAQ::RAQ(std::vector<float> data){
    m_data = data;
    //loop is right but figure out how to place things at the right place
    //for(int i=0;i<m_data.size();i++){
    int i=0;
    int test = (int) sqrt((float) 9);
    std::vector<float> line;
    float average;
    //loops thru
    for(int i=0;i<m_data.size();i++){
	    for(int j=i;j<m_data.size();j++){
	   		//if i=j push a new vector
	   		if(i==j){
	   			average = m_data.at(j);
	   			line.push_back(average);
	   			m_preComp.push_back(line);
	    	}
	    	else{
	    		//add to the vector we in if its not
	    		average=avg(i,j);
	    		m_preComp.at(i).push_back(average);
	    	}
	    }
	}
  }

  
  // Query the RAQ for interval [i, j]
  float RAQ::query(int i, int j) const{
    //rough idea
    if (i>j) {
    	throw std::domain_error("RAQ::query: j must be greater than i");
    	return 0;
  	}
  	if (i<0) {
    	throw std::domain_error("RAQ::query: i Cannot be negative");
    	return 0;
  	}
  	if (j>=m_data.size()) {
    	throw std::domain_error("RAQ::query: j must be greater than i");
    	return 0;
  	}
    return m_preComp.at(i).at(j);
  }
  
  // Dump the RAQ data structure to stdout
  void RAQ::dump() const{
  	for(int i=0;i<m_preComp.size();i++){
	    for(int j=i;j<m_preComp.at(i).size();j++)
	    	std::cout << m_preComp.at(i).at(j)  <<" ";
	    std::cout <<std::endl;
    }
  }

  float RAQ::avg(int i, int j){
  	//check
    float avg;
    if(i==j){
        avg = m_preComp.at(i).at(0);
   	}
    else{
        //read and make sure thats good 
        avg = ((j-1-i+1)*m_preComp.at(i).at(j-1)+m_data.at(j))/(j-1-i+2);
    	

    }  	
    return avg;
  }
// BlockRAQ class implements the Block Decomposition solution

BlockRAQ::BlockRAQ(std::vector<float> data){
	m_data = data;
	m_blockNum = (int) sqrt((float)m_data.size());
	m_blockCount = m_data.size()/m_blockNum;
	m_leftovers = m_data.size() % m_blockNum;
	int total=0;
	//loops thru the data list and stores the block values
	for(int i=0; i<m_data.size()-m_leftovers;i+=m_blockNum){
		total+=m_data.at(i);
		for(int x=i+1; x<i+m_blockNum;x++)
			total+=m_data.at(x);
		m_blocks.push_back((float)total/m_blockNum);
		total=0;
	}
	//scans for leftovers
	for(int i=m_data.size()-m_leftovers;i<m_data.size();i++)
		total+=m_data.at(i);
	if(total!=0)
		m_blocks.push_back((float)total/m_leftovers);

}
float BlockRAQ::query(int i, int j) const{
	if (i>j) {
    	throw std::domain_error("BlockRAQ::query: j must be greater than i");
  		return 0;
  	}
  	if (i<0) {
    	throw std::domain_error("BlockRAQ::query: i Cannot be negative");
    	return 0;
  	}
  	if (j>=m_data.size()) {
    	throw std::domain_error("BlockRAQ::query: j must be greater than i");
    	return 0;
  	}
	int distance;
	int counter=0;
	float avg=0;
	for(int x=i;x<=j;x++){
		distance=j-x;
		//if its on the start of a block and we can move a block
		if((distance>m_blockNum-1) && (x%m_blockNum == 0)){
			avg+=m_blocks.at(x/m_blockNum)*m_blockNum;
			x+=m_blockNum-1;
			counter+=m_blockNum;	
		}//if we arent
		else{
			avg+=m_data.at(x);
			counter++;
		}
	}
	avg/=counter;
	return avg;
}

void BlockRAQ::dump() const{
	std::cout << "Num blocks: "<<m_blockCount<<std::endl;
	std::cout << "Block size: "<<m_blockNum<<std::endl;
	std::cout << "Block averages:"<<std::endl;
	for(int o = 0; o<m_blocks.size();o++)
		std::cout << m_blocks.at(o)  <<" ";
}