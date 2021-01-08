#pragma once
#ifndef DWAYHEAP_H
#define DWAYHEAP_H
#include <iostream>
#include "treeNode.h"




class DaryHeap
{
private:
    int d;
    int currentSize;
    int size;
    pTree* array;
public:
    /*
     * Constructor
     */
    DaryHeap(int capacity, int numKids);

    /*
     * Constructor , filling up heap with a given array
     */

     /*
      * Function to check if heap is empty
      */
    bool isEmpty();

    /*
     * Check if heap is full
     */
    bool isFull();

    /*
     * Clear heap
     */
    void makeEmpty();

    /*
     * Function to  get index parent of i
     */
    int parent(int i);

    /*
     * Function to get index of k th child of i
     */
    int kthChild(int i, int k);

    /*
     * Function to inset element
     */
    void Insert(pTree x);

    /*
     * Function to find least element
     */
    pTree findMin();
    /*
     * Function to delete element at an index
     */
    pTree Delete(int hole);

    /*
     * Function to build heap
     */
    void buildHeap();

    /*
     * Function percolateDown
     */
    void percolateDown(int hole);

    /*
     * Function to get smallest child from all valid indices
     */
    int smallestChild(int hole);

    /*
     * Function percolateUp
     */
    void percolateUp(int hole);

    /*
    * print the internal array
    */
    void printArray()
    {
        for (int i = 1; i < currentSize; i++)
        {
            std::cout << array[i]->key << ' ';
        }
        std::cout << std::endl;
    }
};
#endif // !DWAYHEAP_H

