#include <iostream>
#include <queue>
//#include <string>
#include <vector>
#include <stack>
using namespace std;

bool intersect(vector<pair<int,int>> c, pair<int,int> spot);
bool intersect(vector<pair<int,int>> c1, vector<pair<int,int>> c2);
bool in_grid(vector<pair<int,int>> car, int n);
int distance(vector<pair<int,int>> car, pair<int,int> spot);

class Found_state;

// A car is a vector of (x,y) pairs
// Either all x-values are the same, and the y are successive
//  or all the y are the same and the x are successive
void print_car(vector<pair<int,int>> c)
{
    cout << "[(" << c[0].first << "," << c[0].second << ")";
    for (int i=1; i<c.size(); i++)
        cout << " (" << c[i].first << "," << c[i].second << ")";
    cout << "]";
}

// Print a vector of cars
// Put * after first car because it is yours
void print_cars(vector<vector<pair<int,int>>> cs)
{
    print_car(cs[0]);
    cout << "*";
    for (int i=1; i<cs.size(); i++)
    {
        cout << " ";
        print_car(cs[i]);
    }
}

// Read in a vector of cars
void read_cars(vector<vector<pair<int,int>>> &cs)
{   
    pair<int,int> p;
    vector<pair<int,int>> c; 
    cin >> p.first >> p.second;
    while (p.first != -1)
    {
        c.clear();
        while (p.first != 0)
        {
            c.push_back(p);
            cin >> p.first >> p.second;
        }
        cs.push_back(c);
        cin >> p.first >> p.second;
    }
}

// State of Parking problem
class State
{
    private:
        // number of rown and columns will be from 1 to grid_size
        int grid_size;  

        // The goal (x,y) coordinates
        pair<int,int> goal;  

        // Vector of all cars, yours is first, index 0
        vector<vector<pair<int,int>>> cars;  

        int heuristic;

        // True if car j is on same spot as some car in vector
        bool intersect_some(vector<pair<int,int>> car, int j); 

        // Replaces old car with new car in vector
        void update_state(vector<pair<int,int>> old_car, vector<pair<int,int>> new_car);

        // Used for heuristic 2
        int num_block();

    public:
        // Constructors
        State(int gs, vector<vector<pair<int,int>>> cs, pair<int,int> g, int heur) 
          {grid_size = gs; cars = cs; goal = g; heuristic = heur;}
        State() 
          {grid_size = 0; cars = vector<vector<pair<int,int>>>(); goal = make_pair(0,0); heuristic = 0;}

        // Returns all successor states  
        vector<Found_state> find_successors();

        // True if your car is at goal
        bool goal_test() {return intersect(cars[0],goal);}

        // Print all cars
        void print() {print_cars(cars);}

        // Heuristic
        int h() {if (heuristic ==1) 
                   return distance(cars[0],goal); 
                else if (heuristic == 2)
                    return num_block();
                else 
                    return 0;}

        bool operator==(State s);
};

bool State::operator==(State s)
{
    for (int i=0; i<cars.size(); i++)
    {
        for (int j=0; j<cars[i].size(); j++)
        {
            if (cars[i][j].first != s.cars[i][j].first)
                return false;
            if (cars[i][j].second != s.cars[i][j].second)
                return false;
        }
    }
    return true;
}

// Same as free cell
struct Found_state
{
    State new_state;
    string action_applied;
    int step_cost;
    int h_value;

    Found_state(State s, string a, int sc, int h) 
      {new_state = s; action_applied = a; step_cost = sc, h_value = h;}
    Found_state() 
      {new_state = State(); action_applied = ""; step_cost = 0, h_value = 0;}
};

// True if Car c touches spot 
bool intersect(vector<pair<int,int>> c, pair<int,int> spot)
{
    for (int i=0; i<c.size(); i++)  // for all positions in car c
    {
        // both coordiates of position of car and spot are identical
        if (c[i].first == spot.first && c[i].second == spot.second)
            return true;
    }
    return false;
}

// True if c1 and c2 share a common position
bool intersect(vector<pair<int,int>> c1, vector<pair<int,int>> c2)
{
    for (int i=0; i<c2.size(); i++)  // for all positions in c2
    {
        if (intersect(c1,c2[i]))  // if car c1 is in c2 position
            return true;
    }
    return false;
}

// True if Car j is on same spot as some car in list
bool State::intersect_some(vector<pair<int,int>> car, int j)
{
    for (int i=0; i<cars.size(); i++)  // for all cars in list
    {
        // Check that car is is on same position as car j and they
        // are not the same car in list
        if (intersect(car,cars[i]) && i != j)  
            return true;
    }
    return false;
}

// True if car is within the grid
bool in_grid(vector<pair<int,int>> car, int n)
{ 
    return (car.front().first >= 1 && car.front().first <= n
              && car.front().second >= 1 && car.front().second <= n
              && car.back().first >= 1 && car.back().first <= n
              && car.back().second >= 1 && car.back().second <= n);
}

// Distance of car to a spot
// I consider last position in car to be fron of car
// Which is weird, because back function returns front position
int distance(vector<pair<int,int>> car, pair<int,int> spot)
{
    if (car.back().second == spot.second) // second postion of back the same
    {
        // absolute value of difference of first position
        return abs(car.back().first - spot.first);  
    }
    else  // vice versa
    {
        return abs(car.back().second - spot.second);
    }
}

