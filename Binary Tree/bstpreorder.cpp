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

void preorder(Node* root)
{
    if(root == NULL)
        return;

    stack<Node*> st;
    st.push(root);

    while(!st.empty())
    {
        Node* current = st.top();
        st.pop();

        cout << current->data << " ";

        if(current->right != NULL)
            st.push(current->right);

        if(current->left != NULL)
            st.push(current->left);
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

    cout << "Iterative Preorder Traversal: ";
    preorder(root);

    return 0;
}