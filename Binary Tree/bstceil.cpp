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

Node* findCeil(Node* root, int key)
{
    Node* ceilNode = NULL;

    while(root != NULL)
    {
        if(root->data == key)
            return root;

        if(root->data > key)
        {
            ceilNode = root;
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return ceilNode;
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

    cout << "Enter key: ";
    cin >> key;

    Node* result = findCeil(root, key);

    if(result != NULL)
        cout << "Ceiling: " << result->data;
    else
        cout << "Ceiling does not exist";

    return 0;
}