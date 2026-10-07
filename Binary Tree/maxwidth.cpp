#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

int maxWidth(Node* root)
{
    if(root == NULL)
        return 0;

    queue<pair<Node*, unsigned long long>> q;
    q.push({root, 0});

    int maximum = 0;

    while(!q.empty())
    {
        int size = q.size();

        unsigned long long first = q.front().second;
        unsigned long long last = q.back().second;

        maximum = max(maximum, (int)(last - first + 1));

        for(int i = 0; i < size; i++)
        {
            Node* current = q.front().first;
            unsigned long long index = q.front().second;
            q.pop();

            if(current->left != NULL)
                q.push({current->left, 2 * index + 1});

            if(current->right != NULL)
                q.push({current->right, 2 * index + 2});
        }
    }

    return maximum;
}

int main()
{
    Node* root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->right->right = new Node(5);

    root->right->right->right = new Node(6);

    cout << "Maximum Width: " << maxWidth(root);

    return 0;
}