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

    temp->data = x;
    temp->lc = NULL;
    temp->rc = NULL;

    temp->lc = create();
    temp->rc = create();

    return temp;
}

int onechild(node *n)
{
    if(n == NULL)
    {
        return 0;
    }

    if((n->lc != NULL && n->rc == NULL) ||
       (n->lc == NULL && n->rc != NULL))
    {
        return 1 + onechild(n->lc) + onechild(n->rc);
    }

    return onechild(n->lc) + onechild(n->rc);
}

int main()
{
    node *root;
    int total;

    cout << "Enter tree: ";
    root = create();

    total = onechild(root);

    cout << "Nodes with one child: " << total << endl;

    return 0;
}