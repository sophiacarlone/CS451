//Sophia Carlone
//AI - HW1

//generic structure header

#ifndef GENERIC_STRUCTURES_HPP
#define GENERIC_STRUCTURES_HPP

std::struct{
    bool initial; //is it the initial state?
    std::string name; //name of the state   
}state;

std::struct{
    state state; //current state
    state* parent; //parent node
    std::string action; //what action generated the state
}node;

#endif