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

void preorder(node *n)
{
    if(n != NULL)
    {
        cout << n -> data << " ";
        preorder(n -> lc);
        preorder(n -> rc);
    }
}

int main()
{
    node *root;

    cout << "Enter tree: ";
    root = create();

    cout << "Preorder Traversal: ";
    preorder(root);

    return 0;
}