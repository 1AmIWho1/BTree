#pragma once

#include <vector>

using namespace std;


class Node{
private:
    Node* parent;
    vector<Node*> next;
    vector<int> keys;
    bool leaf;

    void SetParent(Node* parent);
    void Add(Node* child, int mid);
    void AddL(Node* child, int key);
    void AddR(Node* child);
    void VerySpecialInsert(int key, int m);
    void InsertKeyHere(int key);
    Node* SearchNode(int n);
    void SplitChild(int id, int m);

public:
    Node();
    Node(Node* parent);
    Node(Node* parent, bool leaf);
    ~Node();
    void NewInsert(int key, int m);
    void Insert(int key, int m);
    bool Search(int n);
    void Delete(int key, int m);
    void Report() const;
};
