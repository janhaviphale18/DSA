#include <iostream>
using namespace std;

struct node
{
    int data;
    node *lc;
    node *rc;
};

int main()
{
    node *root = new node;

    root -> data = 10;
    root -> lc = NULL;
    root -> rc = NULL;

    cout << "Data = " << root -> data << endl;

    if(root -> lc == NULL)
    {
        cout << "Left Child = NULL" << endl;
    }

    if(root -> rc == NULL)
    {
        cout << "Right Child = NULL" << endl;
    }

    return 0;
}