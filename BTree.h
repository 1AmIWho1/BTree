#pragma once

#include "Node.h"

#include <vector>

using namespace std;


class BTree{
private:
    Node* root;
    int order;

public:
    BTree(int m);
    ~BTree();
    bool Search(int n) const;
    void Insert(int n);
    void DeleteKey();
    
    void Report() const;
};
