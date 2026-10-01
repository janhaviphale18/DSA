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

bool childrenSum(Node* root) {
    if (root == NULL)
        return true;

    // Leaf node
    if (root->left == NULL && root->right == NULL)
        return true;

    int leftValue = 0;
    int rightValue = 0;

    if (root->left != NULL)
        leftValue = root->left->data;

    if (root->right != NULL)
        rightValue = root->right->data;

    if (root->data != leftValue + rightValue)
        return false;

    return childrenSum(root->left) &&
           childrenSum(root->right);
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    if (childrenSum(root))
        cout << "Tree satisfies Children Sum Property";
    else
        cout << "Tree does not satisfy Children Sum Property";

    return 0;
}