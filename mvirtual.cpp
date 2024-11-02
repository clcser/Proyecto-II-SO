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

class VMSim{                                            // Activate Protocol: Death by Caffeine Overdose.
    private:
        int numFrames;
        string algoritmo_de_reemplazo;
        PageTable pageTable;
        queue<int> frames;
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
                if(find(frames.begin(), frames.end(), page) == frames.end()){   // If the page isn't in memory...
                    pageErrors++;                                               // We've got ourselves a page error.
                    if(frames.size() == numFrames){                             // If the size of the stored pages currently in frames is equal to the max number of frames...
                        int removed = frames.front();                           // We remove the first page in the frames queue.
                        frames.pop_front();                                     
                        pageTable.removePage(removed);                          // And remove it from the page table.   
                    }
                    frames.push_back(page);                                     // We add the new page into the queue.
                    pageTable.addPage(page, frames.size() - 1);                 // And we add it to the page table with an updated number of frames.
                }
            }
        }

        void lru() {
        for(int page : pageReferences){                                 // Loop over each page reference in the sequence
            auto it = find(frames.begin(), frames.end(), page);         // Search for the page in the current frames
            if(it == frames.end()){                                     // If the page isn't in memory...
                pageErrors++;                                           // page error wooo!!!
                if(frames.size() == numFrames){                         // If the size of the stored pages currently in frames is equal to the max number of frames...
                    int removed = frames.front();                       // Remove the oldest page in the frames queue...
                    frames.pop_front();                                 
                    pageTable.removePage(removed);                      // And from the page table.
                }
            
                frames.push_back(page);                                 // Add the new page to the back of the frames to indicate most recent use
        
            } else {                                                    // If the page is already in memory...
                frames.erase(it);                                       // Remove the existing page from its current position
                frames.push_back(page);                                 // Reinsert it at the back to mark it as most recently used.
            }
            pageTable.addPage(page, frames.size() - 1);                 // Update the page table to reflect the page's position in frames
        }
    }

    void lru_reloj_simple(){                                    
        vector<int> use_bit(numFrames, 0);                              // We initialize the "clock" vector, with all its positions in 0 to indicate they're associated to an "lru-page". 
        int clock_hand = 0;                                             // "Clock" clock_hand starts at hour 0 haha cute :3      
        for(int page : references){                                     // Loop over each page reference in the sequence.
            if(find(frames.begin(), frames.end(), page) == frames.end()){   // If the page isn't in memory...
                pageFaults++;                                           // Ayo people we've got a page error yo
                while(use_bit[clock_hand] == 1){                        // While the bit currently pointed by the clock's clock_hand is 1 (recently used page)
                    use_bit[clock_hand] = 0;                            // Set it to 0 (no longer recently used :C)
                    clock_hand = (clock_hand + 1) % numFrames;          // Move the clock's hand to the next position. (We get the % because this is a clock and is CIRCULAR :D)
                }                                                       // REMINDER: If the while ends, that means that the clock's hand is pointing to a page with a 0 bit (recently unused page).

                if (frames.size() == numFrames) {                       // If the size of the stored pages currently in frames is equal to the max number of frames...
                    pageTable.removePage(frames[clock_hand]);           // We remove the page currently pointed at by the clock's hand from the page table.
                    frames[clock_hand] = page;                          // And replace it with the page pointed at by the clock's hand.
                }else{                                                  // If there is space...
                    frames.push_back(page);                             // Add the new page to the frames queue.
                }
                use_bit[clock_hand] = 1;                                // Set the bit pointed at by the clock's hand to 1 to indicate it has just been used.
                pageTable.addPage(page, clock_hand);                    // And we add the page to the page tabel.
                clock_hand = (clock_hand + 1) % numFrames;              // Then we update the clock's hand.
            }else{                                                      // If the page is already in memory...
                int index = distance(frames.begin(), find(frames.begin(), frames.end(), page)); // Update its use bit to 1... Because Gamers don't die, they respawn.
                use_bit[index] = 1;
            }
        }
    }
}