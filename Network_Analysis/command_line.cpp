//
// Created by kiro3 on 12/30/2024.
//
#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
//#include "../XML2tree/XMLtoTree.cpp"

//#include "User.h"
#include "UsersGraph.cpp"
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
void convertDotToPng(const std::string& dotFile, const std::string& outFile) {
    // Construct the command to convert DOT to PNG
    string dir="";
    bool write=0;
    for(int i=0;i<outFile.size();i++)
    {
       if(write) dir+=outFile[i];
        if(outFile[i]=='.')write=1;

    }
    std::string command = "dot -T"+dir+" ./Network_Analysis/" + dotFile + " -o ./Network_Analysis/" + outFile;

    // Execute the command
    int result = system(command.c_str());

    // Check for success or failure
    if (result != 0) {
        std::cerr << "Error: Failed to generate PNG file from DOT file." << std::endl;
        exit(1);
    } else {
        std::cout << "Successfully generated PNG file: " << outFile << std::endl;
    }
}

void draw_graph(string xml ,string outputFile)
{
    vector <treeNode*> test = totree(xml);
    treeNode* test_tree=test[0];
    UsersGraph *usersGraph=new UsersGraph(test_tree);

    // Open the file to write the DOT graph
    std::ofstream dotFile("./Network_Analysis/graph.dot");

    // Check if the file was opened successfully
    if (!dotFile) {
        std::cerr << "Error opening the file!" << std::endl;
        return ;
    }

    // Write a basic graph description in DOT language
    dotFile << "digraph G {\n";
    dotFile << print_edge_list(usersGraph->getUsers().getRoot());
    dotFile << "}\n";

    // Close the file
    dotFile.close();

    std::cout << "DOT file created successfully!" << std::endl;
    std::string dotfile = "graph.dot";  // The DOT file that will be created

    std::string pngFile = outputFile; // The PNG file that will be generated
    convertDotToPng(dotfile, pngFile);
}

int main() {
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
                <id>6</id>
            </follower>
            <follower>
                <id>7</id>
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
    string outputFile="kiro.tiff";
    draw_graph(xml,outputFile);

}