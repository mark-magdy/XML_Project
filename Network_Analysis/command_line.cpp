//#include <bits/stdc++.h>
//#include "../XML2tree/XMLtoTree.cpp"
//#include "User.h"
#include "Level_2_Command_Line_Functions.h"
//#include "UsersGraph.cpp"

string print_edge_list(UserBSTNode* root)
{
	if (root == nullptr)return "";

	User* user = root->user;
	string temp;
	for (long fol : user->getFollowersIDsList())
	{
		temp += (to_string(user->getID()) + " -> " + to_string(fol) + "\n");
	}

	temp += print_edge_list(root->left);
	temp += print_edge_list(root->right);
	return temp;
}

void convertDotToPng(const std::string& dotFile, const std::string& outFile)
{
	// Construct the command to convert DOT to PNG
	string dir = "";
	bool write = 0;
	for (int i = 0; i < outFile.size(); i++)
	{
		if (write) dir += outFile[i];
		if (outFile[i] == '.')write = 1;
	}
	std::string command = "dot -T" + dir + " ./Network_Analysis/" + dotFile + " -o ./Network_Analysis/" + outFile;

	// Execute the command
	int result = system(command.c_str());

	// Check for success or failure
	if (result != 0)
	{
		std::cerr << "Error: Failed to generate PNG file from DOT file." << std::endl;
		exit(1);
	}
	else
	{
		std::cout << "Successfully generated PNG file: " << outFile << std::endl;
	}
}

void draw_graph(string xml, string outputFile)
{
	vector<treeNode*> test = totree(xml);
	treeNode* test_tree = test[0];
	UsersGraph* usersGraph = new UsersGraph(test_tree);

	// Open the file to write the DOT graph
	std::ofstream dotFile("./Network_Analysis/graph.dot");

	// Check if the file was opened successfully
	if (!dotFile)
	{
		std::cerr << "Error opening the file!" << std::endl;
		return;
	}

	// Write a basic graph description in DOT language
	dotFile << "digraph G {\n";
	dotFile << print_edge_list(usersGraph->getUsers().getRoot());
	dotFile << "}\n";

	// Close the file
	dotFile.close();

	std::cout << "DOT file created successfully!" << std::endl;
	std::string dotfile = "graph.dot"; // The DOT file that will be created

	std::string pngFile = outputFile; // The PNG file that will be generated
	convertDotToPng(dotfile, pngFile);
}

pair<long, string> get_most_active(string xml)
{
	vector<treeNode*> test = totree(xml);
	treeNode* test_tree = test[0];
	UsersGraph* usersGraph = new UsersGraph(test_tree);
	User* user = usersGraph->getMostActiveUser();
	long id = user->getID();
	string name = user->getName();
	return make_pair(id, name);
}

pair<long, string> get_most_influencer(string xml)
{
	vector<treeNode*> test = totree(xml);
	treeNode* test_tree = test[0];
	UsersGraph* usersGraph = new UsersGraph(test_tree);
	User* user = usersGraph->getMostInfluencerUser();
	long id = user->getID();
	string name = user->getName();
	return make_pair(id, name);
}

vector<long> get_mutual(string xml, const vector<long>& IDs)
{
	vector<treeNode*> test = totree(xml);
	treeNode* test_tree = test[0];
	UsersGraph* usersGraph = new UsersGraph(test_tree);
	vector<long> ID_result = usersGraph->getMutualFollowers(IDs);
	return ID_result;
}

vector<long> get_suggest(string xml, long ID)
{
	vector<treeNode*> test = totree(xml);
	treeNode* test_tree = test[0];
	UsersGraph* usersGraph = new UsersGraph(test_tree);
	UsersBST usersBST = usersGraph->getUsers();
	User* user = usersBST.findByID(ID);
	vector<long> ID_result;
	if (user != nullptr)
	{
		ID_result = user->getFollowersIDsList();
	}
	return ID_result;
}


 vector <string> search_by_word (string xml, string word)
 {
 	vector<treeNode*> test = totree(xml);
 	treeNode* test_tree = test[0];
 	UsersGraph* usersGraph = new UsersGraph(test_tree);
 	postsSearch* posts_search = new postsSearch(usersGraph);
 	auto ret =  posts_search->searchByWord(word);
     vector<string> result ;
     for (auto &i: ret ) {
         string toprint = "topics:";
         cout <<" -- " << i.topics.size() <<" " << i.topics[0]<< endl ;
         for ( auto j : i.topics) toprint+= j + "  ";
         toprint+="\n";
         toprint+=i.content;
         result.push_back(toprint);
     }
     return result;
 }

 vector <string> search_by_topic (string xml, string topic)
 {
 	vector<treeNode*> test = totree(xml);
 	treeNode* test_tree = test[0];
 	UsersGraph* usersGraph = new UsersGraph(test_tree);
 	postsSearch* posts_search = new postsSearch(usersGraph);
     auto ret = posts_search->searchByTopic(topic);
     vector<string> result ;
     for (auto &i: ret ) {
         string toprint = "topics:";
         for ( auto &j : i.topics) toprint+= j + "  ";
         toprint+="\n";
         toprint+=i.content;
         result.push_back(toprint);
     }
 	return result;
 }




//int main() {
//    std::string xml = R"(
//<users>
//    <user>
//        <id>1</id>
//        <name>Ahmed Ali</name>
//        <posts>
//            <post>
//                <body>
//                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
//                </body>
//                <topics>
//                    <topic>economy</topic>
//                    <topic>finance</topic>
//                </topics>
//            </post>
//            <post>
//                <body>
//                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo onsequat.
//                </body>
//                <topics>
//                    <topic>solar_energy</topic>
//                </topics>
//            </post>
//        </posts>
//        <followers>
//            <follower>
//                <id>2</id>
//            </follower>
//            <follower>
//                <id>3</id>
//            </follower>
//            <follower>
//                <id>4</id>
//            </follower>
//            <follower>
//                <id>5</id>
//            </follower>
//        </followers>
//    </user>
//    <user>
//        <id>2</id>
//        <name>Yasser Ahmed</name>
//        <posts>
//            <post>
//                <body>
//                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
//                </body>
//                <topics>
//                    <topic>education</topic>
//                </topics>
//            </post>
//        </posts>
//        <followers>
//            <follower>
//                <id>1</id>
//            </follower>
//            <follower>
//                <id>3</id>
//            </follower>
//            <follower>
//                <id>6</id>
//            </follower>
//            <follower>
//                <id>7</id>
//            </follower>
//        </followers>
//    </user>
//    <user>
//        <id>3</id>
//        <name>Mohamed Sherif</name>
//        <posts>
//            <post>
//                <body>
//                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
//                </body>
//                <topics>
//                    <topic>sports</topic>
//                </topics>
//            </post>
//        </posts>
//        <followers>
//            <follower>
//                <id>1</id>
//            </follower>
//            <follower>
//                <id>2</id>
//            </follower>
//            <follower>
//                <id>4</id>
//            </follower>
//        </followers>
//    </user>
//</users>
//
//
//)";
//    //string outputFile="kiro.jpg";
//    //draw_graph(xml,outputFile);
//    for ( auto &i : search_by_word(xml,"consequat")){
//        cout << i<< "\n\n" ;
//    }
//}
