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

bool identical(Node *root1, Node *root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 == NULL || root2 == NULL)
        return false;

    return (root1->data == root2->data &&
            identical(root1->left, root2->left) &&
            identical(root1->right, root2->right));
}

int main()
{
    Node *root1 = create();
    Node *root2 = create();

    if (identical(root1, root2))
        cout << "Trees are identical";
    else
        cout << "Trees are not identical";

    return 0;
}