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

int findLevel(Node *root, int key, int level)
{
    if (root == NULL)
        return -1;

    if (root->data == key)
        return level;

    int leftLevel = findLevel(root->left, key, level + 1);

    if (leftLevel != -1)
        return leftLevel;

    return findLevel(root->right, key, level + 1);
}

int main()
{
    Node *root = create();

    int key;
    cin >> key;

    int level = findLevel(root, key, 0);

    if (level != -1)
        cout << "Level of " << key << ": " << level;
    else
        cout << "Node not found";

    return 0;
}