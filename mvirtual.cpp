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
}
