#pragma once

#include "Node.h"

#include <vector>
#include <string>

using namespace std;

/**
 * @brief Class used for storing order and pointer to root of BTree. 
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
    void OutputToFile(string file_name, bool append) const;
    void Statistic() const;
};
