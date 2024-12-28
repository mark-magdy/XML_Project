//
// Created by kiro3 on 12/27/2024.
//
#include <bits/stdc++.h>
#include "../XML2tree/XMLtoTree.cpp"

using namespace std;
int main()
{
      string str = R"(<users> <a><c>00</c></a> <b></b> </users> <new> <A> </A> </new>)";
  vector <treeNode*> test = totree(str);

  //testing
  see_roots(test);
  //cout<<test[0]->identifier; //issue
    return 0;
}
