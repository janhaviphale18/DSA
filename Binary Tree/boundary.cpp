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

void leftBoundary(Node *root)
{
    Node *current = root->left;

    while (current != NULL)
    {
        if (current->left != NULL || current->right != NULL)
            cout << current->data << " ";

        if (current->left != NULL)
            current = current->left;
        else
            current = current->right;
    }
}

void leaves(Node *root)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        cout << root->data << " ";
        return;
    }

    leaves(root->left);
    leaves(root->right);
}

void rightBoundary(Node *root)
{
    Node *current = root->right;

    int values[100];
    int count = 0;

    while (current != NULL)
    {
        if (current->left != NULL || current->right != NULL)
            values[count++] = current->data;

        if (current->right != NULL)
            current = current->right;
        else
            current = current->left;
    }

    for (int i = count - 1; i >= 0; i--)
        cout << values[i] << " ";
}

void boundary(Node *root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";

    leftBoundary(root);
    leaves(root);
    rightBoundary(root);
}

int main()
{
    Node *root = create();

    cout << "Boundary Traversal: ";
    boundary(root);

    return 0;
}