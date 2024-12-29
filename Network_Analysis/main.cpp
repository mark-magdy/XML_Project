#include <bits/stdc++.h>
//#include "../XML2tree/XMLtoTree.cpp"

//#include "User.h"
#include "UsersGraph.cpp"

using namespace std;

void print_user(UserBSTNode* root)
{
    if(root== nullptr)return;
    User *user=root->user;
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
    cout<<"number of posts: "<<user->getNumOfPosts()<<endl;
    for(post p:user->getPostsList())
    {
        cout<<"body: "<<p.content<<endl;
        cout<<"topics: ";
        for(string t:p.topics)cout<<t<<" ";
        cout<<endl;
    }
    print_user(root->left);
    print_user(root->right);
}

int main()
{
    std::string xml = R"(
<users>
    <user>
        <id>1</id>
        <name>Ahmed Ali</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        economy
                    </topic>
                    <topic>
                        finance
                    </topic>
                </topics>
            </post>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        solar_energy
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>2</id>
            </follower>
            <follower>
                <id>3</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>2</id>
        <name>Yasser Ahmed</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        education
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>3</id>
        <name>Mohamed Sherif</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        sports
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
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

    print_user(usersGraph->getUsers().getRoot());
  cout<<"most influencer: "<<usersGraph->getMostInfluencerUser()->getID()<<endl;
  cout<<"most active : "<<usersGraph->getMostActiveUser()->getID()<<endl;

  //cout<<test[0]->identifier; //issue
    return 0;
}
