//myHeap.h
#ifndef MY_HEAP_
#define MY_HEAP_

#include <algorithm>
#include <iostream>
using namespace std;

template<class ItemType>
class myHeap {
    private:
    // Defining the ROOT node
    static const int ROOT = 0;
    // Start with a small default size
    static const int DEFAULT_CAPACITY = 24;
    ItemType *items;

    int itemCount; // Current count of heap items
    int maxItems; // Maximum capacity of the heap

    // Returns the array index of the left child (if exists).
    int getLeftChildIndex(const int nodeIndex) const;

    // Returns the array index of the right child (if exists).
    int getRightChildIndex(int nodeIndex) const;

    // Returns the array index of the parent node.
    int getParentIndex(int nodeIndex) const;

    // Returns whether there is a child or not.
    bool isLeaf(int nodeIndex) const;

    // Converts a semi heap to a heap.
    void heapRebuild(int nodeIndex);

    // Creates a heap from an unordered array.
    void heapCreate();

    public:
    myHeap();
    myHeap(const ItemType someArray[], const int arraySize);
    ~myHeap();

    // HeapInterface Public Methods:
    bool isEmpty() const;
    int getNumberOfNodes() const;

    ItemType peekTop() const;
    bool add(const ItemType& newData);
    bool remove();
    void clear();
};

// Given a nodeIndex, return its LEFT child index.  If the return
// value of this function is greater than or equal to itemCount, there is
// no left child (the node is a leaf).
template<class ItemType>
int myHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const {
    return (2 * nodeIndex) + 1;
}


// Given a nodeIndex, return its PARENT index.
template<class ItemType>
int myHeap<ItemType>::getParentIndex(const int nodeIndex) const {
    return (nodeIndex - 1) / 2;
}

// To determine the node has the right or left child
// These are complete tress so we can know only comparing the only left child.
template<class ItemType>
bool myHeap<ItemType>::isLeaf(const int nodeIndex) const {
    return (getLeftChildIndex(nodeIndex) >= itemCount);
}
// Given a nodeIndex, return its RIGHT child index.  Our array-based
// format implies that if a node has a right child, it must already have
// a left child.
template<class ItemType>
int myHeap<ItemType>::getRightChildIndex(const int nodeIndex) const {
    return (2 * nodeIndex) + 2;
}

// Given a subheap rooted at index subTreeNodeIndex, rebuild the nodes
// so a heap is formed.
template<class ItemType>
    void myHeap<ItemType>::heapRebuild(const int subTreeNodeIndex) {
    if(!isLeaf(subTreeNodeIndex)){ // if there is a child node doing swap and do it again

        int leftChildIndex = getLeftChildIndex(subTreeNodeIndex);

        int largerChildIndex = leftChildIndex;

        int rightChildIndex = getRightChildIndex(subTreeNodeIndex);

        if(rightChildIndex < itemCount){
            if(items[rightChildIndex] > items[largerChildIndex])
                largerChildIndex = rightChildIndex;
        }
        if(items[subTreeNodeIndex] < items[largerChildIndex]){
            swap(items[largerChildIndex], items[subTreeNodeIndex]);
            heapRebuild(largerChildIndex);
        }
    }
}

// Rebuild the entire heap.  This is the 'bottom up' algorithm.
template<class ItemType>
void myHeap<ItemType>::heapCreate() {
    for (int index = itemCount / 2; index >= 0; index--) {
        heapRebuild(index);
    }
}

// Constructor that accepts an existing array
template<class ItemType>
myHeap<ItemType>::
myHeap(const ItemType someArray[], const int arraySize):
itemCount(arraySize), maxItems(2 * arraySize) {

    items = new ItemType[2 * arraySize];
    for(int i = 0; i < itemCount; i++)
        items[i] = someArray[i];
    heapCreate();
}

// Default constructor
template<class ItemType>
myHeap<ItemType>::myHeap(): itemCount(0),
maxItems(DEFAULT_CAPACITY) {
    items = new ItemType[DEFAULT_CAPACITY];
}

// Default destructor
template<class ItemType>
myHeap<ItemType>::~myHeap() {
    delete[] items;
}

// Return whether the heap is empty
template<class ItemType>
bool myHeap<ItemType>::isEmpty() const {
    return itemCount == 0;
}

// Return the total number of nodes
template<class ItemType>
int myHeap<ItemType>::getNumberOfNodes() const {
    return itemCount;
}

// Remove the root of the heap and rebuild it
template<class ItemType>
bool myHeap<ItemType>::remove() {
    bool result = false;

    if(!isEmpty()){
        items[ROOT] = items[itemCount-1]; // taking out the original root node
        itemCount--; // decrement the amount of size
        heapRebuild(ROOT); // rebuild the heap with the new root
        result = true;
    }
    return result;
}

// Clear all items (note we do not resize the array here).
template<class ItemType>
void myHeap<ItemType>::clear() {
    itemCount = 0;
}

// Return the value at the root of the heap
template<class ItemType>
ItemType myHeap<ItemType>::peekTop() const {
    return items[0];
}

// Add a new item to the heap
template<class ItemType>
bool myHeap<ItemType>::add(const ItemType& newData) {

    bool result = false;

    if(itemCount < maxItems){
        items[itemCount] = newData;

        bool inIndex = false;

        int newDataIndex = itemCount;

        while((newDataIndex > 0) && !inIndex){
            int parentIndex = getParentIndex(newDataIndex);

            if(items[newDataIndex] < items[parentIndex]){
                inIndex = true;
            }
            else{
                swap(items[newDataIndex], items[parentIndex]);
                newDataIndex = parentIndex;
            }

        }
        itemCount++;
        result = true;
    }
    return result;
}
#endif
