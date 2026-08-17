#include<iostream>
using namespace std;

#define MAX 5

int stack[MAX];
int top = -1;

bool isEmpty()
{
    return top == -1;
}

bool isFull()
{
    return top == MAX - 1;
}

void push(int value)
{
    if(isFull())
    {
        cout << "Stack Overflow" << endl;
        return;
    }

    top++;
    stack[top] = value;

    cout << value << " pushed into stack" << endl;
}

void pop()
{
    if(isEmpty())
    {
        cout << "Stack Underflow" << endl;
        return;
    }

    cout << stack[top] << " popped from stack" << endl;
    top--;
}

void peek()
{
    if(isEmpty())
    {
        cout << "Stack is Empty" << endl;
        return;
    }

    cout << "Top element: " << stack[top] << endl;
}

void display()
{
    if(isEmpty())
    {
        cout << "Stack is Empty" << endl;
        return;
    }

    cout << "Stack: ";

    for(int i = top; i >= 0; i--)
    {
        cout << stack[i] << " ";
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

    return 0;
}