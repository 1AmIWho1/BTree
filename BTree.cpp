#include "BTree.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>


/**
 * @brief Construct a new BTree object
 * 
 * @param t order of BTree
 */
BTree::BTree(int t){
    order = t;
    root = NULL;
}

BTree::~BTree(){
    root = NULL;
}

/**
 * @brief Checks, if key is containted in the BTree
 * 
 * @param key key to look for
 * @return true if BTree contains key
 * @return false if BTree doesn't contain key
 */
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

/**
 * @brief Inserts new key into BTree
 * 
 * @param key key to be insterted
 */
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

/**
 * @brief Deletes key from tree
 * 
 * @param key key to delete
 */
void BTree::Delete(int key){
    root = root->Delete(key, order);
}
/**
 * @brief Outputs BTree to consol
 * 
 */
void BTree::Output() const{
    cout << "BTree:" << endl;
    root->Output();
}

void BTree::OutputToFile(string file_name, bool append) const{
    ofstream file;
    if(append){
        file.open(file_name, ios_base::app);
        file << endl;
    }
    else
        file.open(file_name);
    file << "test";
    file.close();
}

/**
 * @brief Outputs brief information about BTree
 * 
 */
void BTree::Statistic() const{
    cout << "BTree statistic:" << endl;
    root->Statistic();
}
