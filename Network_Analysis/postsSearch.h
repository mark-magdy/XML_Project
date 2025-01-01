//
// Created by marka on 12/29/2024.
//

#ifndef LEVEL2NET_POSTSSEARCH_H
#define LEVEL2NET_POSTSSEARCH_H

#include "post.h"
#include "UsersGraph.h"

/*
#include <string>
#include <vector>
#include <algorithm>
#include <map>
*/

//#include "UsersGraph.h"

using namespace std ;

class postsSearch {
private:
    vector <post> listOfPosts;
    map<pair<int,int> , vector <post> > mapOfPosts ;
public:
    postsSearch (UsersGraph* t) ;
    vector <post> searchByWord (string ser);
    vector <post> searchByTopic (string ser);
};

#endif //LEVEL2NET_POSTSSEARCH_H
