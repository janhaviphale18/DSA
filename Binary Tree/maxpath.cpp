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

int maxPathSum(Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return root->data;

    int leftSum = maxPathSum(root->left);
    int rightSum = maxPathSum(root->right);

    if (root->left == NULL)
        return root->data + rightSum;

    if (root->right == NULL)
        return root->data + leftSum;

    return root->data + max(leftSum, rightSum);
}

int main()
{
    Node *root = create();

    cout << "Maximum Root to Leaf Path Sum: "
         << maxPathSum(root);

    return 0;
}