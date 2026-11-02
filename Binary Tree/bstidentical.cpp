#include <iostream>
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

bool isIdentical(Node* root1, Node* root2)
{
    if(root1 == NULL && root2 == NULL)
        return true;

    if(root1 == NULL || root2 == NULL)
        return false;

    if(root1->data != root2->data)
        return false;

    return isIdentical(root1->left, root2->left) &&
           isIdentical(root1->right, root2->right);
}

int main()
{
    Node* root1 = new Node(8);

    root1->left = new Node(5);
    root1->right = new Node(10);
    root1->left->left = new Node(3);
    root1->left->right = new Node(6);

    Node* root2 = new Node(8);

    root2->left = new Node(5);
    root2->right = new Node(10);
    root2->left->left = new Node(3);
    root2->left->right = new Node(6);

    if(isIdentical(root1, root2))
        cout << "The trees are identical";
    else
        cout << "The trees are not identical";

    return 0;
}