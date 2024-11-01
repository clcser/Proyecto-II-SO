#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
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
}

class VMSim{
    private:
        int numMarcos;
        string algoritmo_de_reemplazo;
        PageTable pageTable;
        queue<int> marcos;
        unordered_map<int, list<int>> marcoMap;
        int pageErrors = 0;
        vector<int> pageReferences;

    public:
        VMSim(int numMarcos, string algoritmo_de_reemplazo) : numMarcos(numMarcos), algoritmo_de_reemplazo(algoritmo_de_reemplazo){}

        void loadReferences(const string &filename){
            ifstream file(filename);
            while(file >> page){
                pageReferences.push_back(page);
            }
        }

        void beginSimulation(){
            if(algoritmo_de_reemplazo == "Optimo"){
                optimo();
            }else if(algoritmo_de_reemplazo == "FIFO"){
                fifo();
            }else if(algoritmo_de_reemplazo == "LRU"){
                lru();
            }else if(algoritmo_de_reemplazo == "LRU Reloj simple"){
                lru_reloj_simple();
            }else{
                cout << "Algoritmo " << algoritmo_de_reemplazo << " no compatible." << endl;
            }
        }

        void optimo(){

        }

        void fifo(){

        }

        void lru(){

        }

        void lru_reloj_simple(){
            
}
