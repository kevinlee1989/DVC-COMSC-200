#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <queue>
#include <stack>
using namespace std;
#define IS_QUIT(s) (s == "X" || s == "x")
#define FILENAME "fb_weighted.csv"
using namespace std;
// A node in the Facebook graph
struct Person {
    int best_weight;        // The sum of the weights along the best path
    string best_parent;     // The parent node for the best path
    vector<string> friends; // String names of the friend edges
    vector<int> weights;    // Weights for each friend edge
};
struct Candidate {
    string name;
    string parent;
    int weight;
    bool operator< (const Candidate &rhs) const {
        return weight > rhs.weight;
    }

};
void parse_line(const string &str,
        vector<string> &line) {
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ',')) {
        line.push_back(tmp);
    }
}
// Output the shortest path
// - everyone:  reference variable to the graph
// - starting:  string name of the starting person
// - ending: string name of the ending person
// Calculate the shortest path.
// - everyone:  reference variable to the graph
// - starting:  string name of the starting person
// - ending: string name of the ending person
bool dijkstra(map<string, Person> &everyone,
    string starting, string ending) {
    priority_queue<Candidate> PQ;
    // Add all of the source's edges into the
    // priority queue
    Person &startingPerson = everyone[starting];
    for (size_t i = 0; i < startingPerson.friends.size(); i++) {
        Candidate c;
        c.name = startingPerson.friends[i];
        c.weight = startingPerson.weights[i];
        c.parent = starting;
        PQ.push(c);
    }
    startingPerson.best_parent = "";
    startingPerson.best_weight = 0;
    while (!PQ.empty()) {
        // Get the next best candidate from TENT
        Candidate nextC = PQ.top();
        PQ.pop();

        // Add this node to PATHS.  PATHS is stored
        // in each Person in the graph
        Person &p = everyone[nextC.name];
        // If this node is already in PATHS, ignore
        // this candidate.  If the node is in PATHS
        // here it means we found a better path prior
        // to this.
        if (p.best_weight != -1)
            continue;
        // Now that this node is in PATHS, we can
        // record the best weight and parent.
        p.best_weight = nextC.weight;
        p.best_parent = nextC.parent;

        if (nextC.name == ending){
            return true;
        }

        for (int i = 0; i < p.friends.size(); i++) {
            Candidate newC;
            newC.name = p.friends[i];
            // Total weight of the path
            newC.weight = p.best_weight +
                p.weights[i];
            newC.parent = nextC.name;
            PQ.push(newC);
        }
    }
    return (false);
}

/*void prim_MST(map<string, Person> everyone, string starting){

    priority_queue<Candidate> PQ;

    // Get the person out of the map( reference)
    Person &startingPerson = everyone[starting];
    startingPerson.best_parent = "";
    startingPerson.best_weight = -1;

    // Add all adjacencies to the priority_queue
    for(int i =0; i< startingPerson.friends.size(); i++){
        // Add this friend to the queue
        Candidate c;
        c.name = startingPerson.friends[i]; // Their name
        c.parent = starting;            // Parent node in shortest path
        c.weight = startingPerson.weights[i];  // The name of the Candidate node

        PQ.push(c);
    }
    while(!PQ.empty()){
        // Get the next entry
        Candidate nextC = PQ.top();

        Person nextP = everyone[nextC.name]; // Get the person struct for the name
        // In this case the node was already in the MST
        if(nextP.best_weight != -1){
            continue;
        }
        // Add this node/dege to the MST
        nextP.best_weight = nextC.weight;
        nextP.best_parent = nextC.parent;

         // Add this node's adjacencies into the PQ
        // Skip if already in the MST
        for(int i =0; i < nextP.friends.size(); i++){
            // Get the Person entry for this friend
            Person friendPerson = everyone[nextP.friends[i]];
            // We've already added this Person to shortest paths
            if (friendPerson.best_weight != -1){
                continue;
            }
                                    //////////////////// missing when do i stop , how to print out the path ////////////////////
            // Add the friend to the priority queue
            Candidate newC;

            // The cost of the new candidate is
            // The cost of the best path to THIS node +
            // the eight of the edge from THIS node to the friend
            //
            newC.weight = nextP.weights[i] + nextP.best_weight; // Weight of this edge
            newC.parent = nextC.name;  // Parent in the MST
            newC.name = nextP.friends[i];   // The name of the candidate node
        }
    }

        // Complete this function -- run the Dijkstra algorithm.
    // Here are the things you'll need:
    // - Some way to track tentative "candidate" nodes (priority queue?)
    // - Process each node just like you did in the MST calculation, except
    //   consider the total path length (cost to this node + cost of edge)
    // - Update the best cost/best parent in the graph when found.
    // - Stop the algorithm when the end node is reached.

    // Compute the MST for a graph
        // Remove the front entry;
        PQ.pop();
}*/

