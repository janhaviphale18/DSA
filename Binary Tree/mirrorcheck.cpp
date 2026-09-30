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

bool isMirror(Node *root1, Node *root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 == NULL || root2 == NULL)
        return false;

    return (root1->data == root2->data &&
            isMirror(root1->left, root2->right) &&
            isMirror(root1->right, root2->left));
}

int main()
{
    Node *root1 = create();
    Node *root2 = create();

    if (isMirror(root1, root2))
        cout << "Trees are Mirror Images";
    else
        cout << "Trees are Not Mirror Images";

    return 0;
}