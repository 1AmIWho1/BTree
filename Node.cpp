#include "Node.h"

#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Construct a new Node object
 * 
 */
Node::Node(){
    this->parent = NULL;
}

/**
 * @brief Construct a new Node object with known parent
 * 
 * @param parent this Node's parent
 */
Node::Node(Node* parent){
    this->parent = parent;
}

Node::~Node(){
    this->parent = NULL;
    for(Node* node : children)
        node = NULL;
}

/**
 * @brief Recursively searches for Node which has key
 * 
 * @param key key to search
 * @return Node* pointer to Node, which contains key
 */
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

/**
 * @brief Sets new parent for node
 * 
 * @param parent New parent
 */
void Node::SetParent(Node* parent){
    this->parent = parent;
}

/**
 * @brief Checks, if tree obrains this key
 * 
 * @param key
 * @return true if there's key in this Node or in this Node's children
 * @return false if neither this Node or its children do not contan this key
 */
bool Node::Search(int key){
    return SearchNode(key) == NULL ? false : true;
}

int Node::GetKeysCount() const{
    int res = keys.size();
    for(Node* child : children)
        res += child->GetKeysCount();
    return res;
}

int Node::GetNodesCount() const{
    int res = 1;
    for(Node* child : children)
        res += child->GetNodesCount();
    return res;
}

int Node::GetHeight() const{
    if(!children.size())
        return 1;
    int height = 1;
    Node* node = children.at(0);
    while(true){
        ++height;
        if(!node->children.size())
            return height;
        node = node->children.at(0);
    }
}

/**
 * @brief Outputs information about BTree
 * 
 */
void Node::Statistic(){
    cout << "Nodes: " << GetNodesCount() << endl;
    cout << "Keys: " << GetKeysCount() << endl;
    cout << "Height: " << GetHeight() << endl;
}

/**
 * @brief Outputs BTree
 * 
 */
void Node::Output() const{
    /*if(parent != NULL)
        cout << "(" << parent->keys.at(0) << ") ";*/
    for(int key : keys)
        cout << key << " ";
    cout << endl;
    if(!children.size())
        return;
    cout << "Children : " << children.size() << endl;
    for(Node* child : children)
        child->Output();
}

/**
 * @brief Inserts another Node in this Node's children
 * 
 * @param child Node to be inserted
 * @param id where Node needs to be inserted
 */
void Node::InsertChild(Node* child, int id){
    child->SetParent(this);
    children.insert(children.begin() + id, child);
}

/**
 * @brief Returns parent of Node
 * 
 * @return Node* 
 */
Node* Node::GetParent(){
    return parent;
}

/**
 * @brief Checks if this Node is root
 * 
 * @return true if this Node is root
 * @return false if this Node isn't root
 */
bool Node::IsRoot() const{
    return parent == NULL;
}

/**
 * @brief Checks if this Node has more keys than it should
 * 
 * @param order 
 * @return true 
 * @return false 
 */
bool Node::IsOverFlow(int order) const{
    return keys.size() > 2 * order;
}

/**
 * @brief Inserts key in this Node and checks if there's overflow in this Node
 * 
 * @param key 
 * @param order 
 * @return true 
 * @return false 
 */
bool Node::InsertHere(int key, int order){
    for(int i = 0; i < keys.size() + 1; ++i)
        if((i < keys.size() && key < keys.at(i)) || (i == keys.size())){
            keys.insert(keys.begin() + i, key);
            break;
        }
    return IsOverFlow(order);
}

Node* Node::FindRoot(){
    if(parent == NULL)
        return this;
    return parent->FindRoot();
}

/**
 * @brief Looks for Node in which key should be
 * 
 * @param key 
 * @return Node* 
 */
Node* Node::WhereToInsert(int key){
    if(!children.size())
        return this;
    int i = 0;
        for(; i < keys.size() + 1; ++i)
            if((i < keys.size() && key < keys.at(i)) || (i == keys.size()))
                break;
    return children.at(i)->WhereToInsert(key);
}

/**
 * @brief Splits overflowed child of Node
 * 
 * @param order 
 */
void Node::SplitOverFlowChild(int order){
    int id = 0;
    for(; id < children.size(); ++id)
        if(children.at(id)->IsOverFlow(order))
            break;
    
    Node* y = children.at(id);
    Node* z = new Node(this);
    int mid = y->keys.at(order);
    keys.insert(keys.begin() + id, mid);

    z->keys.insert(z->keys.begin(), y->keys.begin() + order + 1, y->keys.end());
    y->keys.erase(y->keys.begin() + order, y->keys.end());

    if(y->children.size()){
        z->children.insert(z->children.begin(), y->children.begin() + order + 1, y->children.end());
        y->children.erase(y->children.begin() + order + 1, y->children.end());
    }
    for(Node* node : z->children)
        node->SetParent(z);
    InsertChild(z, id + 1);
}

/**
 * @brief Looks for closes key in BTree
 * 
 * @return int 
 */
