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

int internal(node *n)
{
    if(n == NULL)
    {
        return 0;
    }

    if(n -> lc == NULL && n -> rc == NULL)
    {
        return 0;
    }

    return 1 + internal(n -> lc) + internal(n -> rc);
}

int main()
{
    node *root;
    int total;

    cout << "Enter tree: ";
    root = create();

    total = internal(root);

    cout << "Total number of internal nodes: " << total << endl;

    return 0;
}