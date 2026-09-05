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

int countlevel(node *n, int level)
{
    if(n == NULL)
    {
        return 0;
    }

    if(level == 0)
    {
        return 1;
    }

    return countlevel(n -> lc, level - 1) +
           countlevel(n -> rc, level - 1);
}

int main()
{
    node *root;
    int level, total;

    cout << "Enter tree: ";
    root = create();

    cout << "Enter level: ";
    cin >> level;

    total = countlevel(root, level);

    cout << "Number of nodes at level " << level << ": "
         << total << endl;

    return 0;
}