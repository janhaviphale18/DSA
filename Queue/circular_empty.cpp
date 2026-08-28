#include <iostream>
using namespace std;

#define MAX 5

int queueArr[MAX];
int front = -1;
int rear = -1;

bool isEmpty()
{
    return front == -1;
}

void enqueue(int value)
{
    if ((rear + 1) % MAX == front)
    {
        cout << "Queue Overflow" << endl;
        return;
    }

    if (isEmpty())
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }

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