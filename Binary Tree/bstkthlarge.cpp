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

void kthLargest(Node* root, int& k, int& result)
{
    if(root == NULL)
        return;

    // Reverse inorder gives descending order
    kthLargest(root->right, k, result);

    if(k == 1)
    {
        result = root->data;
        return;
    }

    k--;

    kthLargest(root->left, k, result);
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    int k;

    cout << "Enter k: ";
    cin >> k;

    int originalK = k;
    int result = -1;

    kthLargest(root, k, result);

    if(result != -1)
        cout << originalK << "th Largest Element: " << result;
    else
        cout << "Invalid k";

    return 0;
}