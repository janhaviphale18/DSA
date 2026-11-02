#include <iostream>
#include <stack>
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

void postorder(Node* root)
{
    if(root == NULL)
        return;

    stack<Node*> st1, st2;

    st1.push(root);

    while(!st1.empty())
    {
        Node* current = st1.top();
        st1.pop();

        st2.push(current);

        if(current->left != NULL)
            st1.push(current->left);

        if(current->right != NULL)
            st1.push(current->right);
    }

    while(!st2.empty())
    {
        cout << st2.top()->data << " ";
        st2.pop();
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

    cout << "Iterative Postorder Traversal: ";
    postorder(root);

    return 0;
}