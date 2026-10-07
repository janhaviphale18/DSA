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

int findMin(Node* root)
{
    while(root->left != NULL)
        root = root->left;

    return root->data;
}

int findMax(Node* root)
{
    while(root->right != NULL)
        root = root->right;

    return root->data;
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    cout << "Minimum Element: " << findMin(root) << endl;
    cout << "Maximum Element: " << findMax(root);

    return 0;
}