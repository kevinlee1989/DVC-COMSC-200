//Lab #7 - Using STL Maps
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    ifstream f("trees.txt");
    string tid, addr;

    //Declare the maps
    map<int,string>idmap;
    map<string,int>addrmap;

    if (!f.good()){
        cerr << "Bad file" << endl;
        return -1;
    }

    //load the map
    while(true){
        getline(f, tid);
        if(f.eof()){
            break;
        }

        // Get the address
        getline(f, addr);

        //Insert into the maps here
        idmap.insert(make_pair(stoi(tid), addr));
        addrmap.insert(make_pair(addr,stoi(tid)));

    }

    /*cout << "idmaps contains " << idmap.size() << " entries" << endl;
    cout << "addrmap contains " << addrmap.size() <<" entries" << endl;
    cout << "The value associated with 35445 is: " << idmap[35445] << endl;
    int number = addrmap["73 Summer St"];
    cout << "The value associated with 782 43rd Ave is: " << number << endl;*/

    // The menu loop here
    while(true){
        int userChoice;
        int userTreeId;


        cout << "Menu: " << endl;
        cout << "1. Find tree address by ID." << endl;
        cout << "2. Find tree ID by address." << endl;
        cout << "3. Exit." << endl;
        cout << "Your choice: ";
        cin >> userChoice;
        cin.ignore();

        if(userChoice == 1){
            cout << "Enter the tree ID: ";
            cin >> userTreeId;

            //if not found
            if(idmap.find(userTreeId) == idmap.end()){ // .find() function returns an iterator pointing to the end of the map.
                    cout << "Invalid entry, not found" << endl << endl;
            }
            else{
            cout << "The address of this tree is: " << idmap[userTreeId] << endl << endl;
            }
        }
        else if(userChoice == 2){
            string userAddress;
            cout << "Enter the address: ";
            getline(cin,userAddress);

            // if not found
            if(addrmap.find(userAddress) == addrmap.end()){ // .find() function returns an iterator pointing to the end of the map.
                cout << "Invalid entry, not found" << endl << endl;
            }
            else{
            int number = addrmap[userAddress];
            cout << "The Id of this tree is: " << number << endl << endl;
            }

        }
        else if(userChoice == 3){
            cout << "Exiting..." << endl;
            break;
        }
        else{
            cout <<"Not valid answer, please answer again" << endl;
        }

    }
    return 0;
}
