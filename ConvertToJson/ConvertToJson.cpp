//
// Created by Jessica on 12/29/2024.
//

#include "ConvertToJson.h"

string treeToJson(treeNode* node, int indentLevel = 0, bool square = false, int rep = 0) {
    if (!node) return "";

    string json;
    string indent(indentLevel * 4, ' ');        // Current level indentation
    string childIndent((indentLevel + 1) * 4, ' '); // Child level indentation


    // Handle leaf node
    if (node->children.empty()) {

        // If content is empty, just return the identifier
        if (node->content.empty()) {
            return indent + "\"" + node->identifier + "\"";
        }
        if (!square) {
            return indent + "\"" + node->identifier + "\": \"" + node->content + "\"";
        }
        else
        {
            if (rep == 0)
            {
                return indent + "\"" + node->identifier + "\": [\n" + childIndent + "\"" + node->content + "\"";
            }
            else
            {
                return childIndent + "\"" + node->content + "\"";
            }
        }
    }
    // Check if children should be treated as an array
    bool isArray = false;
    if (node->children.size() > 1) {
        isArray = std::all_of(node->children.begin(), node->children.end(),
            [&](treeNode* child) { return child->identifier == node->children[0]->identifier; });
    }

    if (!square) {
        // Array of children
        json += indent + "\"" + node->identifier + "\": ";
        json += "{\n";
        if (isArray)
        {
            for (size_t i = 0; i < node->children.size(); ++i) {
                // Recursively convert children
                string childJson;
                if (i == 0)
                    childJson = treeToJson(node->children[i], indentLevel + 1, isArray, 0);
                else if (i == node->children.size() - 1)
                    childJson = treeToJson(node->children[i], indentLevel + 1, isArray, 2);
                else
                    childJson = treeToJson(node->children[i], indentLevel + 1, isArray, 1);

                json += childJson;

                if (i < node->children.size() - 1) {
                    json += ",\n";
                }
            }
            if (node->children[0]->children.empty())
            {
                json += "\n" + childIndent + "]";
            }
        }
        else
            for (size_t i = 0; i < node->children.size(); ++i) {
                // Recursively convert children
                string childJson = treeToJson(node->children[i], indentLevel + 1, isArray, 0);

                json += childJson;

                if (i < node->children.size() - 1) {
                    json += ",\n";
                }
            }
        json += "\n" + indent + "}";
    }
    else {//rep or not
        // Object with nested children
        if (!rep)
        {
            json += indent + "\"" + node->identifier + "\": ";
            json += "[\n";
        }

        json += childIndent + "{\n";
        for (size_t i = 0; i < node->children.size(); ++i) {
            json += treeToJson(node->children[i], indentLevel + 2, isArray);
            if (i < node->children.size() - 1) {
                json += ",\n";
            }
        }
        json += "\n" + childIndent + "}";
        if (rep == 2)
            json += "\n" + indent + "]";
    }

    return json;
}

string finalJson(vector <treeNode*> test) {

    string finalJson2 = "{\n";
    for (size_t i = 0; i < test.size(); ++i) {
        finalJson2 += treeToJson(test[i], 1, false);
        if (i < test.size() - 1) {
            finalJson2 += ",\n";
        }
    }
    finalJson2 += "\n}";

    // Output the final JSON
    return finalJson2;
}




/*
int main() {
    string str = R"(<users>
    <user>
        <id>1</id>
        <name>Ahmed Ali</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        economy
                    </topic>
                    <topic>
                        finance
                    </topic>
                </topics>
            </post>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        solar_energy
                    </topic>
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
                    <topic>
                        education
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
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
                    <topic>
                        sports
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
            </follower>
        </followers>
    </user>
</users>)";
    vector<treeNode*> test = totree(str);

    // Convert each root to JSON
    string json = finalJson(test);
    cout << json << endl;

    return 0;
}
*/