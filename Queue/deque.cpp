#include <iostream>
using namespace std;

#define MAX 5

int dequeArr[MAX];
int front = -1;
int rear = -1;

bool isEmpty()
{
    return front == -1;
}

bool isFull()
{
    return (front == 0 && rear == MAX - 1);
}

void insertRear(int value)
{
    if (isFull())
    {
        cout << "Deque Overflow" << endl;
        return;
    }

    if (isEmpty())
    {
        front = rear = 0;
    }
    else
    {
        rear++;
    }

    dequeArr[rear] = value;

    cout << value << " inserted at rear" << endl;
}

void insertFront(int value)
{
    if (isFull())
    {
        cout << "Deque Overflow" << endl;
        return;
    }

    if (isEmpty())
    {
        front = rear = 0;
    }
    else if (front > 0)
    {
        front--;
    }
    else
    {
        cout << "No space at front" << endl;
        return;
    }

    dequeArr[front] = value;

    cout << value << " inserted at front" << endl;
}

void deleteFront()
{
    if (isEmpty())
    {
        cout << "Deque Underflow" << endl;
        return;
    }

    cout << dequeArr[front] << " deleted from front" << endl;

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front++;
    }
}

void deleteRear()
{
    if (isEmpty())
    {
        cout << "Deque Underflow" << endl;
        return;
    }

    cout << dequeArr[rear] << " deleted from rear" << endl;

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        rear--;
    }
}

void display()
{
    if (isEmpty())
    {
        cout << "Deque is empty" << endl;
        return;
    }

    cout << "Deque: ";

    for (int i = front; i <= rear; i++)
    {
        cout << dequeArr[i] << " ";
    }

    cout << endl;
}

int main()
{
    insertRear(20);
    insertRear(30);
    insertFront(10);

    deleteRear();

    display();

    return 0;
}