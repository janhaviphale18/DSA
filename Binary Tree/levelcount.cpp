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

int countLevel(Node *root, int target)
{
    if (root == NULL)
        return 0;

    queue<Node*> q;
    q.push(root);

    int level = 0;

    while (!q.empty())
    {
        int size = q.size();

        if (level == target)
            return size;

        for (int i = 0; i < size; i++)
        {
            Node *current = q.front();
            q.pop();

            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);
        }

        level++;
    }

    return 0;
}

int main()
{
    Node *root = create();

    int level;
    cin >> level;

    cout << "Number of Nodes at Level " << level << ": "
         << countLevel(root, level);

    return 0;
}