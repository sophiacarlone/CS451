/* IMPORTANT:
for github purposes, I should say that most of the code is not mine, but was given by the teacher.
All I did was modify heuristic 2 to be the one I thought
*/


#include <iostream>
#include <queue>
//#include <string>
#include <vector>
#include <stack>
using namespace std;

class Found_state; //QUESTION: Do I need to do this?

// Print a pile of cards
void print_pile(vector<int> p)
{
    cout << "[";
    if (p.size() > 0)
        cout << p[0];
    for (int i=1; i<p.size(); i++)
        cout << "," << p[i];
    cout << "]";
}

// Print a bunch of piles of cards
void print_piles(vector<vector<int>> ps)
{
    for (int i=0; i<ps.size(); i++)
    {
        cout << " ";
        print_pile(ps[i]);
    }
}

// State of free cell problem
class State
{
    private:
        int counter;  // what goes next in discard pile
        vector<vector<int>> piles;  // all piles, top card is last in pile
        int heuristic;

        // used for heuristic 2
        int above_big();

    public:
        // Constructors 
        State(int c, vector<vector<int>> p, int heur) {counter = c; piles = p; heuristic = heur;}
        State() {counter = 0; piles = vector<vector<int>>(); heuristic = 0;}

        // find all successor states and action that creates it
        vector<Found_state> find_successors();

        // Problem is solved when discard pile is 0
        bool goal_test() {return counter == 0;}

        // Print the state
        void print() {cout << counter << " "; print_piles(piles);}

        // Heuristic
        int h() {if (heuristic == 2) return above_big(); else if (heuristic == 1) return counter; else return 0;} 
        //Heuristic one here is the counter
        //Heurisitc two has to be dominating. Changing his "above_big" to my heuristic for practice

        bool operator==(State s);
};

int State::above_big()
{
    int total = 0; //this is so that if the wanted number is on top of the pile, it will read a distance of zero
    bool found = false;

    for(int i = 0; i < piles.size(); i++){ //piles is a vector
        if(piles[i].size() > 0){
            for(auto it = piles[i].rbegin(); it != piles[i].rend(); it++){
                total++; 
                if(*it == counter){
                    found = true;
                    break;
                }
            }
        }
        if(found) break;
        total = 0;
    }

    /* Teacher's heuristic 2
    for (int i=0; i<piles.size(); i++)
    {
        if (piles[i].size() > 0)
        {
            int max_index = 0;
            for (int j=1; j<piles[i].size(); j++)
            {
                if (piles[i][j] > piles[i][max_index])
                    max_index = j;
            }
            total += piles[i].size() - max_index - 1;
        }
    }
    */
    return total + counter;
}

bool State::operator==(State s)
{
    if (counter != s.counter)
    {   
        //cout << "Different counter " << endl;
        return false;
    }
    if (piles.size() != s.piles.size())
    {   
        //cout << "Different size " << endl;
        return false;
    }
    for (int i=0; i<piles.size(); i++)
    {
        if (piles[i].size() != s.piles[i].size())
        {   
            //cout << "Different individual size " << endl;
            return false;
        }
        for (int j=0; j<piles[i].size(); j++)
        {
            //cout << "Same value: " << piles[i][j] << " " << s.piles[i][j] << endl;
            if(piles[i][j] != s.piles[i][j])
            {   
                //cout << "Different value: " << piles[i][j] << " " << s.piles[i][j] << endl;
                return false;
            }
        }
    }
    return true;
}

// Contains state and other informaion
// Used by find_successors
// Added 2 additional fields for astar
struct Found_state
{
    State new_state;  // new state found
    string action_applied;  // action applied to get state
    int step_cost;  // Cost of the action
    int h_value;  // h-value of new state

    Found_state(State s, string a, int sc, int h) 
      {new_state = s; action_applied = a; step_cost = sc, h_value = h;}
    Found_state() 
      {new_state = State(); action_applied = ""; step_cost = 0, h_value = 0;}
};

