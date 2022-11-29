#pragma once

#include "Node.h"

#include <vector>

using namespace std;

/**
 * @brief 
 * 
 */
class BTree{
private:
    Node* root;
    int order;

    void NewRoot();

public:
    BTree(int t);
    ~BTree();
    bool Search(int key) const;
    void Insert(int key);
    void Delete(int key);
    void Output() const;
    void Statistic() const;
};
