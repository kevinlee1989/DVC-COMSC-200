#include <iostream>
#include <fstream>

using namespace std;

struct entry {
    string address; // Holds 1 address
    entry *next; // Next entry in the linked list
};

// The hash table
const int TABLE_SIZE = 997;     // Should be prime
entry *hashTable[997];           // Pointers to linked list
                                 // zeored

// The hash function h(k)
// Where 'k' is a string
// The return value is the index of the hash bucket
int hashit(string key){
    int result = 0;

    // changing the result value to make the better hash function
    //result = key[0];
    //result = key[key.size() -1]
    for (int i =0; i < key.size(); i++){
        result += key[i];
    }

    return (result % TABLE_SIZE);

}


int main()
{
    string tmp;
    int hashIndex = 0;
    int count = 0;

    ifstream inputFile("addresses2.txt");
    if(!inputFile.good()){
        cerr << "File open failed. " << endl;
        return -1;
    }
    cout << "File open succeeded. " << endl;
    while(getline(inputFile, tmp)){
        entry *newEntry = new entry; // Make a new hash entry
        newEntry ->address = tmp;
        newEntry ->next = 0;

        // Find the index into the hash table
        hashIndex = hashit(newEntry -> address); // Calculate the index

        // Find the location into the hash table
        entry *htmp = hashTable[hashIndex];
        if(!htmp){
            // Handle the empty case
            hashTable[hashIndex] = newEntry;
        }
        else{
            // There is at least 1 entry in the bucket
            newEntry -> next = hashTable[hashIndex];
            hashTable[hashIndex] = newEntry;
        }
        count++; // Count the total entries
    }
    cout << "Hashed " << count << " entries." << endl;

    while(true){
        cout << "Enter an address (press Enter to quit): ";
        getline(cin, tmp);


        // Quit if requested
        if(tmp == "")
            break;

        // Find the index in the table
        hashIndex = hashit(tmp);

        // Find the location into the hash table
        entry *findtmp = hashTable[hashIndex];
        if(!findtmp){
            cout << "Not in the table. " << endl;
            continue;
        }
        // There is at least 1 entry in this hash bucket
        int compareCount = 0;
        while(findtmp){
            compareCount++; // Note we went 1 more element down the linked list
            if(findtmp -> address == tmp){
                cout << "Found address, bucket: " << hashIndex << endl;
                break;
            }
            findtmp = findtmp -> next;

        }
        if(!findtmp){
            cout << "That address is not in the table. " << endl;
        }
        cout << "Did :" << compareCount << " compares." << endl;

    }

    cout << "Exiting ......." << endl;

    return 0;
}
