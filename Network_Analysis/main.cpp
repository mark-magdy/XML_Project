#include <bits/stdc++.h>
//#include "../XML2tree/XMLtoTree.cpp"

//#include "User.h"
#include "UsersGraph.cpp"

using namespace std;
int main()
{
    std::string xml = R"(
<users>
    <user>
        <id>101</id>
        <name>Michael Scott</name>
        <followers>
            <follower>
                <id>202</id>
            </follower>
            <follower>
                <id>303</id>
            </follower>
            <follower>
                <id>404</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>202</id>
        <name>Dwight Schrute</name>
        <followers>
            <follower>
                <id>101</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>303</id>
        <name>Jim Halpert</name>
        <followers>
            <follower>
                <id>101</id>
            </follower>
            <follower>
                <id>202</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>404</id>
        <name>Angela Martin</name>
        <followers>
            <follower>
                <id>202</id>
            </follower>
            <follower>
                <id>303</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>505</id>
        <name>Pam Beesly</name>
        <followers>
            <follower>
                <id>303</id>
            </follower>
            <follower>
                <id>101</id>
            </follower>
            <follower>
                <id>202</id>
            </follower>
            <follower>
                <id>404</id>
            </follower>
        </followers>
    </user>
</users>
)";

    vector <treeNode*> test = totree(xml);

  //testing
  //see_roots(test);
  treeNode* test_tree=test[0];
  UsersGraph *usersGraph=new UsersGraph(test_tree);
  for(User *user:usersGraph->getUsers())
  {
      cout<<user->getID()<<endl;
      cout<<user->getName()<<endl;
      cout<<"followers: ";
      for(long follwer_id:user->getFollowersIDsList())
      {
          cout<<follwer_id<<" ";
      }
      cout<<endl<<"following: ";
      for(long follwer_id:user->getFollowingIDsList())
      {
          cout<<follwer_id<<" ";
      }
      cout<<endl<<"suggested friends: ";
      for(long follwer_id:user->getSuggestedFriendsIDsList())
      {
          cout<<follwer_id<<" ";
      }
      cout<<endl;
      cout<<"number of followers -  number of follows - number of connections"<<endl;
      cout<<user->getNumOfFollowers()<<" "<<user->getNumOfFollowings()<<" "<<user->getNumOfConnections()<<endl;
  }
  cout<<"most influencer: "<<usersGraph->getMostInfluencerUser()->getID()<<endl;
  cout<<"most active : "<<usersGraph->getMostActiveUser()->getID()<<endl;

  //cout<<test[0]->identifier; //issue
    return 0;
}
