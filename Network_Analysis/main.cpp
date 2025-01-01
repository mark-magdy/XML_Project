#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
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
    cout<<endl;
    print_user(root->left);
    print_user(root->right);
}
string print_edge_list(UserBSTNode* root)
{
    if(root== nullptr)return "";

    User *user=root->user;
    string temp;
    for(long fol:user->getFollowersIDsList())
    {

        temp+=(to_string(user->getID())+ " -> "+ to_string(fol)+"\n");
    }

    temp+=print_edge_list(root->left);
   temp+= print_edge_list(root->right);
   return temp;
}

void convertDotToPng(const std::string& dotFile, const std::string& pngFile) {
    // Construct the command to convert DOT to PNG
    std::string command = "dot -Tpng ./Network_Analysis/" + dotFile + " -o ./Network_Analysis/" + pngFile;

    // Execute the command
    int result = system(command.c_str());

    // Check for success or failure
    if (result != 0) {
        std::cerr << "Error: Failed to generate PNG file from DOT file." << std::endl;
        exit(1);
    } else {
        std::cout << "Successfully generated PNG file: " << pngFile << std::endl;
    }
}


/*
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
                    <topic>economy</topic>
                    <topic>finance</topic>
                </topics>
            </post>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>solar_energy</topic>
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
            <follower>
                <id>4</id>
            </follower>
            <follower>
                <id>5</id>
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
                    <topic>education</topic>
                    <topic>healthcare</topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
            </follower>
            <follower>
                <id>3</id>
            </follower>
            <follower>
                <id>5</id>
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
                    <topic>sports</topic>
                    <topic>technology</topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
            </follower>
            <follower>
                <id>2</id>
            </follower>
            <follower>
                <id>4</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>4</id>
        <name>Ali Hassan</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>finance</topic>
                    <topic>education</topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
            </follower>
            <follower>
                <id>2</id>
            </follower>
            <follower>
                <id>3</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>5</id>
        <name>Sara Khaled</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>solar_energy</topic>
                    <topic>economy</topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
            </follower>
            <follower>
                <id>2</id>
            </follower>
            <follower>
                <id>4</id>
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

//    // Open the file to write the DOT graph
//    std::ofstream dotFile("./Network_Analysis/graph.dot");
//
//    // Check if the file was opened successfully
//    if (!dotFile) {
//        std::cerr << "Error opening the file!" << std::endl;
//        return 1;
//    }
//
//    // Write a basic graph description in DOT language
//    dotFile << "digraph G {\n";
//    dotFile << print_edge_list(usersGraph->getUsers().getRoot());
//    dotFile << "}\n";
//
//    // Close the file
//    dotFile.close();
//
//    std::cout << "DOT file created successfully!" << std::endl;
//    std::string dotfile = "graph.dot";  // The DOT file that will be created
//
//    std::string pngFile = "graph.png"; // The PNG file that will be generated
//    convertDotToPng(dotfile, pngFile);

//    const char* command = "dot -Tpng ./Network_Analysis/graph.dot -o ./Network_Analysis/graph.png";
//    // Run the command in the shell
//    int result = system(command);
//
//    if (result == 0) {
//        std::cout << "Command executed successfully!" << std::endl;
//    } else {
//        std::cout << "Error executing the command!" << std::endl;
//    }



 //   cout<< print_edge_list(usersGraph->getUsers().getRoot());
//  cout<<"most influencer: "<<usersGraph->getMostInfluencerUser()->getID()<<endl;
//  cout<<"most active : "<<usersGraph->getMostActiveUser()->getID()<<endl;

  //cout<<test[0]->identifier; //issue
    return 0;
}
*/