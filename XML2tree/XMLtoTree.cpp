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

    treeNode* slider = new treeNode(); 
    treeNode* temp_go_back;
    string check_content;

     while(i>-1 && i<(str_file.size()))
        {

         if(str_file[i]=='<' && str_file[i+1]!='/')        //open tag
                {
                    index= str_file.find('>',i);              //look for next >
                    len = index-i-1;                          //to get the str inside the tags

                    if(level==0)
                    {
                         treeNode* Root = new treeNode();
                        Root->identifier = str_file.substr(i+1,len);
                        
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
                    
                    i= index + 1; //what is after > ? open tag or content      //<>i
                }
            else if(str_file[i]!='<') //content                 //issue: detecting new lines as content
                {
                    
                    index = str_file.find('<',i);  //look for the end of content
                    
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
                            }
                            else
                            {
                                slider->content = check_content;
                            }

                        }
                    else
                        {
                            //cout<<"NO CONTENT"<<endl;
                        }
                    i=index;                      //next char is new open tag
                }
            else if (str_file[i]=='<' && str_file[i+1]=='/') //closing tag
                {


                    if(slider->identifier==parents_list.top()->identifier)
                        {
                            if(parents_list.size()==1){
                                    roots.push_back(slider);
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
                            }

                        }
                        i=str_file.find('<',i+1);  //next open tag
                }
        }

     return roots;
}

void see_tree( treeNode * test)
{

    cout<<"current : "<<test->identifier<<" "<<test->content<<endl;
    if(test->children.size() == 0)
        {
            //cout<<"no kids"<<endl;
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
            //cout<<"Root : "<<test[i]->identifier<<endl;
        see_tree(test[i]);
    }
}
