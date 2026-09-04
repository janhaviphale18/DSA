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

int count(node *n)
{
    if(n == NULL)
    {
        return 0;
    }

    return 1 + count(n -> lc) + count(n -> rc);
}

int main()
{
    node *root;
    int total;

    cout << "Enter tree: ";
    root = create();

    total = count(root);

    cout << "Total number of nodes: " << total << endl;

    return 0;
}