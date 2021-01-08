#pragma once
#ifndef ENECODER_H
#define ENCODER_H 
#include "treeNode.h"
#include "dWayHeap.h"
#include "pairingHeap.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <time.h>
void read(std::map<int, int>& freq, std::string filename);
void del(Tree* proot);
void print_Code(Tree* proot, std::string st, std::map<int, std::string>& encode);
void huffman(std::map<int, int>& freq, DaryHeap th, std::map<int, std::string>& encode);
std::map<int, std::string> encoder(std::string filename);
#endif
