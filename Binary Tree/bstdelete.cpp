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

Node* findMin(Node* root)
{
    while(root->left != NULL)
        root = root->left;

    return root;
}

Node* deleteNode(Node* root, int key)
{
    if(root == NULL)
        return NULL;

    if(key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if(key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // Case 1: No child
        if(root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }

        // Case 2: Only right child
        if(root->left == NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // Case 3: Only left child
        if(root->right == NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 4: Two children
        Node* temp = findMin(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }

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
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    int key;

    cout << "Before deletion: ";
    inorder(root);

    cout << "\nEnter element to delete: ";
    cin >> key;

    root = deleteNode(root, key);

    cout << "After deletion: ";
    inorder(root);

    return 0;
}