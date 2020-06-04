#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
//FUNTION PROTOTYPES
void readFile(string filename, vector<int> & total_rsrcs, vector<vector<int>> & proc_request, vector<vector<int>> & rsrc_assgn);
void graphReduction(vector<vector<int>> & proc_request, vector<vector<int>> & rsrc_assgn, vector<int> & total_rsrcs);

int main(int args, char** argv){
    if (args != 2) {
        cerr << "usage: ./" << argv[0] << " <inputfile>";
        exit(EXIT_FAILURE);
    }
    string filename = argv[1];

    vector<vector<int>> proc_request, rsrc_assgn;
    vector<int> total_rsrcs;

    readFile(filename, total_rsrcs, proc_request, rsrc_assgn);
    
    for(vector<int> proc: proc_request){
        for (int rsrc : proc)
            cerr << '\t' << rsrc;
        cerr << endl;
    }

    for(vector<int> rsrc: rsrc_assgn){
        for (int proc : rsrc)
            cerr << '\t' << proc;
        cerr << endl;
    }

}

void graphReduction(vector<vector<int>> & proc_request, vector<vector<int>> & rsrc_assgn, vector<int> & total_rsrcs){

}

void readFile(string filename, vector<int> & total_rsrcs, vector<vector<int>> & proc_request, vector<vector<int>> & rsrc_assgn){
    ifstream inFile;
    inFile.open(filename);
    string line;
    int num_processes;
    int num_resources;
    while(getline(inFile, line)){
        if (line.empty()) continue;     //skip empty lines
        if (line[0] == '%') continue;   // skip comments

        if (line.find("num_processes=")){
            string parse_num = line.substr(line.find("=")+1);
            num_processes = stoi(parse_num);
            continue;
        }

        if (line.find("num_resources=")){
            string parse_num = line.substr(line.find("=")+1);
            num_processes = stoi(parse_num);
            continue;
        }

        if(total_rsrcs.empty()){
            size_t pos = 0;
            while (pos <= line.length()){
                size_t comma_pos = line.find(",", pos);
                size_t len = comma_pos - pos;
                string parse_num = line.substr(pos, len);
                total_rsrcs.push_back(stoi(parse_num));
                pos = comma_pos + 1;
            }
            continue;
        }

        if (proc_request.size() < num_processes){
            size_t rpos = line.length()-1;
            vector<int> tmp;
            for (int r = num_resources; r > 0; r--){
                size_t comma_pos = line.rfind(",", rpos);
                size_t len = rpos - comma_pos;
                string parse_num = line.substr(comma_pos, len);
                tmp.push_back(stoi(parse_num));
                rpos = comma_pos-1;
            }
            proc_request.push_back(tmp);
            continue;
        }

        if (rsrc_assgn.size() < num_resources){
            size_t pos = 0;
            vector<int> tmp;
            for (int p = 0; p < num_processes; p++){
                size_t comma_pos = line.find(",", pos);
                size_t len = comma_pos - pos;
                string parse_num = line.substr(pos, len);
                tmp.push_back(stoi(parse_num));
                pos = comma_pos + 1;
            }
            rsrc_assgn.push_back(tmp);
            continue;
        }
    }
    inFile.close();
}