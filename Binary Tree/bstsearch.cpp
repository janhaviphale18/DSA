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

bool search(Node* root, int key)
{
    if(root == NULL)
        return false;

    if(root->data == key)
        return true;

    if(key < root->data)
        return search(root->left, key);

    return search(root->right, key);
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

    cout << "Enter element to search: ";
    cin >> key;

    if(search(root, key))
        cout << "Element found";
    else
        cout << "Element not found";

    return 0;
}