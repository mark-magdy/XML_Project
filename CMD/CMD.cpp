#include "CMD_test.h"

using namespace std;

void command_line (int argc,char* argv []){
    int i = 1;
    LZ77Compressor compression_obj;
    LZ77Decompressor decompression_obj;
    while (i < argc){
        if (!strcmp(argv[i],"verify")){             //n2s minaaaa
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
                validation test;
                pair<bool,string> temp = test.check_valid(xml);
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
        else if (!strcmp(argv[i] ,"format")){       //john done
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
                prettify(xml);
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    ofstream fi(file,ios::out);
                    if (fi.is_open()) {
                        for(string x:xml){
                            fi<<x;
                        }
                        fi.close();
                    }
                    else {
                    cout << "Error opening file!" << endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"json")){         //jessy done
            string xml ="";
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
                vector<treeNode*> test = totree(xml);
                xml = finalJson(test);
                i++;
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
        else if (!strcmp(argv[i] , "mini")){        //john mini done
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

                minify(xml);
                
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    ofstream fi(file,ios::out);
                    if (fi.is_open()) {
                        for(string x:xml){
                            fi<<x;
                        }
                        fi.close();
                    }
                    else {
                    cout << "Error opening file!" << endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"compress")){     // john compression done
            string xml ="";
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
                vector<Token> dummy;
                dummy = compression_obj.compress(xml);
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    compression_obj.saveCompressed(file, file);
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"decompress")){   // decompression john done
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
                xml = decompression_obj.decompressFromFile(file_name);
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    decompression_obj.saveDecompressed(xml,file, file);
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
