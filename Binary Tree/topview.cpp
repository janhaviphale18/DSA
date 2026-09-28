#include <iostream>
#include <queue>
#include <map>
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

void topView(Node *root)
{
    if (root == NULL)
        return;

    map<int, int> mp;
    queue<pair<Node*, int>> q;

    q.push({root, 0});

    while (!q.empty())
    {
        Node *current = q.front().first;
        int hd = q.front().second;
        q.pop();

        if (mp.find(hd) == mp.end())
            mp[hd] = current->data;

        if (current->left != NULL)
            q.push({current->left, hd - 1});

        if (current->right != NULL)
            q.push({current->right, hd + 1});
    }

    for (auto column : mp)
        cout << column.second << " ";
}

int main()
{
    Node *root = create();

    cout << "Top View: ";
    topView(root);

    return 0;
}