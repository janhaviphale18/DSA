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

void postorder(node *n)
{
    if(n != NULL)
    {
        postorder(n -> lc);
        postorder(n -> rc);
        cout << n -> data << " ";
    }
}

int main()
{
    node *root;

    cout << "Enter tree: ";
    root = create();

    cout << "Postorder Traversal: ";
    postorder(root);

    return 0;
}