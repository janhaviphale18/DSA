#include <iostream>
#include <cstdlib>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node* create()
{
    int x;
    cin >> x;

    if (x == -1)
        return NULL;

    Node *newNode = new Node;
    newNode->data = x;

    newNode->left = create();
    newNode->right = create();

    return newNode;
}

int height(Node *root)
{
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(Node *root)
{
    if (root == NULL)
        return true;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (abs(leftHeight - rightHeight) > 1)
        return false;

    return isBalanced(root->left) &&
           isBalanced(root->right);
}

int main()
{
    Node *root = create();

    if (isBalanced(root))
        cout << "Binary Tree is Balanced";
    else
        cout << "Binary Tree is Not Balanced";

    return 0;
}