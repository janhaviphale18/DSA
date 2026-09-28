#include <iostream>
#include <queue>
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

bool isComplete(Node *root)
{
    if (root == NULL)
        return true;

    queue<Node*> q;
    q.push(root);

    bool nullFound = false;

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        if (current == NULL)
        {
            nullFound = true;
            continue;
        }

        if (nullFound)
            return false;

        q.push(current->left);
        q.push(current->right);
    }

    return true;
}

int main()
{
    Node *root = create();

    if (isComplete(root))
        cout << "Binary Tree is Complete";
    else
        cout << "Binary Tree is Not Complete";

    return 0;
}