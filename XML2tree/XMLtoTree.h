#ifndef XMLTOTREE_H
#define XMLTOTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <algorithm>

using namespace std;

class treeNode{
    public :
    string identifier;
    string content;
    treeNode * parent; // for navigating back from child to parent
    vector <treeNode *> children;
    long long level;

    treeNode()
    {

    }
};
vector <treeNode*> totree(string str_file);
void see_tree( treeNode * test);
void see_roots (vector <treeNode*> test);



#endif
