#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include "validate.hpp"
using namespace std;


vector <string> lines_extraction(string filepath){
    vector <string> xml_lines;
    string line;
    fstream input_file;

    input_file.open(filepath, ios::in); //open file

	if (input_file.is_open()) { //check if file opened successfully
		while (getline(input_file, line)) { //while line is not empty lines extract
			if (!line.empty()) { // skip empty lines
				xml_lines.push_back(line);//push line in vector
			}
		}
	}

    input_file.close(); //close file

    return xml_lines;
}

vector <string> correct_xml(string xml_string){

    int error_line_number;
    string tag_missing;
    string type;

    validation check;
    check.check_valid(xml_string,s1,s2,s3);

    while(!s2->empty() && !s3->empty() && !s1->empty()){
        error_line_number= s3->top();
        s3->pop();
        tag_missing=s2->top();
        s2->pop();
        type=s1->top();
        s1->pop();
        
            if (error_line_number >= 0 && error_line_number < lines.size()) {
                if(type=="Closing tag")
                lines[error_line_number-1] = "<"+tag_missing+">"+lines[error_line_number-1];
                else
                lines[error_line_number-1] = "</"+tag_missing+">"+lines[error_line_number-1];
             }

    }
    return lines;
}

void writeback_file(vector <string> xml_lines,string filepath){
    ofstream output_file(filepath);
    if(output_file.is_open()){
        for (int i = 0; i < xml_lines.size(); i++) {
        output_file << xml_lines[i] << "\n";
    }
    output_file.close();
    }
}


/*
int main() {
    vector<string> corrected_xml_lines;
    //string xml_string;
string xmlData = 
"<users>\n"
"\t<user>\n"
"\t\t<id>1</id>\n"
"\t\t<name>Ahmed Ali</name>\n"
"\t\t<posts>\n"
"\t\t\t<post>\n"
"\t\t\t\t<body>\n"
"\t\t\t\t\tLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
"\t\t\t\t</body>\n"
"\t\t\t\t<topics>\n"
"\t\t\t\t\t<topic>\n"
"\t\t\t\t\t\teconomy\n"
"\t\t\t\t\t</topic>\n"
"\t\t\t\t\t<topic>\n"
"\t\t\t\t\t\tfinance\n"
"\t\t\t\t\t</topic>\n"
"\t\t\t\t</topics>\n"
"\t\t\t</post>\n"
"\t\t\t<post>\n"
"\t\t\t\t<body>\n"
"\t\t\t\t\tLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
"\t\t\t\t</body>\n"
"\t\t\t\t<topics>\n"
"\t\t\t\t\t<topic>\n"
"\t\t\t\t\t\tsolar_energy\n"
"\t\t\t\t\t</topic>\n"
"\t\t\t\t</topics>\n"
"\t\t<followers>\n"
"\t\t\t<follower>\n"
"\t\t\t\t<id>2</id>\n"
"\t\t\t</follower>\n"
"\t\t\t<follower>\n"
"\t\t\t\t<id>3</id>\n"
"\t\t\t</follower>\n"
"\t\t</followers>\n"
"\t</user>\n"
"\t<user>\n"
"\t\t<id>2</id>\n"
"\t\t<name>Yasser Ahmed</name>\n"
"\t\t<posts>\n"
"\t\t\t<post>\n"
"\t\t\t\t<body>\n"
"\t\t\t\t\tLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
"\t\t\t\t</body>\n"
"\t\t\t\t<topics>\n"
"\t\t\t\t\t<topic>\n"
"\t\t\t\t\t\teducation\n"
"\t\t\t\t\t</topic>\n"
"\t\t\t\t</topics>\n"
"\t\t\t</post>\n"
"\t\t</posts>\n"
"\t\t<followers>\n"
"\t\t\t<follower>\n"
"\t\t\t\t<id>1</id>\n"
"\t\t\t</follower>\n"
"\t\t</followers>\n"
"\t</user>\n"
"\t\n"
"\t\t<id>3</id>\n"
"\t\t<name>Mohamed Sherif</name>\n"
"\t\t<posts>\n"
"\t\t\t<post>\n"
"\t\t\t\t<body>\n"
"\t\t\t\t\tLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
"\t\t\t\t</body>\n"
"\t\t\t\t<topics>\n"
"\t\t\t\t\t\n"
"\t\t\t\t\t\tsports\n"
"\t\t\t\t\t</topic>\n"
"\t\t\t\t</topics>\n"
"\t\t\t</post>\n"
"\t\t</posts>\n"
"\t\t<followers>\n"
"\t\t\t<follower>\n"
"\t\t\t\t<id>1</id>\n"
"\t\t\t</follower>\n"
"\t\t</followers>\n"
"\t</user>\n"
"</users>";
    corrected_xml_lines = correct_xml(xmlData );
    writeback_file(corrected_xml_lines, "sample_mynew.xml");

    return 0;
}
*/
