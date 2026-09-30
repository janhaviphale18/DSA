#include <iostream>
#include <queue>
#include <stack>
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

void reverseLevelOrder(Node *root)
{
    if (root == NULL)
        return;

    queue<Node*> q;
    stack<Node*> s;

    q.push(root);

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        s.push(current);

        if (current->right != NULL)
            q.push(current->right);

        if (current->left != NULL)
            q.push(current->left);
    }

    while (!s.empty())
    {
        cout << s.top()->data << " ";
        s.pop();
    }
}

int main()
{
    Node *root = create();

    cout << "Reverse Level Order: ";
    reverseLevelOrder(root);

    return 0;
}