#include"validate.hpp"

int count_opening = 0;
int count_closing = 0;
vector<int> line_num;
vector<string> lines;


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


// bool check_valid(string filename,stack<string>& tag_type,stack<string>& its_name,stack<int>& its_line);



pair<bool,string> validation:: check_valid(string input_xml,stack<string>* tag_type,stack<string>* its_name,stack<int>* its_line){
	bool valid = true; // it's valid until we find an error
	bool tag_valid=true;
	istringstream stream(input_xml);
	string read_line; // read single line from xml file

	while(getline(stream,read_line)){
		if (!read_line.empty()) {
    lines.push_back(read_line);
	}
	}
	
	stack<pair<string,int>> tag_stack; // to push tag name of open tags
	string errors_GUI; // to print errors message in GUI
	
	 count_opening = 0;
	 count_closing = 0;


	
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
			 errors_GUI+="Error: Malformed tag <"+ tagname +"> found in line "+to_string(line_num[j])+"\n";
			if (tag_type != nullptr) tag_type->push("Malformed tag");
            if (its_line != nullptr) its_line->push(line_num[j]);
			 valid=tag_valid;
			 break;
		}


		if (closing_tag(tags[j])) {
			if ((!tag_stack.empty()) && (tag_stack.top().first == tagname)) {
				tag_stack.pop();
			} 
			else {
				if(count_opening<=count_closing){
					valid = false; // assign as there is an error and continue to print all errors in xml file
					string error_message = "Error: Closing tag </" + tagname + "> does not match. Line " + to_string(line_num[j])+"\n";
					errors_GUI+=error_message;
					if (tag_type != nullptr) tag_type->push("Closing tag");
               		if (its_name != nullptr) its_name->push(tagname);
                	if (its_line != nullptr) its_line->push(line_num[j]);
					count_closing--;
				}
				else{
					valid = false; // assign as there is an error and continue to print all errors in xml file
					errors_GUI += "Error: Unclosed tag <" + tag_stack.top().first + "> found.. Line " + to_string(tag_stack.top().second)+" correct in line " +to_string(line_num[j])+"\n";
					if (tag_type != nullptr) tag_type->push("Unclosed tag");
       			    if (its_name != nullptr) its_name->push(tag_stack.top().first);
                    if (its_line != nullptr) its_line->push(line_num[j]);
					tag_stack.pop();   
					j--;
					count_opening--;
				}
			}
		} 
		else {
			tag_stack.push({tagname,line_num[j]}); // if it is an opening tag
		}
	}

	// Check for unclosed tags remained in the stack and report where to correct it
	while (!tag_stack.empty()) {
		valid = false;
		errors_GUI+="Error: Unclosed tag <" + tag_stack.top().first + "> found in line "+ to_string(tag_stack.top().second)+" correct in " +to_string(lines.size())+"\n";
		if (tag_type != nullptr) tag_type->push("Unclosed tag");
        if (its_name != nullptr) its_name->push(tag_stack.top().first);
        if (its_line != nullptr) its_line->push(lines.size());
		tag_stack.pop();
	}
	

	
	return {valid,errors_GUI}; // return the validity of the XML
}

// int main() {
//     string filename = "sample.xml";
// 	string xmlData = 
// "<users>\n"
// "\t<user>\n"
// "\t\t<id>1</id>\n"
// "\t\t<name>Ahmed Ali</name>\n"
// "\t\t<posts>\n"
// "\t\t\t<post>\n"
// "\t\t\t\t<body>\n"
// "\t\t\t\t\tLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
// "\t\t\t\t</body>\n"
// "\t\t\t\t<topics>\n"
// "\t\t\t\t\t<topic>\n"
// "\t\t\t\t\t\teconomy\n"
// "\t\t\t\t\t</topic>\n"
// "\t\t\t\t\t<topic>\n"
// "\t\t\t\t\t\tfinance\n"
// "\t\t\t\t\t</topic>\n"
// "\t\t\t\t</topics>\n"
// "\t\t\t</post>\n"
// "\t\t\t<post>\n"
// "\t\t\t\t<body>\n"
// "\t\t\t\t\tLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
// "\t\t\t\t</body>\n"
// "\t\t\t\t<topics>\n"
// "\t\t\t\t\t<topic>\n"
// "\t\t\t\t\t\tsolar_energy\n"
// "\t\t\t\t\t</topic>\n"
// "\t\t\t\t</topics>\n"
// "\t\t<followers>\n"
// "\t\t\t<follower>\n"
// "\t\t\t\t<id>2</id>\n"
// "\t\t\t</follower>\n"
// "\t\t\t<follower>\n"
// "\t\t\t\t<id>3</id>\n"
// "\t\t\t</follower>\n"
// "\t\t</followers>\n"
// "\t<user></user>\n"
// "\t<user>\n"
// "\t\t<id>2</id>\n"
// "\t\t<name>Yasser Ahmed</name>\n"
// "\t\t<posts>\n"
// "\t\t\t<post>\n"
// "\t\t\t\t<body>\n"
// "\t\t\t\t\tLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
// "\t\t\t\t</body>\n"
// "\t\t\t\t<topics>\n"
// "\t\t\t\t\t<topic>\n"
// "\t\t\t\t\t\teducation\n"
// "\t\t\t\t\t</topic>\n"
// "\t\t\t\t</topics>\n"
// "\t\t\t</post>\n"
// "\t\t</posts>\n"
// "\t\t<followers>\n"
// "\t\t\t<follower>\n"
// "\t\t\t\t<id>1</id>\n"
// "\t\t\t</follower>\n"
// "\t\t</followers>\n"
// "\t</user>\n"
// "\t\n"
// "\t\t<id>3</id>\n"
// "\t\t<name>Mohamed Sherif</name>\n"
// "\t\t<posts>\n"
// "\t\t\t<post>\n"
// "\t\t\t\t<body>\n"
// "\t\t\t\t\tLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
// "\t\t\t\t</body>\n"
// "\t\t\t\t<topics>\n"
// "\t\t\t\t\t\n"
// "\t\t\t\t\t\tsports\n"
// "\t\t\t\t\t</topics><topic></topic>\n"
// "\t\t\t\t</post><topics></topics>\n"
// "\t\t\t</posts></post>\n"
// "\t\t</posts>\n"
// "\t\t<followers>\n"
// "\t\t\t<follower>\n"
// "\t\t\t\t<id>1</id>\n"
// "\t\t\t</follower>\n"
// "\t\t</followers>\n"
// "\t</user>\n"
// "</users>";
//     validation val;

//     // Call check_valid only once
//     pair<bool, string> result = val.check_valid(xmlData,s1,s2,s3);

//     // Print the errors stored in the stacks
//     while (!s1->empty()) {
//         cout << s1->top() << endl;
//         s1->pop();
//     }
//     while (!s2->empty()) {
//         cout << s2->top() << endl;
//         s2->pop();
//     }
//     while (!s3->empty()) {
//         cout << s3->top() << endl;
//         s3->pop();
//     }

//     // Output validation status
//     if (result.first) {
//         cout << "XML file is valid." << endl;
//     } else {
//         cout << "XML file has errors." << endl;
//     }

//     // Output error details
//     cout << result.second << endl;

//     // Print the lines vector 
//     for (auto i : lines) {
//         cout << i << endl;
//     }

//     return 0;
// }