int main() {
    ifstream inFile(FILENAME);
    vector<string> row;
    vector<string> names;
    map<string, Person> everyone;
    string inputLine;
    // Verify that the file open was OK
    if (!inFile.good()) {
        cerr << "Invalid file." << endl;
        return (-1);
    }
    // Read the header line of the file (first line, contains column labels).
    // We save this line (names) so we can lookup the string names when
    // needed.
    getline(inFile, inputLine);
    parse_line(inputLine, names);
    // Reach each subsequent entry
    while (getline(inFile, inputLine)) {
        if (inFile.eof())
            break;
        vector<string> row;
        Person p;
        parse_line(inputLine, row);
        // Start at 1 (0th field is the string name)
        for (size_t i = 1; i < row.size(); i++) {
            int adj_status = atoi(row[i].c_str());
            // A '1' indicates an adjacency, so skip if we get a '0'
            // If there is an adjacency to this person, push the string name
            // of that person on the adjacency list.
            if (adj_status > 0) {
                p.friends.push_back(names[i]);
                p.weights.push_back(adj_status);
            }
            // Initialize the other fields
            p.best_weight = -1;
            p.best_parent = "";
        }
        // Add this (new) person to the map.
        // In this map, the key is the string name of the person, and
        // the value is their Person structure (adjacency list).
        everyone.insert(make_pair(row[0], p));
    }
    // The main loop of the program
    for (;;) {
        // Use this code to explore the graph and weights if needed.  It is
        // left commented out here.
        /*
        cout << endl << "Enter the name and I'll tell you their friends: ";
        getline(cin, inputLine);
        if (IS_QUIT(inputLine))
            break;
        // Look up the adjacency list of this person in the map
        if (everyone.count(inputLine) == 0) {
            cout << "That person is not in the map." << endl;
            continue;
        }
        Person this_person = everyone[inputLine];
        // Output all their friends
        cout << inputLine << " is friends with: " << endl;
        for (size_t i = 0; i < this_person.friends.size(); i++) {
            cout << "\t" << this_person.friends[i] << " (weight "
                 << this_person.weights[i] << ")" << endl;
        }
        */
        string to, from;
        cout << endl << "Enter the starting name (X to quit): ";
        getline(cin, from);
        if (IS_QUIT(from))
            break;
        cout << endl << "Enter the ending name (X to quit): ";
        getline(cin, to);
        if (IS_QUIT(to))
            break;
        if (everyone.count(from) == 0 || everyone.count(to) == 0) {
            cout << "One or more people is not in the map." << endl;
            continue;
        }


        // Run the calculation
        if (dijkstra(everyone, from, to)) {
            cout << "The best path between these two people is: " << endl;
            // Construct the path from the parents stored
            // Output the path in reverse
            Person endPerson = everyone[to];
            stack<string> path;
            int cost = endPerson.best_weight;
            path.push(to);

            while(true){
                // Get the parent of this node
                string parent = endPerson.best_parent;

                // Push this name on the stack
                // Get the person struct for this parent
                endPerson = everyone[parent];
                path.push(parent);

                if (parent == from){
                    break;
                }
            }
            while(!path.empty()){ // Check to see if this is the end
                cout << "        " << path.top() << endl;
                path.pop();

            }
            cout << "The cost of this path is: " << cost << endl;
            } else {
                cout << "There is NOT a path between these two people." << endl;
            }
        // Clean up all the state
        for (auto i = everyone.begin(); i != everyone.end(); i++) {
            Person &p = i->second;
            p.best_weight = -1;
            p.best_parent = "";
        }
    }
    cout << "Exiting..." << endl;
}
