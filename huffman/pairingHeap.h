#pragma once
#pragma once
#ifndef PAIRINGHEAP_H
#define PAIRINGHEAP_H
#include <iostream>
#include "treeNode.h"


class PairNode
{
public:
    pTree element;
    PairNode* leftChild;
    PairNode* nextSibling;
    PairNode* prev;
    PairNode(pTree element)
    {
        this->element = element;
        leftChild = NULL;
        nextSibling = NULL;
        prev = NULL;
    }
};


class PairingHeap
{
private:
    PairNode* root;
    void reclaimMemory(PairNode* t);
    void compareAndLink(PairNode*& first, PairNode* second);
    PairNode* combineSiblings(PairNode* firstSibling);
    PairNode* clone(PairNode* t);
public:
    PairingHeap();
    PairingHeap(PairingHeap& rhs);
    ~PairingHeap();
    bool isEmpty();
    bool isFull();
    pTree& findMin();
    PairNode* Insert(pTree& x);
    void deleteMin();
    void deleteMin(pTree& minItem);
    void makeEmpty();
    void decreaseKey(PairNode* p, pTree& newVal);
    PairingHeap& operator=(PairingHeap& rhs);
};
#endif // !PAIRINGHEAP_H

