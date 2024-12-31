//
// Created by marka on 12/29/2024.
//

#ifndef LEVEL2NET_POSTSSEARCH_H
#define LEVEL2NET_POSTSSEARCH_H

#include <string>
#include <vector>
#include <algorithm>
#include "UsersGraph.h"
#include "post.h"
using namespace std ;

class postsSearch {
private:
    vector <post> listOfPosts;

public:
    postsSearch (UsersGraph* t) ;
    vector <string> searchByWord (string ser);
    vector <string> searchByTopic (string ser);
};

#endif //LEVEL2NET_POSTSSEARCH_H
