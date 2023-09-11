//Sophia Carlone
//AI - HW1

#include<iostream>
#include<list>
#include"pcp.hpp"

using namespace std;

#define BFS 1
#define DFS 2

const node& fringeManipulation(const node& initial, int setting){ //TODO: find a better name
	list<node> fringe;

	fringe.push_back(initial);
	while(true){
		if(fringe.size() == 0){
			cout << "failure" << endl;
			exit(1);
		}
		node currentNode = fringe.back();
		if (goalTest(currentNode.state)) return currentNode; //TODO: this will have to be its own function now
		else{
			if(setting == BFS) //TODO: need setting variable to determine BFS vs DFS
				//BFS n, put successors into the fringe
			else if(setting == DFS)
			else{
				cout << "error in search setting" << endl;
				exit(2);
			}
		}
	}
}

/*
	add initial node to fridge
do forever:
	if nothing in fringe, return failure
	chose node n from fringe to expand //Question: last node?
	if n contains a goal state, return n
	Else expand n and add all of n's successors to fringe -> BFS or DFS
		apply all the valid action to the current state and get a bunch of next states to the fringe
*/

int main(){
	node initial; //TODO: set initial node

	return 0;

}



/**********IDEAS*********/

/*
Create a data structure called state
	is it initial
	name/number

successorfn(state, action) -> state

goaltestfn(state)->t/f if its a goal state

nodes:
	state
	parent node (pointer)
	what action action generated it (string)

create a header file with state and node structure
make two files with different successor and goaltest function
main driver 

fringe?

add initial node to fridge
do forever:
	if nothing in fringe, return failure
	chose node n from fringe to expand
	if n contains a goal state, return n
	Else expand n and add all of n's successors to fringe -> BFS or DFS
		apply all the valid action to the current state and get a bunch of next states to the fringe
*/