// Returns all the successors of a state
//
// for all piles p
//   if pile p is not empty
//      let top be top card in p
//      if top == counter then create a successor which discards top
//      for all piles q
//        if q is empty
//          add succcessor which moves top to q
//        else it top card of q < top
//          add successor which moves top to q
// return all successors added 
vector<Found_state> State::find_successors()
{
    vector<Found_state> succs; // all successors and associated values
    Found_state to_be_added;  // a single successor with associated values

    for (int i=0; i<piles.size(); i++)  // for all piles p
    {
        if (!piles[i].empty())  // if p is empty
        {
            int top = piles[i].back();  // let top be top card in p
            if (top == counter)
            {
                State s = *this;  // let s be a copy of current state
                s.counter--;  // decrement counter in s
                s.piles[i].pop_back();  // remove top from current pile
                to_be_added = Found_state(s,"Discard " + to_string(top) + " from pile " + to_string(i), 1,s.h());
                succs.push_back(to_be_added);  // add new state to succs
            }
            for (int j=0; j<piles.size(); j++)  // for all piles q
            {
                if (piles[j].empty())  // if q is empty 
                {
                    State s = *this;  // let s be a copy of current state
                    s.piles[j].push_back(top);  // add top to pile q
                    s.piles[i].pop_back();  // remove top from pile p
                    to_be_added = Found_state(s,"Move " + to_string(top) + " from pile " + to_string(i) + " to empty pile " + to_string(j), 1,s.h());
                    succs.push_back(to_be_added);  // add to succs
                }
                else if (piles[j].back() < top)  // else it top of pile q < top
                {
                    State s = *this;  // let s be a copy of current state
                    s.piles[j].push_back(top);  // put top on top of q
                    s.piles[i].pop_back();  // remove top from p
                    to_be_added = Found_state(s,"Move " + to_string(top) + " from pile " + to_string(i) + " to pile " + to_string(j), 1,s.h());
                    succs.push_back(to_be_added);  // add to succs
                }
            }
        }
    }  
    return succs;
}     

// Same as for bfs and dfs
// except we save more fields
struct Node
{
    State current_state;  // current state
    Node *parent;  // pointer to node that leads to here
    string action;  // action that leads to here
    int num_successors;  // number of active successors
    int step_cost;  // stop cost of action
    int path_cost;  // total path cost
    int h_value;  // h-value of state
    
    Node(State s, Node *p, string a, int pc, int h) {current_state = s; parent = p; action = a; num_successors = 0; path_cost = pc, h_value = h;}
    Node() {current_state = State(); parent = NULL; action = ""; num_successors = 0; path_cost = 0, h_value = 0;}
    ~Node();
    void print_solution();

    // f-value = g-value + h-value
    int f() {return path_cost + h_value;}

};

Node::~Node()
{
    //cout << "Deleting " << endl;

    if (parent != NULL)
    {
        (parent -> num_successors) --;
        if (parent -> num_successors == 0)
            delete parent;
    }
}

void Node::print_solution()
{
    if (parent != NULL)
    {
        parent -> print_solution();
        cout << "  Perform action [" << action << "] to get state below with path cost " << path_cost << " and heuristic " << h_value << endl;
        current_state.print();
    }
    else
    {
        cout << "Initial state: " << endl;
        current_state.print();
    }
}

// This Compare class is used for priority queue
// So we can always select smallest f-value
class Compare
{
public:
    bool operator() (Node *np1, Node *np2)
    {
        return np1->f() > np2->f();
    }
};

bool in_path(State s, Node *np)
{
    //s.print();
    //cout << endl;
    //np->current_state.print();
    //cout << endl;

    if (s == np->current_state)
        {
            //cout << "Equal " << endl;
            return true;
        }
    if (np->parent == NULL)
    {   //cout << "Not equal " << endl;
        //char c;
        //cout << "Enter any character to continue: ";
        //cin >> c;
        return false;
    }
    //cout << "Calling parent " << endl;
    return in_path(s,np->parent);
}

// astar is same as bfs and dfs
// except we use a priority queue, always selecting smallest f-value
// and we need to handle additional fields in node
int astar(State initial, bool is_graph)
{     
    priority_queue<Node*, vector<Node*>, Compare> fringe;  

    Node *np = new Node(initial,NULL,"",0,initial.h());
    fringe.push(np);
    int states_expanded = 0;

    while (!fringe.empty())
    {
        np = fringe.top();
        fringe.pop();
        State s = np -> current_state;
        
        if (s.goal_test())
        {
            cout << "Found solution:  ";
            cout << endl;
            np  -> print_solution();
            return states_expanded;
        }
        
        // Uncomment to see expanded states
        //cout << "Expanding state with path cost " << np -> path_cost << " and heuristic " << np -> h_value << ":  ";
        //(np -> current_state).print(); 
        //cout << endl;
        states_expanded++;
        if (states_expanded % 100000 == 0)
            cout << states_expanded << " ";

        vector<Found_state> succs = s.find_successors();

        int num_succs = 0;
        for (int i=0; i<succs.size(); i++)
        {
            //cout << "Calling in_path " << endl;
            if (!is_graph || !in_path(succs[i].new_state,np))
            {
                num_succs++;
                Node *np_new = new Node(succs[i].new_state,np,succs[i].action_applied,np->path_cost+succs[i].step_cost,succs[i].h_value);  
                fringe.push(np_new); 
            }
        }

        np -> num_successors = num_succs;
        if (np -> num_successors == 0)
        {
            delete np;
        }
    }
    cout << "There is no solution" << endl;
    return states_expanded;
}

