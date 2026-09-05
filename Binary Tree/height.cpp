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

int height(node *n)
{
    if(n == NULL)
    {
        return -1;
    }

    int left = height(n -> lc);
    int right = height(n -> rc);

    if(left > right)
    {
        return left + 1;
    }
    else
    {
        return right + 1;
    }
}

int main()
{
    node *root;
    int h;

    cout << "Enter tree: ";
    root = create();

    h = height(root);

    cout << "Height of binary tree: " << h << endl;

    return 0;
}