#include <iostream>
#include <unordered_set>
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

bool findPair(Node* root, int target, unordered_set<int>& values)
{
    if(root == NULL)
        return false;

    int complement = target - root->data;

    if(values.find(complement) != values.end())
        return true;

    values.insert(root->data);

    return findPair(root->left, target, values) ||
           findPair(root->right, target, values);
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    int target;

    cout << "Enter target sum: ";
    cin >> target;

    unordered_set<int> values;

    if(findPair(root, target, values))
        cout << "Pair exists";
    else
        cout << "Pair does not exist";

    return 0;
}