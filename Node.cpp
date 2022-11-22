#include "Node.h"

#include <vector>
#include <iostream>

using namespace std;


Node::Node(bool leaf){
    this->parent = NULL;
    this->leaf = leaf;
}

Node::Node(Node* parent){
    this->parent = parent;
}

Node::~Node(){
    this->parent = NULL;
    for(Node* node : children)
        node = NULL;
}

Node* Node::SearchNode(int n){
    for(int key : keys)
        if(key == n)
            return this;
    if(!children.size())
        return NULL;
    for(int i = 0; i < keys.size() + 1; ++i)
        if((i < keys.size() && n < keys.at(i)) || i == keys.size()){
            Node* ans = children.at(i)->SearchNode(n);
            if(ans != NULL)
                return ans;
        }
    return NULL;
}

void Node::SetParent(Node* parent){
    this->parent = parent;
}

bool Node::Search(int n){
    return this->SearchNode(n) == NULL ? false : true;
}

void Node::Report() const{
    for(int key : keys)
        cout << key << " ";
    cout << endl;
    if(!children.size())
        return;
    cout << "Children : " << children.size() << endl;
    for(Node* child : children)
        child->Report();
}

vector<int> Node::GetKeys() const{
    //vector<int> keys(this->keys);
    return this->keys;
}

void Node::InsertChild(Node* child, int id){
    this->children.insert(this->children.begin() + id, child);
}

void Node::SplitChild(int key, int id, int order){
    Node* y = this->children[id];
    Node* z = new Node(this);

    z->keys.insert(z->keys.begin(), y->keys.begin() + order, y->keys.end());
    y->keys.erase(y->keys.begin() + order, y->keys.end());

    if(y->children.size()){
        z->children.insert(z->children.begin(), y->children.begin() + order + 1, y->children.end());
        y->children.erase(y->children.begin() + order + 1, y->children.end());
    }
    InsertChild(z, id + 1);
    int l = y->keys.at(y->keys.size() - 1);
    int r = z->keys.at(0);

    //cout << key << " l = " << l << " r = " << r << endl;
    if(l < key && key < r){
        //keys.push_back(key);
        keys.insert(keys.begin() + id, key);
        return;
    }
    if(key > r){
        int i = 0;
        for(; i < z->keys.size(); ++i){
            if((i < z->keys.size() && key < z->keys.at(i)) || (i == z->keys.size()))
                break;
        }
        if(z->children.size()){
            //z->children[z->children.size() - 1]->SplitChild(key, i, order);
            cout << i << " " << key << endl;
            z->SplitChild(key, i - 1, order);
            return;
        }
        keys.insert(keys.begin() + id, z->keys.at(0));
        z->keys[0] = key;
        return;
    }
    if(key < l){
        keys.insert(keys.begin() + id, y->keys.at(y->keys.size() - 1));
        y->keys[y->keys.size() - 1] = key;
        return;
    }
}

void Node::InsertNotFull(int key, int order){
    if(!children.size()){
        for(int i = 0; i < keys.size() + 1; ++i)
            if((i < keys.size() && key < keys.at(i)) || (i == keys.size())){
                this->keys.insert(this->keys.begin() + i, key);
                return;
            }
    }
    else{
        int i = 0;
        for(; i < keys.size() + 1; ++i)
            if((i < keys.size() && key < keys.at(i)) || (i == keys.size()))
                break;
        if(children.at(i)->GetKeys().size() == 2 * order){
            SplitChild(key, i, order);
            if(key > keys.at(i))
                ++i;
        }
        else
            this->children[i]->InsertNotFull(key, order);
    }
}

Node* Node::GetParent(){
    return parent;
}

bool Node::IsRoot(){
    return parent == NULL;
}

bool Node::IsOverFlow(int order){
    return keys.size() > 2 * order;
}

bool Node::IsFull(int order){
    return keys.size() == 2 * order;
}

bool Node::InsertHere(int key, int order){
    for(int i = 0; i < keys.size() + 1; ++i)
        if((i < keys.size() && key < keys.at(i)) || (i == keys.size())){
            keys.insert(keys.begin() + i, key);
            break;
        }
    return keys.size() > 2 * order;
}

Node* Node::WhereToInsert(int key){
    if(!children.size())
        return this;
    int i = 0;
        for(; i < keys.size() + 1; ++i)
            if((i < keys.size() && key < keys.at(i)) || (i == keys.size()))
                break;
    return children.at(i)->WhereToInsert(key);
}

void Node::SplitOverFlowChild(int order){
    int id = 0;
    for(; id < children.size(); ++id)
        if(children.at(id)->keys.size() > 2 * order)
            break;
    
    Node* y = this->children[id];
    Node* z = new Node(this);
    int mid = y->keys.at(order);
    keys.insert(keys.begin() + id, mid);

    z->keys.insert(z->keys.begin(), y->keys.begin() + order + 1, y->keys.end());
    y->keys.erase(y->keys.begin() + order, y->keys.end());

    if(y->children.size()){
        z->children.insert(z->children.begin(), y->children.begin() + order + 1, y->children.end());
        y->children.erase(y->children.begin() + order + 1, y->children.end());
    }
    children.insert(children.begin() + id + 1, z);
    //InsertChild(z, id + 1);
}
