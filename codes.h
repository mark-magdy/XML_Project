#ifndef codes_h
#define codes_h
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include "XMLtoTree.h"
using namespace std;

void minify(vector<string>& lines);

void editing(vector<string>& lines);

void prettify(vector<string>& lines);

void node_to_vector(vector<treeNode*> parent, vector<string>& result);

void tester(vector<string> x,vector<treeNode*> y);
#endif // !codes.h