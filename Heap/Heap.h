#pragma once

class Heap {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;

        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* getParentNode(Node* current);
    void heapifyUp(Node* current);
    void heapifyDown(Node* current);
    void inorderTraversal(Node* node);
    void preorderTraversal(Node* node);
    void postorderTraversal(Node* node);
    Node* removeNode(Node* node, int value); 
    Node* findMin(Node* node);


public:
    Heap();
    void insert(int value);
    void remove(int value);
    void inorder();
    void preorder();
    void postorder();
};