int Node::GetClosesKeyBig(){
    if(!children.size())
        return keys.at(0);
    return children.at(0)->GetClosesKeyBig();
}

Node* Node::DoSomething(int order){ // activates when in current node too few keys
    if(IsRoot()){
        if(!keys.size()){
            keys.insert(keys.begin(), children.at(0)->keys.begin(), children.at(0)->keys.end());
            children.erase(children.begin(), children.end());
            return this;
        }
        if(children.size() == 2 && children.at(0)->keys.size() + children.at(1)->keys.size() + keys.size() <= 2 * order){
            keys.insert(keys.begin(), children.at(0)->keys.begin(), children.at(0)->keys.end());
            keys.insert(keys.begin() + keys.size() - 1, children.at(1)->keys.begin(), children.at(1)->keys.end());
            children.erase(children.begin(), children.end());
            return this;
        }

        int child_id = 0;
        for(; child_id < keys.size(); ++child_id)
            if(children.at(child_id)->keys.size() < order)
                break;
    
        if(children.at(child_id)->keys.size() >= order)
            return this;

        if(children.size() == 2){
            if(child_id == 1){
                children[child_id]->keys.insert(children[child_id]->keys.begin(), keys.at(0));
                keys[0] = children.at(0)->keys.at(children.at(0)->keys.size() - 1);
                children.at(0)->keys.erase(children.at(0)->keys.begin() + children.at(0)->keys.size() - 1);
            }
            else{
                children.at(child_id)->keys.push_back(keys.at(0));
                keys[0] = children.at(1)->keys.at(0);
                children.at(1)->keys.erase(children.at(1)->keys.begin());
            }
            return this;
        }
        if(children.size() == 1 && keys.size() == 0){
            children.at(0)->SetParent(NULL);
            return children.at(0);
        }
    } 
    Node* C = parent;
    int child_id = 0;
    for(; child_id < C->children.size(); ++child_id)
        if(C->children.at(child_id) == this)
            break;
    Node* B;
    if(child_id != C->keys.size())
        B = C->children.at(child_id + 1);
    else
        B = C->children.at(child_id - 1);   

    if(C->IsRoot()){
        if(B->keys.size() + 2 <= 2 * order){
            if(!keys.size() || B->keys.at(0) < keys.at(0)){
                B->keys.push_back(C->keys.at(child_id - 1));
                C->keys.erase(C->keys.begin() + child_id - 1);
                for(int i = 0; i < keys.size(); ++i){
                    B->keys.push_back(keys.at(i));
                    children.at(i)->SetParent(B);
                    B->children.push_back(children.at(i));
                }
                B->children.push_back(children.at(children.size() - 1));
                B->parent = NULL;
                return B;
            }
        }
    }
    return NULL;
}

Node* Node::SecretDelete(int key, int order){
    int id = 0;
    for(; id < keys.size(); ++id)
        if(key == keys.at(id))
            break;

    if(!children.size()){
        keys.erase(keys.begin() + id);
        
        if(keys.size() >= order || parent == NULL)
            return FindRoot();
        
        Node* R = parent;
        int child_id = 0;
        for(; child_id < R->children.size(); ++child_id)
            if(R->children.at(child_id) == this)
                break;

        if(child_id < R->children.size() - 1){
            Node* S = R->children.at(child_id + 1);
            if(S->keys.size() == order){
                keys.push_back(R->keys.at(child_id));
                R->keys.erase(R->keys.begin() + child_id);
                keys.insert(keys.begin() + order, S->keys.begin(), S->keys.end());
                R->children.erase(R->children.begin() + child_id + 1);

                if(R->keys.size() < order)
                    return R->DoSomething(order);

                return FindRoot();
            }
            InsertHere(R->keys.at(child_id), order);
            R->keys[child_id] = S->keys.at(0);
            S->DeleteKey(S->keys.at(0), order);
        }
        else{
            Node* S = R->children.at(child_id - 1);

            if(S->keys.size() == order){
                keys.insert(keys.begin() ,R->keys.at(child_id - 1));
                R->keys.erase(R->keys.begin() + child_id - 1);
                keys.insert(keys.begin(), S->keys.begin(), S->keys.end());
                R->children.erase(R->children.begin() + child_id - 1);

                if(R->keys.size() < order)
                    return R->DoSomething(order);

                return FindRoot();
            }
            
            InsertHere(R->keys.at(child_id - 1), order);
            R->keys[child_id - 1] = S->keys.at(S->keys.size() - 1);
            S->DeleteKey(S->keys.at(S->keys.size() - 1), order);
        }
    }

    else{
        int y = children.at(id + 1)->GetClosesKeyBig();
        children.at(id + 1)->DeleteKey(y, order);
        keys[id] = y;
    }
    return FindRoot();
}

/**
 * @brief Deletes key from BTree
 * 
 * @param key 
 * @param order 
 * @return Node* 
 */
Node* Node::DeleteKey(int key, int order){
    Node* node = SearchNode(key);

    if(node == NULL)
        return FindRoot();

    return node->SecretDelete(key, order);
}
