#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

class PageTable{
    public:
        unordered_map<int, list<int>> table;

        void addPage(int page, int marcoPagina){
            table[page].push_back(marcoPagina);
        }

        void removePage(int page){
            if(table.find(page) != table.end()){
                table[page].pop_front();
            }
        }

        int frameGetter(int page){
            if(table.find(page) != table.end() && !table[page].empty()){
                return table[page].front();
            }else{
                return -1;
            }
        }
};

int main(int argc, char* argv[]) {
    if (argc != 7) {
        cerr << "Uso: " << argv[0] << " -m <num_marcos> -a <algoritmo> -f <archivo_referencias>\n";
        return 1;
    }

    int num_marcos = 0;
    string algoritmo, archivo_referencias;

    for (int i = 1; i < argc; i += 2) {
        string arg = argv[i];
        if (arg == "-m") num_marcos = stoi(argv[i + 1]);
        else if (arg == "-a") algoritmo = argv[i + 1];
        else if (arg == "-f") archivo_referencias = argv[i + 1];
        else {
            cerr << "Uso: " << argv[0] << " -m <num_marcos> -a <algoritmo> -f <archivo_referencias>\n";
            return 1;
        }
    }

    return 0;
}