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

void dequeue()
{
    if (isEmpty())
    {
        cout << "Queue Underflow" << endl;
        return;
    }

    cout << queueArr[front] << " deleted from queue" << endl;

    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }
}

void display()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << "Queue: ";

    int i = front;

    while (true)
    {
        cout << queueArr[i] << " ";

        if (i == rear)
        {
            break;
        }

        i = (i + 1) % MAX;
    }

    cout << endl;
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);

    dequeue();

    display();

    return 0;
}