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

Node* findNode(Node* root, int key)
{
    if(root == NULL || root->data == key)
        return root;

    if(key < root->data)
        return findNode(root->left, key);

    return findNode(root->right, key);
}

Node* successor(Node* root, int key)
{
    Node* current = findNode(root, key);

    if(current == NULL)
        return NULL;

    // If right subtree exists, successor is its minimum node
    if(current->right != NULL)
    {
        Node* temp = current->right;

        while(temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    // Otherwise, find the lowest ancestor greater than the key
    Node* successor = NULL;
    Node* ancestor = root;

    while(ancestor != NULL)
    {
        if(key < ancestor->data)
        {
            successor = ancestor;
            ancestor = ancestor->left;
        }
        else
        {
            ancestor = ancestor->right;
        }
    }

    return successor;
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    int key;

    cout << "Enter node: ";
    cin >> key;

    Node* result = successor(root, key);

    if(result != NULL)
        cout << "Inorder Successor: " << result->data;
    else
        cout << "Inorder Successor does not exist";

    return 0;
}