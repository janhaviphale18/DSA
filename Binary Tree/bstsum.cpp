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

int sumNodes(Node* root)
{
    if(root == NULL)
        return 0;

    return root->data +
           sumNodes(root->left) +
           sumNodes(root->right);
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    cout << "Sum of Nodes: " << sumNodes(root);

    return 0;
}