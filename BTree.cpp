#include "BTree.h"

#include <iostream>
#include <vector>


BTree::BTree(int m){
    this->order = m;
    this->root = NULL;
}

BTree::~BTree(){
    this->root = NULL;
}

bool BTree::Search(int n) const{
    return this->root->Search(n);
}

void BTree::Insert(int n){
    if(this->root == NULL){
        Node* root = new Node();
        this->root = root;
    }
    root->Insert(n, order);
}

void BTree::Report() const{
    cout << "BTree:" << endl;
    root->Report();
}
