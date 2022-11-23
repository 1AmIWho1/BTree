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
    //b.Report();
    b.Delete(3);
    b.Delete(7);
    b.Delete(8);
    b.Delete(6);
    b.Delete(22);
    b.Report();
    //b.Delete(46);
    b.Insert(56);
    b.Delete(68);
    b.Report();
    return 0;
}
