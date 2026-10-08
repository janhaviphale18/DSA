#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

int checkHeight(Node* root)
{
    if(root == NULL)
        return 0;

    int leftHeight = checkHeight(root->left);

    if(leftHeight == -1)
        return -1;

    int rightHeight = checkHeight(root->right);

    if(rightHeight == -1)
        return -1;

    if(abs(leftHeight - rightHeight) > 1)
        return -1;

    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(Node* root)
{
    return checkHeight(root) != -1;
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    if(isBalanced(root))
        cout << "The BST is balanced";
    else
        cout << "The BST is not balanced";

    return 0;
}