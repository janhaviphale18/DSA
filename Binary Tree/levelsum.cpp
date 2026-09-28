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

void levelSum(Node *root)
{
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    int level = 0;

    while (!q.empty())
    {
        int size = q.size();
        int sum = 0;

        for (int i = 0; i < size; i++)
        {
            Node *current = q.front();
            q.pop();

            sum += current->data;

            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);
        }

        cout << "Level " << level << " Sum: " << sum << endl;
        level++;
    }
}

int main()
{
    Node *root = create();

    levelSum(root);

    return 0;
}