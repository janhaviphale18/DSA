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

bool printAncestors(Node* root, int key) {
    if (root == NULL)
        return false;

    if (root->data == key)
        return true;

    if (printAncestors(root->left, key) ||
        printAncestors(root->right, key)) {
        cout << root->data << " ";
        return true;
    }

    return false;
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    int key;
    cout << "Enter node whose ancestors are required: ";
    cin >> key;

    cout << "Ancestors of " << key << ": ";

    if (!printAncestors(root, key))
        cout << "Node not found";

    return 0;
}