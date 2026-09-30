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

void oneChildNodes(Node *root)
{
    if (root == NULL)
        return;

    if ((root->left != NULL && root->right == NULL) ||
        (root->left == NULL && root->right != NULL))
    {
        cout << root->data << " ";
    }

    oneChildNodes(root->left);
    oneChildNodes(root->right);
}

int main()
{
    Node *root = create();

    cout << "Nodes with One Child: ";
    oneChildNodes(root);

    return 0;
}