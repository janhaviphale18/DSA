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

bool isFull()
{
    return (rear + 1) % MAX == front;
}

void enqueue(int value)
{
    if (isFull())
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

void checkFull()
{
    if (isFull())
    {
        cout << "Queue is full" << endl;
    }
    else
    {
        cout << "Queue is not full" << endl;
    }
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    checkFull();

    return 0;
}