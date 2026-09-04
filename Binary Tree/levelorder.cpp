#include <iostream>
using namespace std;

struct node
{
    int data;
    node *lc;
    node *rc;
};

struct queue
{
    node *data[100];
    int front;
    int rear;
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

void enqueue(queue *q, node *n)
{
    if(q -> rear < 100)
    {
        q -> rear++;
        q -> data[q -> rear] = n;
    }
}

node *dequeue(queue *q)
{
    if(q -> front <= q -> rear)
    {
        node *temp = q -> data[q -> front];
        q -> front++;

        return temp;
    }

    return NULL;
}

void levelorder(node *root)
{
    if(root == NULL)
    {
        return;
    }

    queue q;

    q.front = 0;
    q.rear = -1;

    enqueue(&q, root);

    while(q.front <= q.rear)
    {
        node *temp = dequeue(&q);

        cout << temp -> data << " ";

        if(temp -> lc != NULL)
        {
            enqueue(&q, temp -> lc);
        }

        if(temp -> rc != NULL)
        {
            enqueue(&q, temp -> rc);
        }
    }
}

int main()
{
    node *root;

    cout << "Enter tree: ";
    root = create();

    cout << "Level Order Traversal: ";
    levelorder(root);

    return 0;
}