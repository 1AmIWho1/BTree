#pragma once

#include "Node.h"

#include <vector>

using namespace std;


class BTree{
private:
    Node* root;
    int order;

public:
    BTree(int t);
    ~BTree();
    bool Search(int key) const;
    void Insert(int key);
    void Delete(int key);
    void NewRoot();
    void Report() const;
    void Statistic();
};