int State::num_block()
{
    int blocks = 0;
    if (cars[0].back().second == goal.second) // second postion of back the same
    {
        for (int i=0; i<cars.size(); i++)
        {
            for (int j=cars[0].back().first+1; j<goal.first; j++)
            {
                if (intersect(cars[i],make_pair(j,goal.second)))
                    blocks++;
            }
        }
    }
    else
    {
        for (int i=0; i<cars.size(); i++)
        {
            for (int j=cars[0].back().second+1; j<goal.second; j++)
            {
                if (intersect(cars[i],make_pair(j,goal.first)))
                    blocks++;
            }
        }
    }
    return blocks + distance(cars[0],goal);
}

// REplace old car with new car in list
void State::update_state(vector<pair<int,int>> old_car, vector<pair<int,int>> new_car)
{
    for (int i=0; i<cars.size(); i++)
    {
        if (cars[i] == old_car)
            cars[i] = new_car;
    }
}

// Return all successors of state
vector<Found_state> State::find_successors()
{
    vector<Found_state> succs;
    Found_state to_be_added;  
    State s;

    for (int i=0; i<cars.size(); i++)  // for all cars
    {
        vector<pair<int,int>> c = cars[i]; // let c be car i
        vector<pair<int,int>> new_car;  // will create new position for c
        if (c[0].second == c[1].second)  // this means the first coordinate is chainging
        {
            new_car = c;  // copy c to new car
            // Add a new position at one end of car
            new_car.push_back(make_pair(c.back().first+1,c.back().second));
            // Delete a positon from other end of car
            new_car.erase(new_car.begin(),new_car.begin()+1);
            // Check if car is in grid and not intersecting with another car
            if (in_grid(new_car,grid_size) && !intersect_some(new_car,i))
            {
                s = *this;  // copy state
                s.update_state(c,new_car);  // replace old car by new car
                to_be_added = Found_state(s,"Move car " + to_string(i) + " forward ", 1,s.h());
                succs.push_back(to_be_added);  // add new state to succs
            }

            // repeat previous logic, moving car in opposite direction
            new_car = c;
            new_car.insert(new_car.begin(),make_pair(c.front().first-1,c.front().second));
            new_car.pop_back();
            if (in_grid(new_car,grid_size) && !intersect_some(new_car,i))
            {
                s = *this;
                s.update_state(c,new_car);
                to_be_added = Found_state(s,"Move car " + to_string(i) + " backward ", 1,s.h());
                succs.push_back(to_be_added);
            }
        }
        else // second coordintate is changing, so repeat above for that case
        {
        new_car = c;
        new_car.push_back(make_pair(c.back().first,c.back().second+1));
        new_car.erase(new_car.begin(),new_car.begin()+1);
            if (in_grid(new_car,grid_size) && !intersect_some(new_car,i))
            {
                s = *this;
                s.update_state(c,new_car);
                to_be_added = Found_state(s,"Move car " + to_string(i) + " forward ", 1,s.h());
                succs.push_back(to_be_added);
            }
        new_car = c;
        new_car.insert(new_car.begin(),make_pair(c.front().first,c.front().second-1));
        new_car.pop_back();
            if (in_grid(new_car,grid_size) && !intersect_some(new_car,i))
            {
                s = *this;
                s.update_state(c,new_car);
                to_be_added = Found_state(s,"Move car " + to_string(i) + " backward ", 1,s.h());
                succs.push_back(to_be_added);
            }
        }
    }
    return succs;
}     

// Identical to Free Cell
struct Node
{
    State current_state;
    Node *parent;
    string action;
    int num_successors;
    int step_cost;
    int path_cost;
    int h_value;
    
    Node(State s, Node *p, string a, int pc, int h) 
      {current_state = s; parent = p; action = a; num_successors = 0; path_cost = pc, h_value = h;}
    Node() 
      {current_state = State(); parent = NULL; action = ""; num_successors = 0; path_cost = 0, h_value = 0;}
    ~Node();
    void print_solution();
    int f() {return path_cost + h_value;}
};

// Identical to Free Cell
Node::~Node()
{
    if (parent != NULL)
    {
        (parent -> num_successors) --;
        if (parent -> num_successors == 0)
            delete parent;
    }
}

// Identical to Free Cell
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

// Identical to Free Cell
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

// Identical to Free Cell
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
        
        // Ucomment to see expanded states
        //cout << "Expanding state with path cost " << np -> path_cost << " and heuristic " << np -> h_value << ":  ";
        //(np -> current_state).print(); 
        states_expanded++;

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

// Identical to Free Cell
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

// Identical to Free Cell
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

int main()
{
    int gs;  // grid will be size gs by gs
    cout << "What is the size of your grid? ";
    cin >> gs;

    vector<vector<pair<int,int>>> cs;  // vector of cars, yours is first
    cout << "Give me cars, yours first, end car with 0 0, end all cars with -1 -1 " << endl;
    read_cars(cs);
    pair<int,int> g;  // goal (x,y) coordinates
    cout << "What is your goal? ";
    cin >> g.first >> g.second;

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

    State s(gs,cs,g,heuristic);  // initial state
    int num; // number of states expanded
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


