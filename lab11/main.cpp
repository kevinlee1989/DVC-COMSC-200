#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
using namespace std;
//
// This file provides a starting point for Lab #11.  It reads the
// input file (.csv), builds a graph from the adjacencies in the file,
// and will print the friends list for any node requested.
//
// The graph is a simple adjacency list format -- each node (struct Person)
// contains a string vector of all of its friend nodes.
//
#define IS_QUIT(s) (s == "X" || s == "x")
#define FILENAME "facebook.csv"
using namespace std;

//basic vertex, bunch of people connected together.
struct Person {
    vector<string> friends;// each vertex is each Person, not vector of person but vector of name.
};

//just taking the string and breaking it up
void parse_line(const string &str,
        vector<string> &line) {
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ',')) {
        line.push_back(tmp);
    }
}

bool DFS(map<string, Person> &everyone,
         map<string, bool> &visited, Person startPerson, string end){

    //Loop through the friends of this person
    for(int i = 0 ; i < startPerson.friends.size(); i++){
        // Examine this friend
        string currentFriend = startPerson.friends[i];


        if(currentFriend == end){
            return true;
        }
        // Mark this friend as visited
        visited[currentFriend] = true;

        // This friend has been visited, skip
        // This will stop the search
        if(visited[currentFriend] == false){
            if(DFS(everyone, visited, startPerson, end) == true){
                return true;
            }
        }

    }

    // If there is no name
    return false;

}

int main() {
    ifstream inFile(FILENAME);
    vector<string> row;
    vector<string> names;
    map<string, Person> everyone;
    string inputLine;
    Person p;
    // Verify that the file open was OK
    if (!inFile.good()) {
        cerr << "Invalid file." << endl;
        return (-1);
    }
    // Read the header line of the file (first line, contains column labels).
    // We save this line (names) so we can lookup the string names in the
    // below loop.
    getline(inFile, inputLine);
    parse_line(inputLine, names);
    // Reach each subsequent entry
    while (getline(inFile, inputLine)) {
        if (inFile.eof())
            break;
        vector<string> row; //going to read a row

        parse_line(inputLine, row);
        // Start at 1 (0th field is the string name)
        for (size_t i = 1; i < row.size(); i++) {
            int adj_status = atoi(row[i].c_str());
            // A '1' indicates an adjacency, so skip if we get a '0'
            // If there is an adjacency to this person, push the string name
            // of that person on the adjacency list.
            if (adj_status != 0)
                p.friends.push_back(names[i]);
        }

        // Add this (new) person to the map.
        // In this map, the key is the string name of the person, and
        // the value is their Person structure (adjacency list).

            everyone.insert(make_pair(row[0], p));

    }

    for (;;) {
        string begin; // Starting friend
        string end;     // Ending friend (key for the serach


        cout << endl << "Enter the starting name "
             << "(X to quit): ";
        getline(cin, begin);
        if (IS_QUIT(begin))
            break;
        // Look up the adjacency list of this person in the map
        if (everyone.count(begin) == 0) {
            cout << "That person is not in the map." << endl;
            continue;
        }
        Person this_person = everyone[begin];

        // Keep track of visited nodes
        map<string, bool> visited;
        cout << endl << "Enter the ending name(X to quit): ";
        getline(cin, end);
        if (everyone.count(end) == 0) {
            cout << "That person is not in the map." << endl;
            continue;
        }
        for(auto x:everyone){
            visited[x.first] = false;
        }

        if(DFS(everyone, visited, this_person, end) == true){
            cout << "There IS a path between these two people" << endl;
        }
        else{
            cout << "There is NOT a path between these two people." << endl;
        }


        // Output all their friends
        //cout << inputLine << " is friends with: " << endl;
        //for (size_t i = 0; i < this_person.friends.size(); i++) {
        //    cout << "\t" << this_person.friends[i] << endl;
        //}
    }
    cout << "Exiting..." << endl;
    return (0);
}
