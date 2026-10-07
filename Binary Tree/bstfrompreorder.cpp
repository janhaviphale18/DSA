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

Node* buildTree(int preorder[], int& index, int n, int minimum, int maximum)
{
    if(index >= n)
        return NULL;

    if(preorder[index] <= minimum || preorder[index] >= maximum)
        return NULL;

    Node* root = new Node(preorder[index]);
    index++;

    root->left = buildTree(preorder, index, n, minimum, root->data);
    root->right = buildTree(preorder, index, n, root->data, maximum);

    return root;
}

void inorder(Node* root)
{
    if(root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main()
{
    int preorder[] = {8, 5, 3, 6, 10, 11};
    int n = 6;
    int index = 0;

    Node* root = buildTree(preorder, index, n, -1000000, 1000000);

    cout << "Inorder Traversal: ";
    inorder(root);

    return 0;
}