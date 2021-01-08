#include "dWayHeap.h"
#include <cmath>



DaryHeap::DaryHeap(int capacity, int numKids)
{
    currentSize = 1;
    d = numKids;
    size = capacity + 1 + 1;

    array = new pTree[capacity + 1 + 1];
}

/*
 * Constructor , filling up heap with a given array
 */

 /*
  * Function to check if heap is empty
  */
bool DaryHeap::isEmpty()
{
    return currentSize == 1;
}

/*
 * Check if heap is full
 */
bool DaryHeap::isFull()
{
    return currentSize == size;
}

/*
 * Clear heap
 */
void DaryHeap::makeEmpty()
{
    currentSize = 1;
}

/*
 * Function to  get index parent of i
 */
int DaryHeap::parent(int i)
{
    int idx = (i - 1) / d;
    if (idx * d == i - 1)
    {
        return idx;
    }
    return idx + 1;
}

/*
 * Function to get index of k th child of i
 */
int DaryHeap::kthChild(int i, int k)
{
    return d * (i-1) + k + 1;
}

/*
 * Function to inset element
 */
void DaryHeap::Insert(pTree x)
{
    if (isFull())
    {
        std::cout << "Array Out of Bounds" << std::endl;
        return;
    }
    int hole = currentSize;
    currentSize++;
    array[hole] = x;
    percolateUp(hole);
}

/*
 * Function to find least element
 */
pTree DaryHeap::findMin()
{
    if (isEmpty())
    {
        std::cout << "Array Underflow" << std::endl;
        return 0;
    }
    return array[1];
}
/*
 * Function to delete element at an index
 */
pTree DaryHeap::Delete(int hole)
{
    if (isEmpty())
    {
        std::cout << "Array Underflow" << std::endl;
        return 0;
    }
    pTree keyItem = array[hole];
    array[hole] = array[currentSize - 1];
    currentSize--;
    percolateDown(hole);
    return keyItem;
}

/*
 * Function to build heap
 */
void DaryHeap::buildHeap()
{
    for (int i = currentSize - 1; i >= 1; i--)
        percolateDown(i);
}

/*
 * Function percolateDown
 */
void DaryHeap::percolateDown(int hole)
{
    
    int child;
    pTree tmp = array[hole];
    for (; kthChild(hole, 1) < currentSize; hole = child)
    {
        child = smallestChild(hole);
        if (array[child]->freq < tmp->freq)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

/*
 * Function to get smallest child from all valid indices
 */
int DaryHeap::smallestChild(int hole)
{
    int bestChildYet = kthChild(hole, 1);
    int k = 2;
    int candidateChild = kthChild(hole, k);
    while ((k <= d) && (candidateChild < currentSize))
    {
        if (array[candidateChild]->freq < array[bestChildYet]->freq)
            bestChildYet = candidateChild;
        k++;
        candidateChild = kthChild(hole, k);
    }
    return bestChildYet;
}

/*
 * Function percolateUp
 */
void DaryHeap::percolateUp(int hole)
{
    pTree tmp = array[hole];
    for (; hole > 1 && tmp->freq < array[parent(hole)]->freq; hole = parent(hole))
        array[hole] = array[parent(hole)];
    array[hole] = tmp;
}

