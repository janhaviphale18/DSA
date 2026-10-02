#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

Node* create() {
    int value;
    cin >> value;

    if (value == -1)
        return NULL;

    Node* root = new Node(value);

    root->left = create();
    root->right = create();

    return root;
}

bool findPath(Node* root, int key) {
    if (root == NULL)
        return false;

    cout << root->data;

    if (root->data == key)
        return true;

    if (findPath(root->left, key) ||
        findPath(root->right, key)) {
        return true;
    }

    return false;
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    int key;
    cout << "Enter node: ";
    cin >> key;

    cout << "Root to node path: ";

    if (!findPath(root, key))
        cout << "Node not found";

    return 0;
}