#include<iostream>
using namespace std;

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value)
{
    if(top == MAX - 1)
    {
        cout << "Stack Overflow" << endl;
        return;
    }

    top++;
    stack[top] = value;
}

int pop()
{
    int value = stack[top];
    top--;

    return value;
}

void insertBottom(int value)
{
    if(top == -1)
    {
        push(value);
        return;
    }

    int temp = pop();

    insertBottom(value);

    push(temp);
}

void reverseStack()
{
    if(top == -1)
    {
        return;
    }

    int temp = pop();

    reverseStack();

    insertBottom(temp);
}

void display()
{
    if(top == -1)
    {
        cout << "Stack is Empty" << endl;
        return;
    }

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
    push(40);

    cout << "Original Stack: ";
    display();

    reverseStack();

    cout << "Reversed Stack: ";
    display();

    return 0;
}