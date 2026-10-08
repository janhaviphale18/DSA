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

void printRange(Node* root, int low, int high)
{
    if(root == NULL)
        return;

    // Search left subtree only when values can be smaller
    if(root->data > low)
        printRange(root->left, low, high);

    if(root->data >= low && root->data <= high)
        cout << root->data << " ";

    // Search right subtree only when values can be larger
    if(root->data < high)
        printRange(root->right, low, high);
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    int low, high;

    cout << "Enter range: ";
    cin >> low >> high;

    cout << "Nodes in range: ";
    printRange(root, low, high);

    return 0;
}