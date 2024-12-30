//
// Created by Jessica on 12/29/2024.
//

#ifndef CONVERTTOJSON_H
#define CONVERTTOJSON_H

#include "../XML2tree/XMLtoTree.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <stack>
#include <cctype>
#include <algorithm>

string finalJson(vector <treeNode*> test);
string treeToJson(treeNode* node, int indentLevel , bool square ,int rep );


#endif //CONVERTTOJSON_H
