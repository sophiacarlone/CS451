//Sophia Carlone
//AI - HW1

#include<iostream>
#include<list>
#include<stack>
#include<queue>
#include"pcp.hpp"

using namespace std;

const node& fringeManipulationBFS(const node& initial, int setting){ //TODO: find a better name
	list<node> visitedFringe;
	list<string> actions = {"MOM,M", "O,OMOMO"}; //TODO: pass in the list?
	queue<node> unvisitedFringe;

	unvisitedFringe.push(initial);
	while(true){
		if(unvisitedFringe.size() == 0){
			cout << "failure" << endl;
			exit(1);
		}
		node currentNode = fringe.pop();
		if (goalTest(currentNode.state)) return currentNode; //TODO: this will have to be its own function now
		else{
			for(int i = 0; i < actions.size(); i++)
				fringe.push(successor(currentNode.state, actions[i]));
		}
	}
}

const node& fringeManipulationDFS(const node& initial, int setting){ //TODO: find a better name
	list<node> visitedFringe;
	list<string> actions = {"MOM,M", "O,OMOMO"}; //TODO: pass in the list?
	stack<node> unvisitedFringe;

	unvisitedFringe.push(initial);
	while(true){
		if(unvisitedFringe.size() == 0){
			cout << "failure" << endl;
			exit(1);
		}
		node currentNode = fringe.pop();
		if (goalTest(currentNode.state)) return currentNode; //TODO: this will have to be its own function now
		else{
			for(int i = 0; i < actions.size(); i++)
				fringe.push(successor(currentNode.state, actions[i]));
		}
	}
}

const node& fringeManipulation(const node& initial, int setting){ //TODO: find a better name
	list<node> fringe;
	int currentNodeIndex = 0;

	fringe.push_back(initial);
	while(true){
		if(fringe.size() == 0){
			cout << "failure" << endl;
			exit(1);
		}
		node currentNode = fringe.back();
		currentNodeIndex = fringe.size()-1; //should be index at the end of the list
		if (goalTest(currentNode.state)) return currentNode; //TODO: this will have to be its own function now
		else{
			if(setting == BFS){ //BFS n, put successors into the fringe
				fringe.push_back(successor());
			} 
			else if(setting == DFS){
				fringe.push_back(successor());
			}
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