#include "CMD_test.h"

using namespace std;

void command_line (int argc,char* argv []){
    int i = 1;
    while (i < argc){
        if (!strcmp(argv[i],"verify")){
            string xml ="";
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for verify";
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }
                pair<bool,string> temp ;//= check_valid(string xml)
                if(temp.first) cout<<endl<<"valid"<<endl;
                else{
                    int errors=0;
                    cout<<endl<<"invalid"<<endl<<"Errors number: ";
                    for (int j = 0; j < temp.second.size(); j++){
                        if(temp.second[i]=='\n')errors++;
                    }
                    cout<<errors<<endl;
                    for (int j = 0; j < temp.second.size(); j++){
                        cout<<temp.second[j];
                    }
                }
                i++;
                if(!strcmp(argv[i],"-f")){
                    //fill it
                    // xml = check valid
                    i++; // to see the next element
                }
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    ofstream fi(file,ios::out);
                    if (fi.is_open()) {
                        fi << xml;
                        fi.close();
                    }
                    else {
                    cout << "Error opening file!" << endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"format")){
            vector<string> xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml.push_back(line);
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // xml = pretify;

                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    ofstream fi(file,ios::out);
                    if (fi.is_open()) {
                        // fi << xml;
                        fi.close();
                    }
                    else {
                    cout << "Error opening file!" << endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"json")){
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // xml = json;
                
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    ofstream fi(file,ios::out);
                    if (fi.is_open()) {
                        // fi << xml;
                        fi.close();
                    }
                    else {
                    cout << "Error opening file!" << endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] , "mini")){
            vector<string> xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml.push_back(line);
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // xml = mini;
                
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    ofstream fi(file,ios::out);
                    if (fi.is_open()) {
                        // fi << xml;
                        fi.close();
                    }
                    else {
                    cout << "Error opening file!" << endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"compress")){
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // xml = json;
                
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    ofstream fi(file,ios::out);
                    if (fi.is_open()) {
                        // fi << xml;
                        fi.close();
                    }
                    else {
                    cout << "Error opening file!" << endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"decompress")){
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // xml = json;
                
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    ofstream fi(file,ios::out);
                    if (fi.is_open()) {
                        // fi << xml;
                        fi.close();
                    }
                    else {
                    cout << "Error opening file!" << endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] , "draw")){
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // xml = json;
                
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    ofstream fi(file,ios::out);
                    if (fi.is_open()) {
                        // fi << xml;
                        fi.close();
                    }
                    else {
                    cout << "Error opening file!" << endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"most_active")){
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // cout most activeee;
                i++;
            }
        }
        else if (!strcmp(argv[i] ,"most_influencer")){
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // cout most infulencer;
                i++;
            }
        }
        else if (!strcmp(argv[i] ,"mutual")){
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // cout most activeee;
                i++;
                if(!strcmp(argv[i],"-ids")){
                    i++;
                    string IDs_number = argv [i];
                    vector <int> IDs;
                    string temp ="";
                    for (int j = 0; j < IDs_number.size(); j++){
                        if(IDs_number[j]==','){
                            IDs.push_back(stoi(temp));
                            temp="";
                        }
                        else temp += IDs_number[j];
                    }

                    //ndiniiiii

                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"suggest")){
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }

                // cout most activeee;
                i++;
                if(!strcmp(argv[i],"-id")){
                    i++;
                    string IDs_number = argv [i];
                    int IDs;
                    IDs = stoi(IDs_number);

                    //suggest
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"search")){
            string xml,word_topic;
            i++;
            if(!strcmp(argv[i],"-w")){
                i++;
                word_topic = argv[i];
                i++;
            }
            if(!strcmp(argv[i],"-t")){
                i++;
                word_topic = argv[i];
                i++;
            }
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                cout<<endl<<"ready for format"<<endl;
                ifstream fio(file_name, ios::in);
                if (fio.is_open()) {
                    string line;
                    while (getline(fio, line)) {
                        xml+=line;
                        xml+='\n';
                    }
                    fio.close();
                }
                else {
                    cout << "Error opening file!" << endl;
                }
                // cout most activeee;
                i++;
            }
        }
        else{
            cout<<"no valid command";
            break;
        }
    }
}
