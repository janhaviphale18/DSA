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

void printPath(int path[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << path[i];

        if (i != length - 1)
            cout << " -> ";
    }

    cout << endl;
}

void rootToLeaf(Node *root, int path[], int length)
{
    if (root == NULL)
        return;

    path[length] = root->data;
    length++;

    if (root->left == NULL && root->right == NULL)
    {
        printPath(path, length);
        return;
    }

    rootToLeaf(root->left, path, length);
    rootToLeaf(root->right, path, length);
}

int main()
{
    Node *root = create();

    int path[100];

    cout << "Root to Leaf Paths:" << endl;
    rootToLeaf(root, path, 0);

    return 0;
}