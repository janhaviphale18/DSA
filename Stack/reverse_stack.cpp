#include<iostream>
using namespace std;

#define MAX 5

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

void reverseStack()
{
    int temp[MAX];
    int newTop = -1;

    while(top != -1)
    {
        newTop++;
        temp[newTop] = stack[top];
        top--;
    }

    for(int i = 0; i <= newTop; i++)
    {
        top++;
        stack[top] = temp[i];
    }
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