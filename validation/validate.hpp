
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
	validation();
	pair<bool,string> check_valid(string filename,stack<string>* tag_type=nullptr,stack<string>* its_name=nullptr,stack<int>* its_line=nullptr);


};

vector <string> correct_xml(string xml_string);

#endif
