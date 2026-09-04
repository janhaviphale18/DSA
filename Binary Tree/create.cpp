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

    cout << "Enter left child of " << x << ": ";
    temp -> lc = create();

    cout << "Enter right child of " << x << ": ";
    temp -> rc = create();

    return temp;
}

int main()
{
    node *root;

    cout << "Enter root node: ";
    root = create();

    return 0;
}