#include <iostream>
using namespace std;

#define MAX 5

int queueArr[MAX];
int front = -1;
int rear = -1;

bool isEmpty()
{
    if (front == -1 || front > rear)
    {
        return true;
    }

    return false;
}

void enqueue(int value)
{
    if (rear == MAX - 1)
    {
        cout << "Queue Overflow" << endl;
        return;
    }

    if (front == -1)
    {
        front = 0;
    }

    rear++;
    queueArr[rear] = value;

    cout << value << " inserted into queue" << endl;
}

void checkEmpty()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
    }
    else
    {
        cout << "Queue is not empty" << endl;
    }
}

int main()
{
    checkEmpty();

    enqueue(10);

    checkEmpty();

    return 0;
}