#include <iostream>
#include "Heap.h"
#include <queue>
#include <utility>

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
        queue<Node*> nodeQueue;
        nodeQueue.push(root);

        while (!nodeQueue.empty()) {
            Node* current = nodeQueue.front();
            nodeQueue.pop();

            if (current->left != nullptr && current->right != nullptr) {
                nodeQueue.push(current->left);
                nodeQueue.push(current->right);
            }
            else {
                if (current->left == nullptr) {
                    current->left = newNode;
                }
                else {
                    current->right = newNode;
                }
                break;
            }
        }
    }

    heapifyUp(newNode);
}


void Heap::remove(int value) {
    if (root == nullptr)
        return;

    Node* nodeToRemove = nullptr;
    Node* temp = root;
    Node* parent = nullptr;

    // Przeszukiwanie kopca w głąb, aby znaleźć węzeł do usunięcia
    while (temp != nullptr) {
        if (temp->value == value) {
            nodeToRemove = temp;
            break;
        }
        else {
            parent = temp;
            if (value < temp->value)
                temp = temp->left;
            else
                temp = temp->right;
        }
    }

    if (nodeToRemove == nullptr)
        return;

    if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr) {
        if (parent != nullptr) {
            if (parent->left == nodeToRemove)
                parent->left = nullptr;
            else
                parent->right = nullptr;
        }
        else {
            root = nullptr;
        }

        delete nodeToRemove;
    }
    else if (nodeToRemove->left == nullptr) {
        if (parent != nullptr) {
            if (parent->left == nodeToRemove)
                parent->left = nodeToRemove->right;
            else
                parent->right = nodeToRemove->right;
        }
        else {
            root = nodeToRemove->right;
        }

        delete nodeToRemove;
    }
    else if (nodeToRemove->right == nullptr) {
        if (parent != nullptr) {
            if (parent->left == nodeToRemove)
                parent->left = nodeToRemove->left;
            else
                parent->right = nodeToRemove->left;
        }
        else {
            root = nodeToRemove->left;
        }

        delete nodeToRemove;
    }
    else {
        Node* successor = findMin(nodeToRemove->right);
        int successorValue = successor->value;
        remove(successorValue);
        nodeToRemove->value = successorValue;
    }

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
