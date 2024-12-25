#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include "XMLtoTree.h"
using namespace std;

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

void editing(vector<string>& lines) { //call in case of multiple tags in 1 line
    for (int i = 0; i < lines.size(); i++) {
        string temp = lines[i];
        for (int j = 0; j < temp.length(); j++) {
            if (temp[j] == '>' && j < temp.length() - 1 && temp[j + 1] == '<') {
                lines[i] = temp.substr(0, j + 1);
                string push = temp.substr(j + 1, temp.length() - (j + 1));
                lines.insert(lines.begin() + i + 1, push);
            }
        }
    }
}
//minify, editing are called inside prettify
void prettify(vector<string>& lines) {
    editing(lines);
    minify(lines);

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
//not called inside inside prettify
void node_to_vector(vector<treeNode*> parent, vector<string>& result) {
    if (!parent[0]) return;
    treeNode* current = parent[0];
    bool done;

    stack<treeNode*> nodes;
    stack<bool> finished;
    nodes.push(current);
    finished.push(false);

    while (!nodes.empty()) {
        current = nodes.top();
        done = finished.top();
        finished.pop();
        nodes.pop();

        if (done) {
            result.push_back("</" + current->identifier + ">");
            continue;
        }

        result.push_back("<" + current->identifier + ">");
        if (current->content != "")
            result.push_back(current->content);

        nodes.push(current);
        finished.push(true);
        int childrenSize = current->children.size();
        for (int i = childrenSize - 1; i >= 0; i--) {
            nodes.push(current->children[i]);
            finished.push(false);
        }
    }

}

void tester(vector<string> x, vector<treeNode*> y)
{
    vector<string> xml = {
            "  <users>  ",
            "  ",
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

    prettify(xml);
    for (int i = 0; i < xml.size(); i++) {
        cout << xml[i];
    }

    string str = R"(<users><user><id>1</id><name>Ahmed Ali</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>economy</topic><topic>finance</topic></topics></post><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>solar_energy</topic></topics></post></posts><followers><follower><id>2</id></follower><follower><id>3</id></follower></followers></user><user><id>2</id><name>Yasser Ahmed</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>education</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user><user><id>3</id><name>Mohamed Sherif</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>sports</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user></users>)";

    vector <treeNode*> test = totree(str);

    //testing
    vector<string> tester1;
    node_to_vector(test, tester1);
    for (int i = 0; i < tester1.size(); i++)cout << i << ": " << tester1[i] << endl;

    cout << "-------------------------" << endl;

    prettify(tester1);
    for (int i = 0; i < tester1.size(); i++) {
        cout << tester1[i];
    }
    cout << "-------------------------" << endl;

    prettify(x);
    for (int i = 0; i < x.size(); i++) {
        cout << x[i];
    }
    cout << "-------------------------" << endl;

    vector<string> tester2;
    node_to_vector(y, tester2);
    prettify(tester2);
    for (int i = 0; i < tester2.size(); i++) {
        cout << tester2[i];
    }

}