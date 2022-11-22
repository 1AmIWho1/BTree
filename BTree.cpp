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

void BTree::Insert(int key){
    if(this->root == NULL){
        Node* root = new Node(true);
        this->root = root;
    }
    /*if(this->root->GetKeys().size() == 2 * order){
        cout << "new root at key " << key << endl;
        Node* new_root = new Node(false);
        this->root->SetParent(new_root);
        new_root->InsertChild(this->root, 0);
        this->root = new_root;
        new_root->SplitChild(key, 0, order);
    }
    else
        root->InsertNotFull(key, order);*/
    Node* node = root->WhereToInsert(key);
    bool split = node->InsertHere(key, order);
    if(split){
        cout << "split needed at key " << key << endl;
        if(node->IsRoot()){
            cout << "new root at key " << key << endl;
            Node* new_root = new Node(false);
            this->root->SetParent(new_root);
            new_root->InsertChild(this->root, 0);
            new_root->SplitOverFlowChild(order);
            this->root = new_root;
        }
        else{
            cout << "else at key " << key << endl;
            //node = node->GetParent();
            do{
                node = node->GetParent();
                node->SplitOverFlowChild(order);
            } while(!node->IsRoot() && node->IsFull(order));
            if(node->IsRoot() && node->IsOverFlow(order)){
                cout << "new root after insert at key " << key << endl;
                Node* new_root = new Node(false);
                this->root->SetParent(new_root);
                new_root->InsertChild(this->root, 0);
                cout << "half done" << endl;
                new_root->SplitOverFlowChild(order);
                this->root = new_root;
            }
        }
    }
}

void BTree::Report() const{
    cout << "BTree:" << endl;
    root->Report();
}
