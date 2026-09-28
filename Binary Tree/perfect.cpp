#include <iostream>
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

int depth(Node *root)
{
    int d = 0;

    while (root != NULL)
    {
        d++;
        root = root->left;
    }

    return d;
}

bool isPerfect(Node *root, int depth, int level)
{
    if (root == NULL)
        return true;

    if (root->left == NULL && root->right == NULL)
        return depth == level + 1;

    if (root->left == NULL || root->right == NULL)
        return false;

    return isPerfect(root->left, depth, level + 1) &&
           isPerfect(root->right, depth, level + 1);
}

int main()
{
    Node *root = create();

    int d = depth(root);

    if (isPerfect(root, d, 0))
        cout << "Binary Tree is Perfect";
    else
        cout << "Binary Tree is Not Perfect";

    return 0;
}