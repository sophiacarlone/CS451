//Sophia Carlone
//AI HW1

//PCP section

#ifndef PCP_HPP
#define PCP_HPP

#include <string>
#include "generic_structures.hpp"

/*successor function
Summary: will find the successor of a state based on an action
Inputs:
    - s (state structure): current state
    - action (string): action modifying current state
Outputs: new state
*/
const state& successor(const state& s, const std::string& action){
    state successorState;
    successorState.name = s.name + action; //Question: dont remember if this works
    successor.initial = false;
    return successorState;
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

#endif