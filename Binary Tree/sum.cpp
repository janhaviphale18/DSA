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

int sum(node *n)
{
    if(n == NULL)
    {
        return 0;
    }

    return n -> data + sum(n -> lc) + sum(n -> rc);
}

int main()
{
    node *root;
    int total;

    cout << "Enter tree: ";
    root = create();

    total = sum(root);

    cout << "Sum of all nodes: " << total << endl;

    return 0;
}