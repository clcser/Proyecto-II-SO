#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

class PageTable {
    private:
        int num_frames;
        unordered_map<int, list<int>> table;

    public:
        PageTable(int frames) : num_frames(frames) {}

        void add_page(int page, int frame) {
            if (table.size() >= num_frames) {
                throw runtime_error("Insufficient space in frames");
            }
            table[page].push_back(frame);
        }

        void remove_page(int page) {
            if(table.find(page) != table.end()) {
                table[page].pop_front();
            }
        }

        int get_frame(int page) {
            if(table.find(page) != table.end() && !table[page].empty()){
                return table[page].front();
            }
            else {
                return -1;
            }
        }
};

class VMSim {
    private:
        int num_frames;
        string algorithm;
        vector<int> page_references;
        int page_errors = 0;
        PageTable page_table;

        queue<int> fifo_queue;
        unordered_map<int, list<int>> marcoMap;

    public:
        VMSim(int numFrames, string algoritmo_de_reemplazo) : numFrames(numFrames), algoritmo_de_reemplazo(algoritmo_de_reemplazo){}

        void loadReferences(const string &filename){
            int page;
            ifstream file(filename);
            while(file >> page) {
                pageReferences.push_back(page);
            }
        }

        void beginSimulation(){
            if(algoritmo_de_reemplazo == "Optimo"){
                optimo();
            }
            else if(algoritmo_de_reemplazo == "FIFO"){
                fifo();
            }
            else if(algoritmo_de_reemplazo == "LRU"){
                lru();
            }
            else if(algoritmo_de_reemplazo == "LRU Reloj simple"){
                lru_reloj_simple();
            }
            else{
                cout << "Algoritmo " << algoritmo_de_reemplazo << " no compatible." << endl;
            }
        }

        void optimo() {
        }

        void fifo(int page) {
            for(int page : pageReferences) {
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

        void lru() {
        }

        void lru_reloj_simple() {
        }
};

int main(int argc, char* argv[]) {
    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " -m <num_frames> -a <algorithm> -f <reference_file>\n";
        return 1;
    }

    int num_frames = 0;
    string algorithm, reference_file;

    for (int i = 1; i < argc; i += 2) {
        string arg = argv[i];
        if (arg == "-m")
            num_frames = stoi(argv[i + 1]);
        else if (arg == "-a")
            algorithm = argv[i + 1];
        else if (arg == "-f")
            reference_file = argv[i + 1];
        else {
            cerr << "Usage: " << argv[0] << " -m <num_frames> -a <algorithm> -f <reference_file>\n";
            return 1;
        }
    }

    return 0;
}