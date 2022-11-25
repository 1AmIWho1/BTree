#include "BTree.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


int main(){
    ifstream file;
    file.open("test.txt");
    //file.open("delete_test.txt");
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
    //b.Report();
    b.Delete(46);
    //b.Insert(56);
    //b.Delete(68);
    b.Delete(1);
    b.Delete(17);
    b.Delete(55);
    b.Delete(44);
    b.Delete(4);
    b.Delete(45);
    b.Delete(15);
    b.Delete(9);
    b.Delete(10);
    b.Delete(67);
    b.Delete(2); // ???
    //b.Delete(70);
    //b.Delete(21);
    //b.Delete(5);


    /*b.Delete(3);
    b.Delete(2);
    b.Delete(4);*/


    b.Report();
    return 0;
}
