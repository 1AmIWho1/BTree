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

bool BTree::Search(int key) const{
    return this->root->Search(key);
}

void BTree::Insert(int key){
    if(this->root == NULL){
        Node* root = new Node();
        this->root = root;
    }
    root->Insert(key, order);
}

void BTree::Delete(int key){
    this->root->Delete(key, order);
}

void BTree::Report() const{
    cout << "BTree:" << endl;
    root->Report();
}
