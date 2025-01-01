#include "CMD.h"

using namespace std;

void command_line (int argc,char* argv []){
    int i = 1;
    LZ77Compressor compression_obj;
    LZ77Decompressor decompression_obj;
    while (i < argc){
        if (!strcmp(argv[i],"verify")){             //done
            string xml ="";
            bool correct_code = false,valid = false;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
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
                if(temp.first){
                    valid = true;
                    cout<<endl<<"valid"<<endl;
                }
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
                    correct_code = true;
                    i++; // to see the next element
                }
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    if(correct_code && !valid)writeback_file(correct_xml(xml),file);
                    else{
                        ofstream fi(file,ios::out);
                        if (fi.is_open()) {
                            fi << xml;
                            fi.close();
                        }
                        else {
                        cout << "Error opening file!" << endl;
                        }
                    }

                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] , "format")){       //john done
            vector<string> xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
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
        else if (!strcmp(argv[i] , "json")){         //jessy done
            string xml ="";
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
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
                //xml = finalJson(test);
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
        else if (!strcmp(argv[i] , "compress")){     // john compression done
            string xml ="";
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
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
        else if (!strcmp(argv[i] , "decompress")){   // decompression john done
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
        else if (!strcmp(argv[i] , "draw")){        // draw done
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
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
                
                i++;
                if(!strcmp(argv[i],"-o")){
                    i++;
                    string file = argv[i];
                    draw_graph(xml ,file);
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"most_active")){  // most active done
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
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
                auto tempRet = get_most_active(xml); 
                cout <<"Most active user: " << tempRet .first<< " " << tempRet.second<<  endl;
                i++;
            }
        }
        else if (!strcmp(argv[i] ,"most_influencer")){ //most influencer done
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
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
                auto tempRet = get_most_influencer(xml); 
                cout <<"Most influencer user: " <<  tempRet.first << " " << tempRet.second <<endl;
                i++;
            }
        }
        else if (!strcmp(argv[i] ,"mutual")){           //mutual done;
            string xml;
            i++;
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
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

                i++;
                if(!strcmp(argv[i],"-ids")){
                    i++;
                    string IDs_number = argv [i];
                    vector <long> IDs;
                    string temp ="";
                    for (int j = 0; j < IDs_number.size(); j++){
                        if(IDs_number[j]==','){
                            IDs.push_back(stoi(temp));
                            temp="";
                        }
                        else temp += IDs_number[j];
                    }
                    IDs.push_back(stoi(temp));
                    vector<long> mutual;
                    mutual = get_mutual(xml,IDs);
                    if(mutual.empty())cout<<"No mutual users! "<<endl;
                    else{
                        cout<<"Mutual users: ";
                        for(long y : mutual){
                            cout<< y<<", ";
                        }
                        cout<<endl;
                    }
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
                i++;
                if(!strcmp(argv[i],"-id")){
                    i++;
                    string IDs_number = argv [i];
                    int IDs;
                    IDs = stoi(IDs_number);
                    vector<long> suggested;
                    suggested = get_suggest(xml,IDs);
                    if(suggested.empty()) cout << "No suggested users! " <<endl;
                    else{
                        cout<<"suggested users: ";
                        for(long y : suggested){
                            cout<< y <<", ";
                        }
                        cout<<endl;
                    }
                    i++;
                }
            }
        }
        else if (!strcmp(argv[i] ,"search")){
            string xml,word_topic;
            bool word;
            i++;
            if(!strcmp(argv[i],"-w")){
                i++;
                word_topic = argv[i];
                word = true;
                i++;
            }
            if(!strcmp(argv[i],"-t")){
                i++;
                word_topic = argv[i];
                word = false;
                i++;
            }
            if(!strcmp(argv[i],"-i")){
                i++;
                string file_name = argv [i];
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
                if(word){
                    vector <string> byword;
                    cout <<"ser by word: " << word_topic << endl;
                    byword = search_by_word (xml, word_topic);
                    if(byword.empty())cout<<"No posts found! "<<endl;
                    else{
                        cout << "posts using this word: "<<endl;
                        int j = 1;
                        for (string temp : byword){
                            cout << "post number " <<j<<": "<<endl<<temp<<endl;
                            j++;
                        }
                    }
                }
                else{
                    vector <string> bytopic;
                    cout << "ser by topic: " << word_topic << endl;
                    bytopic = search_by_topic  (xml, word_topic);
                    if(bytopic.empty())cout<<"No posts with this topic found! "<<endl;
                    else{
                        cout << "posts using this topic: "<<endl;
                        int j = 1;
                        for (string temp : bytopic){
                            cout << "post number " <<j<<": "<<endl<<temp<<endl;
                            j++;
                        }
                    }
                }
                i++;
            }
        }
        else{
            cout<<"no valid command"<<endl;
            break;
        }
    }
    cout.flush();
    cout<<endl;
}
