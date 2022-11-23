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

void Node::InsertChild(Node* child, int id){
    this->children.insert(this->children.begin() + id, child);
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
        if(children.at(id)->IsOverFlow(order))
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
    InsertChild(z, id + 1);
}

void Node::DeleteKey(int key, int order){
    Node* node = SearchNode(key);
    if(node == NULL)
        return;
    if(!node->children.size()){
        int id = 0;
        for(; id < node->keys.size(); ++id)
            if(key == node->keys.at(id)){
                break;
            }
        if(node->keys.size() > order){
            node->keys.erase(node->keys.begin() + id);
            return;
        }
        node->keys.erase(node->keys.begin() + id);

    }
}
