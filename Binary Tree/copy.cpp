#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node* create()
{
    int x;
    cin >> x;

    if (x == -1)
        return NULL;

    Node *newNode = new Node;
    newNode->data = x;

    newNode->left = create();
    newNode->right = create();

    return newNode;
}

Node* copyTree(Node *root)
{
    if (root == NULL)
        return NULL;

    Node *newNode = new Node;
    newNode->data = root->data;

    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    return newNode;
}

void inorder(Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main()
{
    Node *root = create();

    Node *copy = copyTree(root);

    cout << "Inorder of Original Tree: ";
    inorder(root);

    cout << endl;

    cout << "Inorder of Copied Tree: ";
    inorder(copy);

    return 0;
}