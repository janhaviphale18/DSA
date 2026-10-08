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

Node* predecessor(Node* root, int key)
{
    Node* current = findNode(root, key);

    if(current == NULL)
        return NULL;

    // If left subtree exists, predecessor is its maximum node
    if(current->left != NULL)
    {
        Node* temp = current->left;

        while(temp->right != NULL)
            temp = temp->right;

        return temp;
    }

    // Otherwise, find the lowest ancestor smaller than the key
    Node* predecessor = NULL;
    Node* ancestor = root;

    while(ancestor != NULL)
    {
        if(key > ancestor->data)
        {
            predecessor = ancestor;
            ancestor = ancestor->right;
        }
        else
        {
            ancestor = ancestor->left;
        }
    }

    return predecessor;
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

    Node* result = predecessor(root, key);

    if(result != NULL)
        cout << "Inorder Predecessor: " << result->data;
    else
        cout << "Inorder Predecessor does not exist";

    return 0;
}