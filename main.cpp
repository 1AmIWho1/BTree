#include "BTree.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


int main(){
    ifstream file;
    file.open("test.txt");
    int n, m;
    file >> n >> m;
    BTree b(m);
    int key;
    for(int i = 0; i < n; ++i){
        file >> key;
        //cout << "adding " << key << endl;
        b.Insert(key);
        //b->Report();
        //cout << endl;
    }
    file.close();
    b.Report();
    return 0;
}
