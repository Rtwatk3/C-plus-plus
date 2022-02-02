#include <iostream>
#include "heap.h"
#include "donut.h"

int main()
{
	Heap <Donut> newHeap;
	/*newHeap.push_back(Donut("glazed", 5, "super donut"));
  	newHeap.push_back(Donut("glazed", 12, "mega donut"));
  	newHeap.push_back(Donut("glazed", 4, "shack of donuts"));
  	
  	newHeap.push_back(Donut("boston cream", 10, "mega donut"));
  	newHeap.push_back(Donut("boston cream", 5, "donut world"));
  	*/
  	newHeap.insert(Donut("sprinkle", 7, "donut world"));
  	newHeap.insert(Donut("sprinkle", 15, "super donut"));
  	newHeap.insert(Donut("sprinkle", 8, "shack of donuts"));
  	/*
  	newHeap.push_back(Donut("boston cream", 3, "donut joint"));
  	
  	newHeap.push_back(Donut("cinnamon", 3, "shack of donuts"));
  	
  	newHeap.push_back(Donut("bavarian cream", 28, "mega donut"));
  	newHeap
  	newHeap.push_back(Donut("cinnamon", 11, "super donut"));
	*/
	cout<<"Dump 1"<<endl;
	newHeap.dump();
	newHeap.removeTop();
	cout<<"dump 2"<<endl;
	newHeap.dump();
	return 0;
}