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

Node* lca(Node *root, int n1, int n2)
{
    if (root == NULL)
        return NULL;

    if (root->data == n1 || root->data == n2)
        return root;

    Node *left = lca(root->left, n1, n2);
    Node *right = lca(root->right, n1, n2);

    if (left != NULL && right != NULL)
        return root;

    if (left != NULL)
        return left;

    return right;
}

int findDistance(Node *root, int key, int distance)
{
    if (root == NULL)
        return -1;

    if (root->data == key)
        return distance;

    int left = findDistance(root->left, key, distance + 1);

    if (left != -1)
        return left;

    return findDistance(root->right, key, distance + 1);
}

int distanceBetween(Node *root, int n1, int n2)
{
    Node *ancestor = lca(root, n1, n2);

    if (ancestor == NULL)
        return -1;

    int d1 = findDistance(ancestor, n1, 0);
    int d2 = findDistance(ancestor, n2, 0);

    if (d1 == -1 || d2 == -1)
        return -1;

    return d1 + d2;
}

int main()
{
    Node *root = create();

    int n1, n2;
    cin >> n1 >> n2;

    int distance = distanceBetween(root, n1, n2);

    if (distance != -1)
        cout << "Distance between " << n1 << " and " << n2
             << ": " << distance;
    else
        cout << "Node not found";

    return 0;
}