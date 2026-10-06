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

void serialize(Node* root, stringstream& ss) {
    if (root == NULL) {
        ss << "-1 ";
        return;
    }

    ss << root->data << " ";

    serialize(root->left, ss);
    serialize(root->right, ss);
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    stringstream ss;

    serialize(root, ss);

    cout << "Serialized tree: ";
    cout << ss.str();

    return 0;
}