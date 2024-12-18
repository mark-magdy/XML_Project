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

vector <treeNode*> totree(string str_file)
{
    int len;
    signed long long index, level=0, i=0;
    vector <treeNode*> roots;
    stack<treeNode*> parents_list;

    treeNode* slider;
    treeNode* temp_go_back;
    string check_content;

     while(i>-1 && i<(str_file.size()))
        {
            cout<<"i is kaza : "<<i<<endl;
            cout<<"current char is "<<str_file[i]<<"test"<<endl;
            cout<<"next char is :"<<str_file[i+1]<<"test"<<endl<<endl;

         if(str_file[i]=='<' && str_file[i+1]!='/')        //open tag
                {
                    index= str_file.find('>',i);              //look for next >
                    len = index-i-1;                          //to get the str inside the tags

                    if(level==0)
                    {
                         treeNode* Root = new treeNode();
                        Root->identifier = str_file.substr(i+1,len);
                        cout<<"new root...."<<Root->identifier;
                        Root->level = level++;
                        slider=Root;
                    }
                    else{

                        treeNode *new_child = new treeNode();  //pointer to new node
                        new_child->identifier = str_file.substr(i+1,len);
                        new_child->level = level++;

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
                            if(parents_list.size()==1){
                                    cout<<"The End.."<<parents_list.top()->identifier<<endl;
                                    roots.push_back(slider);
                                    cout<<roots[0]->identifier<<endl;
                                    cout<<"Size : "<<roots.size()<<endl;
                                    level =0;
                                    parents_list.pop();
                            }
                            else {

                            temp_go_back = parents_list.top(); //pop the child
                            parents_list.pop();
                            level--;                           // go up a level
                            slider = parents_list.top();
                            temp_go_back->parent = slider;
                            slider->children.push_back(temp_go_back); //adding child to the vector of the parent
                            cout<<"popped: "<<temp_go_back->identifier<<", current"<<slider->identifier<<endl;
                            }

                        }
                        i=str_file.find('<',i+1);  //next open tag
                        cout<<"next index: :"<<i<<endl;
                }
        }

     return roots;
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

void see_roots (vector <treeNode*> test){
    for(int i=0; i<test.size(); i++)
        {
            cout<<"Root : "<<test[i]->identifier<<endl;
        see_tree(test[i]);
    }
}
int main()
{
  string str = R"(<users> <a><c>00</c></a> <b></b> </users> <new> <A> </A> </new>)";
  vector <treeNode*> test = totree(str);

  //testing
  see_roots(test);
  //cout<<test[0]->identifier; //issue
    return 0;
}
