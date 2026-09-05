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

int maximum(node *n)
{
    if(n == NULL)
    {
        return -1;
    }

    int max = n -> data;

    int left = maximum(n -> lc);
    int right = maximum(n -> rc);

    if(left > max)
    {
        max = left;
    }

    if(right > max)
    {
        max = right;
    }

    return max;
}

int main()
{
    node *root;
    int max;

    cout << "Enter tree: ";
    root = create();

    max = maximum(root);

    cout << "Maximum element: " << max << endl;

    return 0;
}