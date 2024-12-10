#include <iostream>
#include "beautify.h"
using namespace std;

void prettify(vector<string>& lines) {
    char indent = '\t';
    stack<string> temp;

    for (int i = 0; i < lines.size(); i++) {
        string s = lines[i];
        string letters;

        int start_index = 0;
        int end_index = 0;

        int level = temp.size();
        string tabs(level, indent);

        if (s[0] != '<') {
            lines[i] = tabs + lines[i] + '\n';
            //cout << lines[i];
            continue;
        }

        if (s[1] != '/') {
            lines[i] = tabs + lines[i] + '\n';
            //cout << lines[i];
        }

        for (int j = 0; j < s.length(); j++) {

            if (s[j] == '<') start_index = j + 1;

            else if (s[j] == '>') {
                end_index = j;
                letters = s.substr(start_index, end_index - start_index);

                if (!letters.empty() && letters[0] != '/') {
                    temp.push(letters);
                }

                else {
                    if ("/" + temp.top() == letters) {
                        temp.pop();
                    }
                }
            }
        }

        if (s[1] == '/') {
            int level = temp.size();
            string tabs(level, indent);
            lines[i] = tabs + lines[i] + '\n';
            //cout << lines[i];
        }

    }
}

void minify(vector<string>& lines) {
    int l = 0;
    for (int i = 0; i < lines.size(); i++) {
        string s = lines[i];
        string temp;
        bool space = s[0] == ' ' ? true : false;
        for (int j = 0; j < s.length(); j++) {
            if (space) {
                space = s[j + 1] == ' ' ? true : false;
                continue;
            }

            if (j > 0 && s[j - 1] == '>') {
                if (s[j] == ' ' && !isalpha(s[j + 1])) break;
            }

            temp += s[j];
        }

        if (!temp.empty()) {
            lines[l] = temp;
            l++;
        }
    }
    for (l; l < lines.size(); l++) {
        lines.pop_back();
    }
}

int main()
{
    vector<string> xml = {
            "  <users>  ",
            "",
            "  <user> ",
            "  <id>1</id> ",
            "  <name> Ahmed Ali</name>",
            "    <posts>",
            "  <post>",
            "  <body>  ",
            "  Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",
            "  </body>  ",
            "  <topics> ",
            "  <topic>",
            "  economy",
            "  </topic>",
            "  <topic>",
            "  finance",
            "  </topic>",
            "  </topics>",
            "  </post>",
            "  <post>",
            "  <body>",
            "  Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",
            "  </body>",
            "    <topics>",
            "  <topic>",
            "  solar_energy",
            "  </topic>",
            "  </topics>",
            "  </post>",
            "  </posts>",
            "  <followers>",
            "  <follower>",
            "  <id>2</id>",
            "  </follower>",
            "  <follower>",
            "  <id>3</id>",
            "  </follower>",
            "  </followers>",
            "  </user>",
            "  <user>",
            "  <id>2</id>",
            "  <name>Yasser Ahmed</name>",
            "  <posts>",
            "  <post>",
            "  <body>",
            "  Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",
            "  </body>",
            "  <topics>",
            "  <topic>",
            "  education",
            "  </topic>",
            "  </topics>",
            "  </post>",
            "  </posts>",
            "  <followers>",
            "  <follower>",
            "  <id>1</id>",
            "  </follower>",
            "  </followers>",
            "  </user>",
            "  <user>",
            "  <id>3</id>",
            "  <name>Mohamed Sherif</name>",
            "  <posts>",
            "  <post>",
            "  <body>",
            "  Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",
            "  </body>",
            "  <topics>",
            "  <topic>",
            "  sports",
            "  </topic>",
            "  </topics>",
            "  </post>",
            "  </posts>",
            "  <followers>",
            "  <follower>",
            "  <id>1</id>",
            "  </follower>",
            "  </followers>",
            "  </user>",
            "  </users>"
    };
    minify(xml);
    for (int i = 0; i < xml.size(); i++) {
        cout << xml[i] << endl;
    }
    cout << "--------------" << endl;
    prettify(xml);
    for (int i = 0; i < xml.size(); i++) {
        cout << xml[i] << endl;
    }
    
}