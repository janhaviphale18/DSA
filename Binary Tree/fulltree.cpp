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

bool isFull(Node *root)
{
    if (root == NULL)
        return true;

    if (root->left == NULL && root->right == NULL)
        return true;

    if (root->left != NULL && root->right != NULL)
        return isFull(root->left) && isFull(root->right);

    return false;
}

int main()
{
    Node *root = create();

    if (isFull(root))
        cout << "Binary Tree is Full";
    else
        cout << "Binary Tree is Not Full";

    return 0;
}