#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
class beautify{
public:
    void pretty_stack(vector<string>& lines) {
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
                cout << lines[i];
                continue;
            }

            if (s[1] != '/') {
                lines[i] = tabs + lines[i] + '\n';
                cout << lines[i];
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
                cout << lines[i];
            }

        }
    }
};
