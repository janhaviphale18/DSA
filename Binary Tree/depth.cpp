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

int depth(node *n, int x, int d)
{
    if(n == NULL)
    {
        return -1;
    }

    if(n -> data == x)
    {
        return d;
    }

    int left = depth(n -> lc, x, d + 1);

    if(left != -1)
    {
        return left;
    }

    return depth(n -> rc, x, d + 1);
}

int main()
{
    node *root;
    int x, d;

    cout << "Enter tree: ";
    root = create();

    cout << "Enter node to find depth: ";
    cin >> x;

    d = depth(root, x, 0);

    if(d == -1)
    {
        cout << "Node not found" << endl;
    }
    else
    {
        cout << "Depth of node: " << d << endl;
    }

    return 0;
}