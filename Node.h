#pragma once

#include <vector>
#include <string>

using namespace std;

/**
 * @brief Contains pointer to its parent, keys and child Nodes.
 * 
 */
class Node{
private:
    Node* parent;
    vector<Node*> children;
    vector<int> keys;

    Node* SearchNode(int n);
    Node* FindRoot();
    int GetClosesKeyBig();
    
    Node* SecretDelete(int key, int order);

    Node* DoSomething(int order);

public:
    Node();
    Node(Node* parent);
    ~Node();
    bool Search(int n);
    string GetString() const;
    int GetKeysCount() const;
    int GetNodesCount() const;
    int GetHeight() const;

    void InsertChild(Node* child, int id);
    void SetParent(Node* parent);

    Node* GetParent();
    bool IsOverFlow(int order) const;
    bool IsRoot() const;
    bool InsertHere(int key, int order);
    Node* WhereToInsert(int key);
    void SplitOverFlowChild(int order);

    Node* Delete(int key, int order);
};
