#include <iostream>
#include "Heap.h"

using namespace std;

Heap::Heap() {
    root = nullptr;
}

Heap::Node* Heap::getParentNode(Node* current) {
    if (current == nullptr || current == root)
        return nullptr;

    // Przechodzenie kopca od góry do dołu, w lewo i prawo
    Node* parent = root;
    while (parent->left != current && parent->right != current) {
        if (parent->left != nullptr && parent->left != current)
            parent = parent->left;
        else
            parent = parent->right;
    }

    return parent;
}

void Heap::heapifyUp(Node* current) {
    if (current == nullptr || current == root)
        return;

    Node* parent = getParentNode(current);
    while (parent != nullptr && current->value > parent->value) {
        swap(current->value, parent->value);
        current = parent;
        parent = getParentNode(current);
    }
}

void Heap::heapifyDown(Node* current) {
    if (current == nullptr)
        return;

    Node* maxNode = current;
    if (current->left != nullptr && current->left->value > maxNode->value)
        maxNode = current->left;

    if (current->right != nullptr && current->right->value > maxNode->value)
        maxNode = current->right;

    if (maxNode != current) {
        swap(current->value, maxNode->value);
        heapifyDown(maxNode);
    }
}
void Heap::inorderTraversal(Node* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        cout << node->value << " ";
        inorderTraversal(node->right);
    }
}

void Heap::preorderTraversal(Node* node) {
    if (node != nullptr) {
        cout << node->value << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

void Heap::postorderTraversal(Node* node) {

    if (node != nullptr) {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->value << " ";
    }
}

void Heap::insert(int value) {

    Node* newNode = new Node(value);

    if (root == nullptr) {
        root = newNode;
    }
    else {
        Node* temp = root;
        while (temp->left != nullptr && temp->right != nullptr) {
            // Dodawanie węzłów na koniec kopca
            if (temp->left != nullptr && temp->right != nullptr)
                temp = temp->left;
            else
                temp = temp->right;
        }

        if (temp->left == nullptr)
            temp->left = newNode;
        else
            temp->right = newNode;
    }

    heapifyUp(newNode);
}

void Heap::remove(int value) {
    if (root == nullptr)
        return;

    Node* nodeToRemove = nullptr;
    Node* temp = root;

    // Przeszukiwanie kopca w głąb, aby znaleźć węzeł do usunięcia
    while (temp != nullptr) {
        if (temp->value == value) {
            nodeToRemove = temp;
            break;
        }
        else {
            if (temp->left != nullptr && temp->left->value == value) {
                nodeToRemove = temp->left;
                break;
            }
            else if (temp->right != nullptr && temp->right->value == value) {
                nodeToRemove = temp->right;
                break;
            }

            if (temp->left != nullptr && value < temp->value)
                temp = temp->left;
            else
                temp = temp->right;
        }
    }

    if (nodeToRemove == nullptr)
        return;

    Node* parentNode = getParentNode(nodeToRemove);

    if (parentNode != nullptr) {
        if (parentNode->left == nodeToRemove)
            parentNode->left = nullptr;
        else
            parentNode->right = nullptr;
    }
    else {
        root = nullptr;
    }

    if (nodeToRemove != root) {
        nodeToRemove->left = root->left;
        nodeToRemove->right = root->right;
        root->left = nullptr;
        root->right = nullptr;
    }

    delete root;
    root = nodeToRemove;
    heapifyDown(root);
}





Heap::Node* Heap::findMin(Node* node) {
    if (node == nullptr)
        return nullptr;

    while (node->left != nullptr)
        node = node->left;

    return node;
}



void Heap::inorder() {
    inorderTraversal(root);
    cout << endl;
}

void Heap::preorder() {
    preorderTraversal(root);
    cout << endl;
}

void Heap::postorder() {
    postorderTraversal(root);
    cout << endl;
}
