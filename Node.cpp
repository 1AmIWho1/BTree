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

void Node::NewInsert(int key, int m){
    if(this->keys.size() == m){
    }
}

void Node::SplitChild(int id, int m){
    Node* child = this->next[id];
    Node* new_child = new Node(this, child->leaf);
    for(int i = keys.size() / 2 + 1; i < keys.size(); ++i)
        new_child->AddL(next[i], keys.at(i));
    this->keys[id] = keys.at(keys.size() / 2);
    this->next[id + 1] = new_child;
    

    if(!child->leaf){
        for(int i = m / 2 + 1; i < child->next.size(); ++i)
            new_child->next.push_back(child->next.at(i));
        child->next.erase(child->next.begin() + m / 2 + 1, child->next.end());
    }
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

void Node::Delete(int key, int m){
    Node* P = SearchNode(key);
    if(P == NULL)
        return;
    if(P->leaf){
        for(int i = 0; i < P->keys.size(); ++i){
            if(P->keys.at(i) == key){
                for(; i < P->keys.size() - 1; ++i)
                    P->keys[i] = P->keys[i + 1];
            }
        }
        P->keys.erase(P->keys.end() - 1, P->keys.end());
        if(P->keys.size() >= m / 2)
            return;
        Node* R = P->parent;
        Node* S;
        // not finished!!!
    }
    else{
        int id;
        for(int i = 0; i < P->keys.size(); ++i){
            if(P->keys.at(i) == key){
                id = i;
                break;
            }
        }
        if(P->next.at(id)->keys.size() > m / 2){
            int tmp = P->next.at(id)->keys.at(P->next.at(id)->keys.size() - 1);
            P->next[id]->keys.erase(P->next[id]->keys.end() - 1, P->next[id]->keys.end());
            P->keys[id] = tmp;
            return;
        }
        else if(P->next.at(id + 1)->keys.size() > m / 2){
            int tmp = P->next.at(id + 1)->keys.at(0);
            P->next[id + 1]->keys.erase(P->next[id + 1]->keys.begin(), P->next[id + 1]->keys.begin() + 1);
            P->keys[id] = tmp;
            return;
        }
    }
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
