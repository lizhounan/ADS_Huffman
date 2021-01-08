#pragma once
#ifndef TREENODE_H
#define TREENODE_H 

typedef struct Tree
{
    int freq;
    int key;
    struct Tree* left, * right;
    Tree(int fr = 0, int k = 0, Tree* l = nullptr, Tree* r = nullptr) :
        freq(fr), key(k), left(l), right(r) {};
}Tree, * pTree;

#endif

