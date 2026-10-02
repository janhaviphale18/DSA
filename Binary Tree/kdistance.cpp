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

void printKDistance(Node* root, int k) {
    if (root == NULL)
        return;

    if (k == 0) {
        cout << root->data << " ";
        return;
    }

    printKDistance(root->left, k - 1);
    printKDistance(root->right, k - 1);
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    int k;
    cout << "Enter distance: ";
    cin >> k;

    cout << "Nodes at distance " << k << " from root: ";

    printKDistance(root, k);

    return 0;
}