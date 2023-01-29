
#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

#include "myHeap.h"

using namespace std;

int main()
{

    srand(time(0));

    myHeap<int> heap3; // Creating the new heap.

    // Create an temporary array of size 10
    int array[10], array2[10];
    string empty1, empty2;

    for(int i = 0; i < 10; i++){ // Allocating the random value to the array
        int randomNumber = 1 + (rand() % 100);
        array[i] = randomNumber;
    }

    myHeap<int> heap(array, 10);

    //print existing array test
    cout << "Existing Array Test" << endl;
    cout << "-----------------" << endl;
    //print random array
    cout << "Random Array:" << endl;
    for(int number = 0; number < 10; number++){
        cout << array[number] << " ";
    }
    if(heap.isEmpty() == 0){
        empty1 = "FALSE";
    }
    else{
        empty1 = "TRUE";
    }

    //print number of nodes
    cout << endl << "Number of nodes: (isEmpty() is " << empty1 << ")" << endl;
    int number1 = heap.getNumberOfNodes();
    cout << "  " << number1 << endl;
    cout << "10 PeekTops/Removes:" << endl;

    for(int i = 0; i < 10; i++){
        cout << heap.peekTop() << " ";
        heap.remove();
    }
    heap.isEmpty();

    //print initial heap
    cout << endl << endl << "Starting with empty heap" << endl;
    cout << "------------------------" << endl;

    //print random array
    cout << "Random array:" << endl;
    for(int i = 0; i < 10; i++){
        int tempNumber = 1 + (rand() % 100);
        array2[i] = tempNumber;
        cout << array2[i] << " ";
    }


    //check whether heap is empty or not
    if(heap3.isEmpty() == 0){
        empty2 = "FALSE";
    }
    else{
        empty2 = "TRUE";
    }
    int number2 = heap3.getNumberOfNodes();

    //print number of nodes
    cout << endl << "Number of nodes: (isEmpty() is " << empty2 << ")" << endl;
    cout << "   " << number2 << endl;

    cout << "10 PeekTops/Removes:" << endl;
    // add array values to the heap3
    for(int temp = 0; temp < 10; temp++){
        heap3.add(array2[temp]);
    }

    //remove the number from the random array
    for(int i = 0; i < 10; i++){
        cout << heap3.peekTop() << " ";
        heap3.remove();
    }
    return 0;
}
