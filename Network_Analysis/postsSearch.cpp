//
// Created by marka on 12/29/2024.
//

#include "postsSearch.h"
bool cmp(post&a ,post&b) {
    return a.number_of_followers>b.number_of_followers;
}
postsSearch::postsSearch (UsersGraph* t) {
    for (auto &i : t->getUsers() ){
        for (auto &j: i->getPostsList()){
            post x = post(j,i->number_of_followers,i->getID());
            listOfPosts.push_back(x);
        }
    }
    sort (listOfPosts.begin(),listOfPosts.end(),cmp);
}
vector <string> postsSearch::searchByWord (string ser){
    int sz = ser.size();
    auto cmp = Hash(ser).getHashVal();
    vector < string > ret ;
    for (int i = 0; i+sz-1 < min((int)listOfPosts.size(),(int)1e5); ++i) {
        if (listOfPosts[i].hashedContent.getRangeHashVal(i,i+sz-1) == cmp) {// getHash O(1)
            ret.push_back(listOfPosts[i].content);
        }
    }
}
vector <string>  postsSearch::searchByTopic (string ser){
    // to be implemented if topics was added
}