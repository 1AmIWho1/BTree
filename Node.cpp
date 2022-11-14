#include "Node.h"

#include <vector>
#include <iostream>

using namespace std;


Node::Node(){
    this->parent = NULL;
    this->leaf = true;
}

Node::Node(Node* parent){
    this->parent = parent;
    this->leaf = true;
}

Node::Node(Node* parent, bool leaf){
    this->parent = parent;
    this->leaf = leaf;
}

Node::~Node(){
    this->parent = NULL;
    for(Node* node : next)
        node = NULL;
}

Node* Node::SearchNode(int n){
    for(int key : keys)
        if(key == n)
            return this;
    if(leaf)
        return NULL;
    for(int i = 0; i < keys.size() + 1; ++i)
        if((i < keys.size() && n < keys.at(i)) || i == keys.size()){
            Node* ans = next.at(i)->SearchNode(n);
            if(ans != NULL)
                return ans;
        }
    return NULL;
}

void Node::SetParent(Node* parent){
    this->parent = parent;
}

void Node::AddL(Node* child, int key){
    child->SetParent(this);
    this->keys.push_back(key);
    this->next.push_back(child);
}

void Node::AddR(Node* child){
    child->SetParent(this);
    this->next.push_back(child);
}

void Node::Add(Node* child, int mid){
    for(int i = 0; i < keys.size(); ++i)
        if(mid < keys.at(i)){
            this->next.insert(this->next.begin() + (i + 1), child);
            this->keys.insert(this->keys.begin() + i, mid);
            return;
        }
    this->next.push_back(child);
    this->keys.push_back(mid);
}

void Node::InsertKeyHere(int key){
    int i = 0;  
    while(i < keys.size() && key >= keys.at(i))
        ++i;
    if(i < keys.size())
        this->keys.insert(this->keys.begin() + i, key);
    else
        this->keys.push_back(key);
}

void Node::VerySpecialInsert(int key, int m){
    Node* L = new Node(this, false);
    for(int i = 0; i < keys.size() / 2; ++i)
        L->AddL(next[i], keys.at(i));
    L->AddR(next[keys.size() / 2]); 
    Node* R = new Node(this, false);
    for(int i = keys.size() / 2 + 1; i < keys.size(); ++i)
        R->AddL(next[i], keys.at(i));
    R->AddR(next[keys.size()]);
    vector<int> new_keys;
    int mid = keys.at(keys.size() / 2);
    this->keys = {};
    this->next = {};
    this->next.push_back(L);
    this->Add(R, mid);
    this->Insert(key, m);
}

void Node::Insert(int key, int m){
    if(leaf){
        if(keys.size() < m){  // insert key in always sorted keys
            this->InsertKeyHere(key);
            return;
        }
        if(parent == NULL){
            for(int i = 0; i < keys.size() + 1; ++i)
                if(i == keys.size())
                    this->keys.push_back(key);
                else if(key < keys.at(i)){
                    this->keys.insert(this->keys.begin() + i, key);
                    break;
                }

            leaf = false;

            Node* L = new Node();
            L->SetParent(this);
            for(int i = 0; i < keys.size() / 2; ++i)
                L->Insert(keys.at(i), m);

            Node* R = new Node(this);
            for(int i = keys.size() / 2 + 1; i < keys.size(); ++i)
                R->Insert(keys.at(i), m);

            vector<int> new_keys;
            int mid = keys.at(keys.size() / 2);
            this->keys = {};
            this->next.push_back(L);
            this->Add(R, mid);
            return;
        }
        else{
            Node* R = new Node(parent);
            this->InsertKeyHere(key);
            for(int i = keys.size() / 2 + 1; i < keys.size(); ++i)
                R->Insert(keys.at(i), m);
            
            int mid = keys.at(keys.size() / 2);
            parent->Add(R, mid);
            vector<int> new_keys;
            for(int i = 0; i < keys.size() / 2; ++i)
                new_keys.push_back(keys.at(i));
            this->keys = new_keys;
        }
    }
    else{
        if(keys.size() == next.size() - 2){
            this->keys.push_back(key);
            return;
        }
        for(int i = 0; i < keys.size(); ++i)
            if(key < keys.at(i)){
                next[i]->Insert(key, m);
                return;
            }
        if(keys.size() < m){
            next[keys.size()]->Insert(key, m);
            return;
        }
        // if you end up here ypu need the tree to grow up
        this->VerySpecialInsert(key, m);
    }
}

void Node::Delete(int key){

}

bool Node::Search(int n){
    return this->SearchNode(n) == NULL ? false : true;
}

void Node::Report() const{
    for(int key : keys)
        cout << key << " ";
    cout << endl;
    if(leaf)
        return;
    cout << "Children : " << next.size() << endl;
    for(Node* child : next){
        child->Report();
    }
}
