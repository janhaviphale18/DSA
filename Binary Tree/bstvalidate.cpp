#include <iostream>
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

bool isBST(Node* root, long long minimum, long long maximum)
{
    if(root == NULL)
        return true;

    if(root->data <= minimum || root->data >= maximum)
        return false;

    return isBST(root->left, minimum, root->data) &&
           isBST(root->right, root->data, maximum);
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    if(isBST(root, -1000000000LL, 1000000000LL))
        cout << "The tree is a valid BST";
    else
        cout << "The tree is not a valid BST";

    return 0;
}