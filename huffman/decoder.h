#pragma once
#ifndef DECODER_H
#define DECODER_H 
#include "treeNode.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <time.h>
void decode(std::map<int, std::string>& encode, Tree* proot);
void decoder();
#endif
