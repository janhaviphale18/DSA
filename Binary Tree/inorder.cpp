#include <iostream>
using namespace std;

struct node
{
    int data;
    node *lc;
    node *rc;
};

node *create()
{
    int x;

    cin >> x;

    if(x == -1)
    {
        return NULL;
    }

    node *temp = new node;

    temp -> data = x;
    temp -> lc = NULL;
    temp -> rc = NULL;

    temp -> lc = create();
    temp -> rc = create();

    return temp;
}

void inorder(node *n)
{
    if(n != NULL)
    {
        inorder(n -> lc);
        cout << n -> data << " ";
        inorder(n -> rc);
    }
}

int main()
{
    node *root;

    cout << "Enter tree: ";
    root = create();

    cout << "Inorder Traversal: ";
    inorder(root);

    return 0;
}