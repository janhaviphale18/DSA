#include <iostream>
using namespace std;

#define MAX 5

int queueArr[MAX];
int rear = -1;

void enqueue(int value)
{
    if (rear == MAX - 1)
    {
        cout << "Queue Overflow" << endl;
        return;
    }

    rear++;
    queueArr[rear] = value;

    cout << value << " inserted into queue" << endl;
}

void display()
{
    if (rear == -1)
    {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << "Queue: ";

    for (int i = 0; i <= rear; i++)
    {
        cout << queueArr[i] << " ";
    }

    cout << endl;
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);

    display();

    return 0;
}