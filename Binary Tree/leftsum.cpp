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

int leftLeafSum(Node *root)
{
    if (root == NULL)
        return 0;

    int sum = 0;

    if (root->left != NULL &&
        root->left->left == NULL &&
        root->left->right == NULL)
    {
        sum += root->left->data;
    }

    sum += leftLeafSum(root->left);
    sum += leftLeafSum(root->right);

    return sum;
}

int main()
{
    Node *root = create();

    cout << "Sum of Left Leaves: " << leftLeafSum(root);

    return 0;
}