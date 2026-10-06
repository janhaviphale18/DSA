#include <iostream>
#include <sstream>
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

Node* deserialize(stringstream& ss) {
    int value;

    if (!(ss >> value))
        return NULL;

    if (value == -1)
        return NULL;

    Node* root = new Node(value);

    root->left = deserialize(ss);
    root->right = deserialize(ss);

    return root;
}

void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    string input;

    cout << "Enter serialized tree: ";
    getline(cin, input);

    stringstream ss(input);

    Node* root = deserialize(ss);

    cout << "Inorder traversal after deserialization: ";
    inorder(root);

    return 0;
}