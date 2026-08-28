#include <iostream>
using namespace std;

#define MAX 5

struct Element
{
    int data;
    int priority;
};

Element queueArr[MAX];
int size = 0;

void insert(int value, int priority)
{
    if (size == MAX)
    {
        cout << "Priority Queue Overflow" << endl;
        return;
    }

    queueArr[size].data = value;
    queueArr[size].priority = priority;

    size++;

    cout << value << " inserted with priority "
         << priority << endl;
}

void deleteHighest()
{
    if (size == 0)
    {
        cout << "Priority Queue Underflow" << endl;
        return;
    }

    int highest = 0;

    for (int i = 1; i < size; i++)
    {
        if (queueArr[i].priority > queueArr[highest].priority)
        {
            highest = i;
        }
    }

    cout << queueArr[highest].data
         << " deleted from priority queue" << endl;

    for (int i = highest; i < size - 1; i++)
    {
        queueArr[i] = queueArr[i + 1];
    }

    size--;
}

void display()
{
    if (size == 0)
    {
        cout << "Priority Queue is empty" << endl;
        return;
    }

    cout << "Priority Queue: ";

    for (int i = 0; i < size; i++)
    {
        cout << queueArr[i].data
             << "(" << queueArr[i].priority << ") ";
    }

    cout << endl;
}

int main()
{
    insert(10, 2);
    insert(20, 1);
    insert(30, 3);

    deleteHighest();

    display();

    return 0;
}