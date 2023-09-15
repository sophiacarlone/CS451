//Sophia Carlone
//AI HW1

#include<iostream>
#include<list> 
#include<string>
#include<stack>
#include<queue>
#include<vector>

using namespace std;

struct state{
    // bool initial; //is it the initial state? //NOT USED
    std::string top; //top of the state
    std::string bottom; //bottom of the domino  
};

struct node{
    state state_; //current state
    // state* parent; //parent node NOT USED
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
    int comma = action.find(",");  //separate top and bottom of domino based on comma
    if(comma == string::npos){
        cout << "Error with action"<<endl;
        exit(3);
    }
    string top = action.substr(0, comma); 
    string bottom = action.substr(comma+1);
    // cout << "top: " << top << " , bottom: " << bottom <<endl;
    successorState.top = s.top + top; 
    successorState.bottom = s.bottom + bottom; 

    cout << "top: " << successorState.top << " , bottom: " << successorState.bottom << endl;

    // successorState.initial = false;
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

node fringeManipulationBFS(const node& initial, vector<string>& actions){ //TODO: find a better name
	// list<node> visitedFringe; //NOT USED
	// vector<string> actions = {"MOM,M", "O,OMOMO"}; //TODO: pass in the list?
	queue<node> unvisitedFringe;

	unvisitedFringe.push(initial);
	while(true){
		if(unvisitedFringe.size() == 0){
			cout << "failure using BFS" << endl;
            // state failure_s;
            // failure_s.top = "fail";
            node failure;
            failure.state_.top = "fail";
			return failure; 
		}
		node currentNode = unvisitedFringe.front();
		if (goalTest(currentNode.state_)) return currentNode; 
		else{
			for(int i = 0; i < actions.size(); i++){
				unvisitedFringe.push(successor(currentNode.state_, actions[i]));
            }
		}
        unvisitedFringe.pop();
	}
}

node fringeManipulationDFS(const node& initial, vector<string>& actions){ //TODO: find a better name
	// list<node> visitedFringe;
	// vector<string> actions = {"MOM,M", "O,OMOMO"}; //TODO: pass in the list?
	stack<node> unvisitedFringe;

	unvisitedFringe.push(initial);
	while(true){
		if(unvisitedFringe.size() == 0){
			cout << "failure using DFS" << endl;
			// state failure_s;
            // failure_s.top = "fail";
            node failure;
            failure.state_.top = "fail";
			return failure; 
		}
		node currentNode = unvisitedFringe.top();
        unvisitedFringe.pop();
		if (goalTest(currentNode.state_)) return currentNode; 
		else{
			for(int i = 0; i < actions.size(); i++)
				unvisitedFringe.push(successor(currentNode.state_, actions[i]));
		}
	}
}



int main(){
    cout << "start of program" << endl; 
    
    node init_n;
    state init_s;
    vector<string> actions;
 
    cout << "Please pass in the actions in format: TOP_OF_DOMINO,BOTTOM_OF_DOMINO" << endl;
    cout << "type DONE when you are done applying actions" << endl;

    string temp;
    cin >> temp;
    do{
        actions.push_back(temp);
        cin >> temp;
    } while (temp != "DONE");

    cout << "actions are:" <<endl;
    for(int i = 0; i < actions.size(); i++){
        cout << actions[i] << ";";
    }
    cout << endl;

    cout << "Please enter the initial top of the domino" << endl;
    cin >> init_s.top;
    cout << "Please enter the initial bottom of the domino" << endl;
    cin >> init_s.bottom;

    init_n.state_ = init_s;
    init_n.action = "";
 
    // node solution1 = fringeManipulationBFS(init_n, actions);
    // if(solution1.state_.top != "fail"){
    //     cout << "found a solution: " << endl;
    //     cout << "top: " << solution1.state_.top << " bottom: " << solution1.state_.bottom << endl;
    // }
    
    node solution2 = fringeManipulationDFS(init_n, actions);
    if(solution2.state_.top != "fail"){
        cout << "found a solution: " << endl;
        cout << "top: " << solution2.state_.top << " bottom: " << solution2.state_.bottom << endl;
    }
}