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

bool findSibling(Node* root, int key) {
    if (root == NULL)
        return false;

    if (root->left != NULL && root->right != NULL) {
        if (root->left->data == key) {
            cout << "Sibling of " << key << ": "
                 << root->right->data;
            return true;
        }

        if (root->right->data == key) {
            cout << "Sibling of " << key << ": "
                 << root->left->data;
            return true;
        }
    }

    if (findSibling(root->left, key))
        return true;

    return findSibling(root->right, key);
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    int key;
    cout << "Enter node: ";
    cin >> key;

    if (!findSibling(root, key))
        cout << "Sibling not found";

    return 0;
}