#pragma once

#include <vector>

using namespace std;


class Node{
private:
    Node* parent;
    vector<Node*> children;
    vector<int> keys;

    Node* SearchNode(int n);
    Node* FindRoot();
    int GetClosesKeyBig();
    int GetKeysCount() const;
    int GetNodesCount() const;
    int GetHeight() const;

    Node* DoSomething(int order);

public:
    Node();
    Node(Node* parent);
    ~Node();
    bool Search(int n);
    void Report() const;

    void InsertChild(Node* child, int id);
    void SetParent(Node* parent);

    Node* GetParent();
    bool IsOverFlow(int order) const;
    bool IsRoot() const;
    bool InsertHere(int key, int order);
    Node* WhereToInsert(int key);
    void SplitOverFlowChild(int order);

    Node* DeleteKey(int key, int order);
    void Statistic();
};
