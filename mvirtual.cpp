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

        void addPage(int page, int marcoPagina){        // So Tired by Ozzy Osbourne is quite the mood right now.
            table[page].push_back(marcoPagina);
        }

        void removePage(int page){                      // I still need to prepare my presentation for Topics in Management of Large Volumes of Data.
            if(table.find(page) != table.end()){
                table[page].pop_front();
            }
        }

        int frameGetter(int page){
            if(table.find(page) != table.end() && !table[page].empty()){    // It's just you and me, anxiety attack.
                return table[page].front();
            }else{
                return -1;
            }
        }
}

class VMSim{
    private:
        int numFrames;
        string algoritmo_de_reemplazo;
        PageTable pageTable;
        queue<int> Frames;
        unordered_map<int, list<int>> marcoMap;
        int pageErrors = 0;
        vector<int> pageReferences;

    public:
        VMSim(int numFrames, string algoritmo_de_reemplazo) : numFrames(numFrames), algoritmo_de_reemplazo(algoritmo_de_reemplazo){}

        void loadReferences(const string &filename){                           // We read the page references from the inputted file and store them in the pageReference vector.
            ifstream file(filename);
            while(file >> page){
                pageReferences.push_back(page);
            }
        }

        void beginSimulation(){                                                // We begin the simulation according to the inputted algorithm.
            if(algoritmo_de_reemplazo == "Optimo"){                            // This reminded me of the Simplex method and I don't like that.
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
            for(int page : pageReferences){
                if(find(Frames.begin(), Frames.end(), page) == Frames.end()){   // If the page isn't in memory...
                    pageErrors++;                                               // We've got ourselves a page error.
                    if(Frames.size() == numFrames){                             // If the size of the stored pages currently in grames is equal to the max number of frames...
                        int removed = Frames.front();                           // We remove the first page in the frames queue.
                        Frames.pop_front();                                     
                        pageTable.removePage(removed);                          // And remove it from the page table.   
                    }
                    Frames.push_back(page);                                     // We add the new page into the queue.
                    pageTable.addPage(page, Frames.size() - 1);                 // And we add it to the page with an updated number of frames.
                }
            }
        }

        void lru(){

        }

        void lru_reloj_simple(){
            
        }
}
