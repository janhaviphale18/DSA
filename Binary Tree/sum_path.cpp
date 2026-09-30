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

void sumPath(Node *root, int sum, int path[], int length)
{
    if (root == NULL)
        return;

    sum += root->data;
    path[length] = root->data;
    length++;

    if (root->left == NULL && root->right == NULL)
    {
        cout << "Path: ";

        for (int i = 0; i < length; i++)
        {
            cout << path[i];

            if (i != length - 1)
                cout << " -> ";
        }

        cout << " | Sum: " << sum << endl;
        return;
    }

    sumPath(root->left, sum, path, length);
    sumPath(root->right, sum, path, length);
}

int main()
{
    Node *root = create();

    int path[100];

    cout << "Root to Leaf Path Sums:" << endl;
    sumPath(root, 0, path, 0);

    return 0;
}