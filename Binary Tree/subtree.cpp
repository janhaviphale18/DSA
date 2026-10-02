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

bool identical(Node* root1, Node* root2) {
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 == NULL || root2 == NULL)
        return false;

    return root1->data == root2->data &&
           identical(root1->left, root2->left) &&
           identical(root1->right, root2->right);
}

bool isSubtree(Node* root, Node* subRoot) {
    if (subRoot == NULL)
        return true;

    if (root == NULL)
        return false;

    if (identical(root, subRoot))
        return true;

    return isSubtree(root->left, subRoot) ||
           isSubtree(root->right, subRoot);
}

int main() {
    cout << "Enter main tree elements (-1 for NULL): ";

    Node* root = create();

    cout << "Enter subtree elements (-1 for NULL): ";

    Node* subRoot = create();

    if (isSubtree(root, subRoot))
        cout << "Subtree exists";
    else
        cout << "Subtree does not exist";

    return 0;
}