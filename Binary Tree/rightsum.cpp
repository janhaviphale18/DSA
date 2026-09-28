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

int rightLeafSum(Node *root)
{
    if (root == NULL)
        return 0;

    int sum = 0;

    if (root->right != NULL &&
        root->right->left == NULL &&
        root->right->right == NULL)
    {
        sum += root->right->data;
    }

    sum += rightLeafSum(root->left);
    sum += rightLeafSum(root->right);

    return sum;
}

int main()
{
    Node *root = create();

    cout << "Sum of Right Leaves: " << rightLeafSum(root);

    return 0;
}