//Sophia Carlone
//AI HW1

#include<iostream>
#include<list> //NOT USED
#include<string>
#include<stack>
#include<queue>
#include<vector>

using namespace std;

struct state{
    bool initial; //is it the initial state? //NOT USED
    std::string top; //top of the state
    std::string bottom; //bottom of the domino  
};

struct node{
    state state_; //current state
    state* parent; //parent node NOT USED
    std::string action; //what action generated the state
};

/*successor function
Summary: will find the successor of a state based on an action
Inputs:
    - s (state structure): current state
    - action (string): action modifying current state
Outputs: new state
*/
const node successor(const state& s, const std::string& action){
    state successorState;
    int comma = action.find(","); //TODO: error checking
    string top = action.substr(0, comma); 
    string bottom = action.substr(comma+1);
    // cout << "top: " << top << " , bottom: " << bottom <<endl;
    successorState.top = s.top + top; //Question: dont remember if this works
    successorState.bottom = s.bottom + bottom; //Question: dont remember if this works

    // cout << "top: " << successorState.top << " , bottom: " << successorState.bottom << endl;

    successorState.initial = false;
    node successorNode;
    successorNode.state_ = successorState;
    successorNode.action = action;
    return successorNode;
}

/*goalTest function
Summary: check if state is a goal state
Inputs: 
    - s (state structure): possible goal state
Outputs: bool that reflects if goal state has been reached
*/
bool goalTest(const state& s){
    if(s.top == s.bottom) return true;
    return false;
}

node fringeManipulationBFS(const node& initial){ //TODO: find a better name
	list<node> visitedFringe; //NOT USED
	vector<string> actions = {"AA,A"}; //TODO: pass in the list?
	queue<node> unvisitedFringe;

	unvisitedFringe.push(initial);
	while(true){
		if(unvisitedFringe.size() == 0){
			cout << "failure" << endl;
			exit(1);
		}
		node currentNode = unvisitedFringe.front();
		if (goalTest(currentNode.state_)) return currentNode; //TODO: this will have to be its own function now
		else{
			for(int i = 0; i < actions.size(); i++){
				unvisitedFringe.push(successor(currentNode.state_, actions[i]));
            }
		}
        unvisitedFringe.pop();
	}
}

node fringeManipulationDFS(const node& initial){ //TODO: find a better name
	list<node> visitedFringe;
	vector<string> actions = {"AA,A"}; //TODO: pass in the list?
	stack<node> unvisitedFringe;

	unvisitedFringe.push(initial);
	while(true){
		if(unvisitedFringe.size() == 0){
			cout << "failure" << endl;
			exit(1);
		}
		node currentNode = unvisitedFringe.top();
		if (goalTest(currentNode.state_)) return currentNode; //TODO: this will have to be its own function now
		else{
			for(int i = 0; i < actions.size(); i++)
				unvisitedFringe.push(successor(currentNode.state_, actions[i]));
		}
        unvisitedFringe.pop();
	}
}



int main(){
    cout << "start of program" << endl; //TODO: Clean and make this take input for dominios
    
    node init_n;
    state init_s;
 
    init_s.top = "AA";
    init_s.bottom = "A";
    init_s.initial = true;

    init_n.state_ = init_s;
    init_n.action = "";
 
    node solution1 = fringeManipulationBFS(init_n);
    cout << "found a solution: " << endl;
    cout << "top: " << solution1.state_.top << " bottom: " << solution1.state_.bottom << endl;
    
    node solution2 = fringeManipulationDFS(init_n);
    cout << "found a solution: " << endl;
    cout << "top: " << solution2.state_.top << " bottom: " << solution2.state_.bottom << endl;
}