#include<iostream>
using namespace std;

#define MAX 100

int queue1[MAX];
int queue2[MAX];

int front1 = 0;
int rear1 = -1;

int front2 = 0;
int rear2 = -1;

void push(int value)
{
    if(rear1 - front1 + 1 == MAX)
    {
        cout << "Stack Overflow" << endl;
        return;
    }

    while(front1 <= rear1)
    {
        rear2++;
        queue2[rear2] = queue1[front1];
        front1++;
    }

    rear1++;
    queue1[rear1] = value;

    while(front2 <= rear2)
    {
        rear1++;
        queue1[rear1] = queue2[front2];
        front2++;
    }

    front1 = 0;
    rear2 = -1;
    front2 = 0;

    cout << value << " pushed into stack" << endl;
}

void pop()
{
    if(front1 > rear1)
    {
        cout << "Stack Underflow" << endl;
        return;
    }

    cout << queue1[front1] << " popped from stack" << endl;

    front1++;

    if(front1 > rear1)
    {
        front1 = 0;
        rear1 = -1;
    }
}

void peek()
{
    if(front1 > rear1)
    {
        cout << "Stack is Empty" << endl;
        return;
    }

    cout << "Top element: " << queue1[front1] << endl;
}

void display()
{
    if(front1 > rear1)
    {
        cout << "Stack is Empty" << endl;
        return;
    }

    cout << "Stack: ";

    for(int i = front1; i <= rear1; i++)
    {
        cout << queue1[i] << " ";
    }

    cout << endl;
}

int main()
{
    push(10);
    push(20);
    push(30);

    display();

    peek();

    pop();

    display();

    peek();

    return 0;
}