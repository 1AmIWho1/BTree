#pragma once

#include <vector>

using namespace std;


class Node{
private:
    Node* parent;
    vector<Node*> children;
    vector<int> keys;
    bool leaf;

    Node* SearchNode(int n);

public:
    Node(bool leaf);
    Node(Node* parent);
    ~Node();
    bool Search(int n);
    void Report() const;
    vector<int> GetKeys() const;

    void InsertChild(Node* child, int id);
    void SetParent(Node* parent);
    void SplitChild(int key, int id, int m);
    void InsertNotFull(int key, int m);

    Node* GetParent();
    bool IsFull(int order);
    bool IsOverFlow(int order);
    bool IsRoot();
    bool InsertHere(int key, int order);
    Node* WhereToInsert(int key);
    void SplitOverFlowChild(int order);
};
