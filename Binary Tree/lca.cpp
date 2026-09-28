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

    Node *leftLCA = lca(root->left, n1, n2);
    Node *rightLCA = lca(root->right, n1, n2);

    if (leftLCA != NULL && rightLCA != NULL)
        return root;

    if (leftLCA != NULL)
        return leftLCA;

    return rightLCA;
}

int main()
{
    Node *root = create();

    int n1, n2;
    cin >> n1 >> n2;

    Node *result = lca(root, n1, n2);

    if (result != NULL)
        cout << "Lowest Common Ancestor: " << result->data;
    else
        cout << "Lowest Common Ancestor not found";

    return 0;
}