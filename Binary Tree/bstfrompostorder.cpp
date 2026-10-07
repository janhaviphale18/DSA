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

Node* buildTree(int postorder[], int& index, int minimum, int maximum)
{
    if(index < 0)
        return NULL;

    if(postorder[index] <= minimum || postorder[index] >= maximum)
        return NULL;

    Node* root = new Node(postorder[index]);
    index--;

    root->right = buildTree(postorder, index, root->data, maximum);
    root->left = buildTree(postorder, index, minimum, root->data);

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
    int postorder[] = {3, 6, 5, 11, 10, 8};
    int n = 6;
    int index = n - 1;

    Node* root = buildTree(postorder, index, -1000000, 1000000);

    cout << "Inorder Traversal: ";
    inorder(root);

    return 0;
}