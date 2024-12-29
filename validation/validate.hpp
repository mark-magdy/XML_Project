
#ifndef VALIDATE_HPP
#define VALIDATE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class validation{

private:

	bool closing_tag(string line);

	vector<string>  extract_tag(string str,int num);

	pair<string,bool> get_tagname(string tag);

public:

	pair<bool,string> check_valid(string filename,stack<string>* tag_type=nullptr,stack<string>* its_name=nullptr,stack<int>* its_line=nullptr);



};

extern int count_opening;
extern int count_closing;

extern vector<int>line_num ; // to count number of lines and use it 
extern vector<string> lines; // vector of strings to push content of each line


stack<string> s1_stack;
stack<string> s2_stack;
stack<int> s3_stack;
stack<string> *s1=&s1_stack;
stack<string> *s2=&s2_stack;
stack<int> *s3=&s3_stack;

#endif
