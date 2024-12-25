#ifndef VALIDATE_HPP
#define VALIDATE_HPP

#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include <utility> // For std::pair
#include <string>
using namespace std;

class validation{
private:
	bool closing_tag(string line);
	vector<string>  extract_tag(string str,int num);
	pair<string,bool> get_tagname(string tag);
public:
	pair<bool,string> check_valid(string filename,stack<string>& tag_type,stack<string>& its_name,stack<int>& its_line);
};
int count_opening=0;
int count_closing=0;
vector<int>line_num ; // to count number of lines and use it 
#endif  