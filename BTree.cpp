#include "BTree.h"

#include <iostream>
#include <vector>


BTree::BTree(int t){
    order = t;
    root = NULL;
}

BTree::~BTree(){
    root = NULL;
}

bool BTree::Search(int key) const{
    return root->Search(key);
}

void BTree::NewRoot(){
    Node* new_root = new Node();
    root->SetParent(new_root);
    new_root->InsertChild(root, 0);
    new_root->SplitOverFlowChild(order);
    root = new_root;
}

void BTree::Insert(int key){
    if(root == NULL)
        root = new Node();
    Node* node = root->WhereToInsert(key);
    if(node->InsertHere(key, order)){
        if(node->IsRoot())
            NewRoot();
        else{
            do{
                node = node->GetParent();
                node->SplitOverFlowChild(order);
            } while(!node->IsRoot() && node->IsOverFlow(order));
            if(node->IsRoot() && node->IsOverFlow(order))
                NewRoot();
        }
    }
}

void BTree::Delete(int key){
    root = root->DeleteKey(key, order);
}

void BTree::Report() const{
    cout << "BTree:" << endl;
    root->Report();
}