// Same as before, except node has some additional fields
int bfs(State initial)
{    
    queue<Node*> fringe;
    Node *np = new Node(initial,NULL,"",0,initial.h());
    fringe.push(np);
    int states_expanded = 0;

    while (!fringe.empty())
    {
        np = fringe.front();
        fringe.pop();
        State s = np -> current_state;
        
        if (s.goal_test())
        {
            cout << "Found solution:  ";
            cout << endl;
            np  -> print_solution();
            return states_expanded;
        }
        
        // Uncomment to see expanded states
        //cout << "Expanding state " << endl;
        //(np -> current_state).print(); 
        states_expanded++;

        vector<Found_state> succs = s.find_successors();
        np -> num_successors = succs.size();
        for (int i=0; i<succs.size(); i++)
        {
            Node *np_new = new Node(succs[i].new_state,np,succs[i].action_applied,np->path_cost+succs[i].step_cost,succs[i].h_value);  
            fringe.push(np_new); 
        }
        if (np -> num_successors == 0)
        {
            delete np;
        }
    }
    cout << "There is no solution" << endl;
    return states_expanded;
}

// Same as before, except node has some additional fields
int dfs(State initial)
{    
    stack<Node*> fringe;
    Node *np = new Node(initial,NULL,"",0,initial.h());
    fringe.push(np);
    int states_expanded = 0;

    while (!fringe.empty())
    {
        np = fringe.top();
        fringe.pop();
        State s = np -> current_state;
        
        if (s.goal_test())
        {
            cout << "Found solution:  ";
            cout << endl;
            np  -> print_solution();
            return states_expanded;
        }
        
        // Uncomment to see expanded states
        // cout << "Expanding state " << endl;
        //  (np -> current_state).print();
        states_expanded++; 

        vector<Found_state> succs = s.find_successors();
        np -> num_successors = succs.size();
        for (int i=0; i<succs.size(); i++)
        {
            Node *np_new = new Node(succs[i].new_state,np,succs[i].action_applied,np->path_cost+succs[i].step_cost,succs[i].h_value); 
            fringe.push(np_new); 
        }

        if (np -> num_successors == 0)
        {
            delete np;
        }
    }
    cout << "There is no solution" << endl;
    return states_expanded;
}

int main()
{
    // Cards will be numbered 1 - count, and first discard must equal count
    int count;  
    vector<int> pile;  // a single pile
    vector<vector<int>> piles;  // all piles
    bool done = false;  // done reading in input
    cout << "How many numbers? ";
    cin >> count;
    cout << "Give me your piles, end a pile with 0, -1 to stop: " << endl;
    int i;  // current card
    cin >> i;
    while (!done)
    {
        while (i != 0)  // 0 indicates end of pile
        {   
            pile.push_back(i);  // add i to pile
            cin >> i;
        }
        piles.push_back(pile);  // pile is finished so add to piles
        pile.clear();  // empty current pile to start again
        cin >> i;
        if (i == -1)  // -1 indicates end of input
        {
            done = true;
        }
    }

    string search_type;
    cout << "What kind of search do you want to do? ";
    cin >> search_type;

    string search_rule;
    cout << "Tree or graph? ";
    cin >> search_rule;
    bool is_graph;
    if (search_rule == "graph")
        is_graph = true;
    else 
        is_graph = false;
    int heuristic;
    cout << "Which heuristic will you use? ";
    cin >> heuristic;

    State s = State(count,piles,heuristic);  // create initial state
    int num;  // number of states expanded
    if (search_type == "dfs")
    {
        cout << "Running tree search " << endl;
        num = dfs(s);
    } 
    else if (search_type == "bfs")
    {   
        cout << "Running tree search " << endl;
        num = bfs(s);
    }
    else 
        num = astar(s,is_graph);
    cout << "Expanded " << num << " states " << endl;

    return 0;
}


