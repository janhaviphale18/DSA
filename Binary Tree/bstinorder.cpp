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

void morrisInorder(Node* root)
{
    Node* current = root;

    while(current != NULL)
    {
        if(current->left == NULL)
        {
            cout << current->data << " ";
            current = current->right;
        }
        else
        {
            Node* predecessor = current->left;

            while(predecessor->right != NULL &&
                  predecessor->right != current)
            {
                predecessor = predecessor->right;
            }

            if(predecessor->right == NULL)
            {
                predecessor->right = current;
                current = current->left;
            }
            else
            {
                predecessor->right = NULL;
                cout << current->data << " ";
                current = current->right;
            }
        }
    }
}

int main()
{
    Node* root = new Node(8);

    root->left = new Node(5);
    root->right = new Node(10);

    root->left->left = new Node(3);
    root->left->right = new Node(6);

    root->right->right = new Node(11);

    cout << "Morris Inorder Traversal: ";
    morrisInorder(root);

    return 0;
}