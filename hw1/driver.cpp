//Sophia Carlone
//AI - HW1

#include<iostream>

using namespace std;

int main(){
	cout << "hello world" << endl;
	return 0;
}
/*IDEAS*/

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