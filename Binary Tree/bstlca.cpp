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

Node* findLCA(Node* root, int n1, int n2)
{
    if(root == NULL)
        return NULL;

    // Both nodes are smaller than root
    if(n1 < root->data && n2 < root->data)
        return findLCA(root->left, n1, n2);

    // Both nodes are greater than root
    if(n1 > root->data && n2 > root->data)
        return findLCA(root->right, n1, n2);

    // Nodes are on different sides or one is root
    return root;
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    int n1, n2;

    cout << "Enter two nodes: ";
    cin >> n1 >> n2;

    Node* result = findLCA(root, n1, n2);

    if(result != NULL)
        cout << "Lowest Common Ancestor: " << result->data;
    else
        cout << "LCA does not exist";

    return 0;
}