#include <iostream>
#include <string.h>
#include <vector>
#include <stack>
#include <cctype>
#include <algorithm>

using namespace std;

class treeNode{
    public :
    string identifier;
    string content;
    treeNode * parent; // for navigating back from child to parent
    vector <treeNode *> children;
    long long level;

    treeNode()
    {

    }
};

treeNode* totree(string str_file)
{
    int len;
    long long index, level=0, i=0;
    stack<treeNode*> parents_list;
    treeNode* Root = new treeNode();
    treeNode* slider;
    treeNode* temp_go_back;
    string check_content;

     while(str_file[i]!=NULL)
        {
            cout<<"current char is "<<str_file[i]<<"test"<<endl;
            cout<<"next char is :"<<str_file[i+1]<<"test"<<endl;
             if(i==-1)
                {
                    break;
                }
            else if(str_file[i]=='<' && str_file[i+1]!='/')        //open tag
                {
                    index= str_file.find('>',i);              //look for next >
                    len = index-i-1;                          //to get the str inside the tags

                    if(i==0)
                    {
                        Root->identifier = str_file.substr(i+1,len);
                        Root->level = level;
                        slider=Root;
                    }
                    else{
                        level++;
                        treeNode *new_child = new treeNode();  //pointer to new node
                        new_child->identifier = str_file.substr(i+1,len);
                        new_child->level = level;

                        slider = new_child;
                    }
                    parents_list.push(slider);
                    cout<<"ind: "<<index<<" ,ident: "<<slider->identifier<<endl;
                    i= index + 1; //what is after > ? open tag or content      //<>i
                }
            else if(str_file[i]!='<') //content                 //issue: detecting new lines as content
                {
                    cout<<"content"<<endl;
                    index = str_file.find('<',i);  //look for the end of content
                    cout<<"start of content @ "<<index<<endl;
                    len = index-i;

                    check_content = str_file.substr(i,len);
                    int start = check_content.find_first_not_of(" \n\t");
                    if(start>=0)
                        {
                            check_content = check_content.substr(start,index);
                            start = check_content.find("\n");
                            if(start > 0)
                            {
                                slider->content = check_content.substr(0,start);
                                cout<<"theres newline @ "<<start<<" cont:"<<slider->content<<endl;
                            }
                            else
                            {
                                slider->content = check_content;
                                cout<<check_content<<endl;
                            }

                        }
                    else
                        {
                            cout<<"NO CONTENT"<<endl;
                        }
                    i=index;                      //next char is new open tag
                }
            else if (str_file[i]=='<' && str_file[i+1]=='/') //closing tag
                {
                    if(slider->identifier==parents_list.top()->identifier)
                        {
                            temp_go_back = parents_list.top(); //pop the child
                            parents_list.pop();
                            level--;                           // go up a level
                            slider = parents_list.top();
                            temp_go_back->parent = slider;
                            slider->children.push_back(temp_go_back); //adding child to the vector of the parent
                            cout<<"popped: "<<temp_go_back->identifier<<", current"<<slider->identifier<<endl;

                        }
                        i=str_file.find('<',i+1);  //next open tag
                        cout<<"next index: :"<<i<<endl;
                }
        }

     return Root;
}

void see_tree( treeNode * test)
{

    cout<<"current : "<<test->identifier<<" "<<test->content<<endl;
    if(test->children.size() == 0)
        {
            cout<<"no kids"<<endl;
            return ;
        }
    else
        {

        for(int i=0; i<test->children.size();i++)
            {
                see_tree(test->children[i]);
            }
    }

}
int main()
{
  string str = R"(<users><user><id>
            1
        </id>
        <name>
            Ahmed Ali
        </name>
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
    </user>)";
  treeNode* test = totree(str);

  //testing
  see_tree(test);
  //cout<<"followers id "<< test->children[0]->children[3]->children[0]->children[0]->content; //issue
    return 0;
}
