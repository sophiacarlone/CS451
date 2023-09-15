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
    std::string sequence; //sequence of the state
    int actionAmount;
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
    
    if(s.sequence.back() == action.front() && (s.sequence.find(action) == string::npos)){
        successorState.sequence = s.sequence + action; //Question: dont remember if this works
        cout << successorState.sequence << endl;
    }
    else
        successorState.sequence = "fail";

    successorState.initial = false;
    successorState.actionAmount = s.actionAmount + 1;
    
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
bool goalTest(const state& s, int totalActions){
    if(s.actionAmount == totalActions) return true; //needs to be based on if all actions have been used
    return false;
}

node fringeManipulationBFS(const node& initial){ //TODO: find a better name
	list<node> visitedFringe; //NOT USED
	vector<string> actions = {"ABC", "CDE", "CFG", "EHE", "EIJ",  "GLC"}; //TODO: pass in the list?
	queue<node> unvisitedFringe;
    node temp; //for testing in for loop later

	unvisitedFringe.push(initial);
	while(true){
		if(unvisitedFringe.size() == 0){
			cout << "failure" << endl;
			exit(1);
		}
		node currentNode = unvisitedFringe.front();

		if (goalTest(currentNode.state_, actions.size()-1)) return currentNode; //TODO: this will have to be its own function now
		else{
			for(int i = 0; i < actions.size(); i++){
                temp = successor(currentNode.state_, actions[i]);
                if (temp.state_.sequence != "fail")
				    unvisitedFringe.push(temp);
                    //increase the amount of correct shit
            }
		}
        unvisitedFringe.pop();
	}
}

node fringeManipulationDFS(const node& initial){ //TODO: find a better name
	list<node> visitedFringe;
	vector<string> actions = {"ABC", "CDE", "CFG", "EHE", "EIJ", "GHK", "GLC"}; //TODO: pass in the list?
	stack<node> unvisitedFringe;
    node temp; //for testing in for loop later

	unvisitedFringe.push(initial);
	while(true){
		if(unvisitedFringe.size() == 0){
			cout << "failure" << endl;
			exit(1);
		}
		node currentNode = unvisitedFringe.top();
		if (goalTest(currentNode.state_, actions.size()-1)) return currentNode; //TODO: this will have to be its own function now
		else{
			for(int i = 0; i < actions.size(); i++){
				temp = successor(currentNode.state_, actions[i]);
                if (temp.state_.sequence != "fail")
				    unvisitedFringe.push(temp);
                    //increase the amount of correct shit
            }
		}
        unvisitedFringe.pop();
	}
}



int main(){
    cout << "start of program" << endl; //TODO: Clean and make this take input for dominios
    
    node init_n;
    state init_s;
 
    init_s.sequence = "ABC";
    init_s.initial = true;
    init_s.actionAmount = 0;

    init_n.state_ = init_s;
    init_n.action = "";
 
    node solution1 = fringeManipulationBFS(init_n);
    cout << "found a solution: " << endl;
    cout << "Solution " << solution1.state_.sequence << endl;
    
    node solution2 = fringeManipulationDFS(init_n);
    cout << "found a solution: " << endl;
    cout << "top: " << solution2.state_.sequence << endl;
}