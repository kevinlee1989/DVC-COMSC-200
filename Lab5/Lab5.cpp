#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SortableBag.h"

using namespace std;

int main()
{
    const int bagSize = 25;
    SortableBag<int> Bag(bagSize);
    srand(time(0)); rand();
    for(int i =0; i < bagSize; i++){
        int item = 1 + rand() % 100;
        Bag.add(item);
    }

    cout << "Before sorting, the bag contains 25 items." << endl << endl;
    Bag.printBag();
    cout << endl <<  "After sorting, the bag contains 25 items." <<endl << endl;
    Bag.sort();
    Bag.printBag();
    cout << endl;

    if(Bag.verify()){
        cout << "Sorting verification passed" << endl;
    }
    else{
        cout << "Sorting verification failed" << endl;
    }

    return 0;
}
