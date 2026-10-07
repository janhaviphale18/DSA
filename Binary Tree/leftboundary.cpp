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

bool isLeaf(Node* root)
{
    return root != NULL &&
           root->left == NULL &&
           root->right == NULL;
}

void printLeftBoundary(Node* root)
{
    if(root == NULL || isLeaf(root))
        return;

    Node* current = root;

    while(current != NULL)
    {
        if(!isLeaf(current))
            cout << current->data << " ";

        if(current->left != NULL)
            current = current->left;
        else
            current = current->right;
    }
}

int main()
{
    Node* root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);

    root->right->right = new Node(6);

    cout << "Left Boundary: ";

    printLeftBoundary(root);

    return 0;
}