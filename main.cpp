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
    int key;
    do{
        file >> type;
        if(type == 'i'){
            int n;
            file >> n;
            for(int i = 0; i < n; ++i){
                file >> key;
                b.Insert(key);
            }
        }
        else if(type == 'd'){
            int n;
            file >> n;
            for(int i = 0; i < n; ++i){
                file >> key;
                b.Delete(key);
            }
        }
        else if(type == 'o')
            b.Report();
    } while(type != 'e');
    file.close();
    return 0;
}
