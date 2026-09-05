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

int minimum(node *n)
{
    if(n == NULL)
    {
        return 999999;
    }

    int min = n -> data;

    int left = minimum(n -> lc);
    int right = minimum(n -> rc);

    if(left < min)
    {
        min = left;
    }

    if(right < min)
    {
        min = right;
    }

    return min;
}

int main()
{
    node *root;
    int min;

    cout << "Enter tree: ";
    root = create();

    min = minimum(root);

    cout << "Minimum element: " << min << endl;

    return 0;
}