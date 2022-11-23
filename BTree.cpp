#include "BTree.h"

#include <iostream>
#include <vector>


BTree::BTree(int t){
    this->order = t;
    this->root = NULL;
}

BTree::~BTree(){
    this->root = NULL;
}

bool BTree::Search(int key) const{
    return this->root->Search(key);
}

void BTree::NewRoot(){
    Node* new_root = new Node(false);
    this->root->SetParent(new_root);
    new_root->InsertChild(this->root, 0);
    new_root->SplitOverFlowChild(order);
    this->root = new_root;
}

void BTree::Insert(int key){
    if(this->root == NULL){
        Node* root = new Node(true);
        this->root = root;
    }
    Node* node = root->WhereToInsert(key);
    bool split = node->InsertHere(key, order);
    if(split){
        if(node->IsRoot()){
            NewRoot();
        }
        else{
            do{
                node = node->GetParent();
                node->SplitOverFlowChild(order);
            } while(!node->IsRoot() && node->IsOverFlow(order));
            if(node->IsRoot() && node->IsOverFlow(order)){
                NewRoot();
            }
        }
    }
}

void BTree::Delete(int key){
    root->DeleteKey(key, order);
}

void BTree::Report() const{
    cout << "BTree:" << endl;
    root->Report();
}
