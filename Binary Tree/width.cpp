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

int width(Node *root)
{
    if (root == NULL)
        return 0;

    queue<Node*> q;
    q.push(root);

    int maxWidth = 0;

    while (!q.empty())
    {
        int size = q.size();

        if (size > maxWidth)
            maxWidth = size;

        for (int i = 0; i < size; i++)
        {
            Node *current = q.front();
            q.pop();

            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);
        }
    }

    return maxWidth;
}

int main()
{
    Node *root = create();

    cout << "Maximum Width: " << width(root);

    return 0;
}