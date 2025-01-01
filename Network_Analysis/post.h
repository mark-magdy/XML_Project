//
// Created by kiro3 on 12/29/2024.
//

#ifndef XML_PROJECT_POST_H
#define XML_PROJECT_POST_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
//#include <utility>
//#include <memory>
#include <queue>
#include <stack>
#include <deque>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <unordered_set>


#include <vector>
#include <algorithm>

// other includes and code...

using namespace std;

struct Hash {
    vector<pair<int, int>> prefixHash;
    int N = 200000; 
    Hash() {}
    int p1, p2;
    int pw1[200000];
    int pw2[200000];
    const int MOD = 1e9 + 7;

    void preHash() {
        //srand(time(0));

        p1 = 1023568 % MOD, p2 = 785632326 % MOD;
        pw1[0] = 1, pw2[0] = 1;
        for (int i = 1; i < 200000; ++i) {
            pw1[i] = (pw1[i - 1] * p1) % MOD;
            pw2[i] = (pw2[i - 1] * p2) % MOD;
        }

    }

    Hash(string &s) {
        preHash(); 
        prefixHash = vector<pair<int, int >>(s.size(), {0, 0});
        for (int i = 0; i < s.size(); i++) {
            prefixHash[i].first = ((int) s[i] * pw1[i]) % MOD;
            prefixHash[i].second = ((int) s[i] * pw2[i]) % MOD;
            if (i)
                prefixHash[i] = {(prefixHash[i].first + prefixHash[i - 1].first) % MOD,
                                 (prefixHash[i].second + prefixHash[i - 1].second) % MOD};
        }
    }

    pair<int, int> getHashVal() {
        pair<int, int> result = prefixHash.back();
        result.first = (result.first * pw1[N - 1]) % MOD;
        result.second = (result.second * pw2[N - 1]) % MOD;
        return result;
    }

    pair<int, int> getRangeHashVal(int l, int r) {
        return {(((prefixHash[r].first - (l ? prefixHash[l - 1].first : 0) + MOD) % MOD) * pw1[N - l - 1]) % MOD,
                (((prefixHash[r].second - (l ? prefixHash[l - 1].second : 0) + MOD) % MOD) * pw2[N - l - 1]) % MOD};
    }
};

struct post{
    int number_of_followers ;
    string content;
    vector<string> topics ;
    int userId ;
    Hash* hashedContent ;
    post(vector<string> topics,string content,  int userId){
        this->topics=topics;
        this->content=content ;
        hashedContent = new Hash (content) ;
        this->userId=userId;
    }
};

#endif //XML_PROJECT_POST_H
