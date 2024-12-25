
#include <iostream>
#include"validate.hpp"

vector<string> validation:: extract_tag(string str,int num) { 
	vector<string> tags;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '<') {
			int j = i + 1;
			while (j < str.length() && str[j] != '>') { // Add boundary check for j
				j++;
			}
			if (j < str.length()) { // Ensure '>' was found
				 tags.push_back(str.substr(i, j - i + 1)); // Extract the tag
                 line_num.push_back(num); 
				 if(closing_tag(str.substr(i, j - i + 1))){
					count_closing++; // increase no.of closing tags
				}
				else{
					count_opening++; // increase no.of opening tags
				}
				i = j; // Move i to the end of the current tag
			} 
			else {
				cerr << "Error: Malformed tag in line: " << str << endl;
				break; // Exit on malformed tags
			}
		}
	}
	return tags;

}


bool validation:: closing_tag(string line){
	bool is_close = false;
	for(int i = 0; i < line.length() - 1; i++){
		if(line[i] == '<' && line[i+1] == '/'){
			is_close = true;
			break;
		}
	}
	return is_close;
}

 pair<string,bool> validation:: get_tagname(string tag) {
	bool insideTag = false;  // Flag to check if we're inside a tag
	string tagname;
	bool tag_valid = true;
	for (char ch : tag) {
		if (ch == '<') {
			insideTag = true;  // Start processing the tag
			continue;
		}

		if (insideTag) {

			if (ch == '>' || ch == ' ') {
				break;  // Stop at the end of the tag
			}
          
              if (!isalnum(ch) && ch!='/' ) { // Check for invalid characters in the tag
                 tag_valid = false;  // Set validity flag to false
                break;
            }
			if (ch != '/') {  // Ignore '/' in closing tags
				tagname += ch;  // Append valid characters to tag name
			}
		}
	}

	return {tagname,tag_valid};  // Return the extracted tag name
}

pair<bool,string> validation::check_valid(string filename,stack<string>& tag_type,stack<string>& its_name,stack<int>& its_line) {
	bool valid = true; // it's valid until we find an error
	bool tag_valid=true;
	fstream xml_file;
	string read_line; // read single line from xml file
	vector<string> lines; // vector of strings to push content of each line
	stack<string> tag_stack; // to push tag name of open tags
	string errors_GUI; // to print errors message in GUI
	

	xml_file.open(filename, ios::in); // open xml file and read contents

	if (xml_file.is_open()) {
		while (getline(xml_file, read_line)) {
			if (!read_line.empty()) { // skip empty lines
				lines.push_back(read_line);
			}
		}
	}
	xml_file.close(); // close the file
	vector<string> tags,tags2;
	vector<string> errors;
	// Start parsing the lines and get the tags
	for (int i = 0; i < lines.size(); i++) {
		string line = lines[i];
		tags2=extract_tag(line,i+1); // extract all tags from line
		tags.insert(tags.end(), tags2.begin(), tags2.end());
    }

	for (int j = 0; j < tags.size(); j++) {
		pair<string,bool>result;
		string tagname; // to be pushed into the stack
		result = get_tagname(tags[j]); // get the tag name and its validity
		tagname = result.first;
		tag_valid = result.second; // get the validity flag

        if (!tag_valid) {
			 // if tag name is not valid, break the loop and return false and the errors message
			 errors_GUI+="Error: Malformed tag in line "+ to_string(line_num[j])+"\n";
			 string v="Malformed tag";
			 tag_type.push(v);
			 its_line.push(line_num[j]);
			 valid=tag_valid;
			 break;
		}


		if (closing_tag(tags[j])) {
			if ((!tag_stack.empty()) && (tag_stack.top() == tagname)) {
				tag_stack.pop();
			} 
			else {
				if(count_opening<=count_closing){
					valid = false; // assign as there is an error and continue to print all errors in xml file
					string error_message = "Error: Closing tag </" + tagname + "> does not match. Line " + to_string(line_num[j])+"\n";
					errors_GUI+=error_message;
					string m ="closing tag";
					tag_type.push(m);
					its_name.push(tagname);
					its_line.push(line_num[j]);
					count_closing--;
				}
				else{
					valid = false; // assign as there is an error and continue to print all errors in xml file
					errors_GUI += "Error: Unclosed tag <" + tag_stack.top() + "> found.. Line " + to_string(line_num[j])+"\n";
					string x ="Unclosed tag";
					tag_type.push(x);
					its_name.push(tag_stack.top());
					its_line.push(line_num[j]);
					tag_stack.pop();   
					j--;
					count_opening--;
				}
			}
		} 
		else {
			tag_stack.push(tagname); // if it is an opening tag
			//cout<<"stack element for now  "<<tag_stack.top()<<endl;
		}
	}


	
	return {valid,errors_GUI}; // return the validity of the XML
}


int main(){
	string filename="sample.xml";
	validation val;
	validation test;
	stack<string>s1;
	stack<string>s2;
	stack<int>s3;
	test.check_valid(filename,s1,s2,s3);
	while(!s1.empty()){
		string b= s1.top();
		cout<<b<<endl;
		s1.pop();
	}
	while(!s2.empty()){
		string c= s2.top();
		cout<<c<<endl;
		s2.pop();
	}
	while(!s3.empty()){
		int l= s3.top();
		cout<<l<<endl;
		s3.pop();
	}
	if (val.check_valid(filename,s1,s2,s3).first){
          
		cout<<"XML file is valid."<<endl;
	}
	else {
         
		cout << "XML file has errors." << endl;
	}
  
		cout<<val.check_valid(filename,s1,s2,s3).second << endl;
    
	return 0;
}
