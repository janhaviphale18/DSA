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

void zigzag(Node *root)
{
    if (root == NULL)
        return;

    queue<Node*> q;
    bool leftToRight = true;

    q.push(root);

    while (!q.empty())
    {
        int size = q.size();
        stack<int> s;

        for (int i = 0; i < size; i++)
        {
            Node *current = q.front();
            q.pop();

            if (leftToRight)
                cout << current->data << " ";
            else
                s.push(current->data);

            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);
        }

        if (!leftToRight)
        {
            while (!s.empty())
            {
                cout << s.top() << " ";
                s.pop();
            }
        }

        leftToRight = !leftToRight;
    }
}

int main()
{
    Node *root = create();

    cout << "Zigzag Level Order: ";
    zigzag(root);

    return 0;
}