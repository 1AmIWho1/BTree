#include "BTree.h"

#include <iostream>
#include <fstream>

using namespace std;


int main(){
    ifstream file;
    file.open("input.txt"); // has same input as in the presentation
    int order;
    file >> order;
    BTree b(order);
    char type;
    do{
        file >> type;
        if(type == 'i'){
            int n, key;
            file >> n;
            for(int i = 0; i < n; ++i){
                file >> key;
                b.Insert(key);
            }
        }
        else if(type == 'd'){
            int n, key;
            file >> n;
            for(int i = 0; i < n; ++i){
                file >> key;
                b.Delete(key);
            }
        }
        else if(type == 'o')
            b.Report();
        else if(type == 's')
            b.Statistic();
    } while(type != 'e');
    file.close();
    return 0;
}
