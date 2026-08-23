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
    if(top == -1)
    {
        return -1;
    }

    int value = stack[top];
    top--;

    return value;
}

void insertBottom(int value)
{
    int temp[MAX];
    int tempTop = -1;

    while(top != -1)
    {
        tempTop++;
        temp[tempTop] = pop();
    }

    push(value);

    while(tempTop != -1)
    {
        push(temp[tempTop]);
        tempTop--;
    }
}

void display()
{
    if(top == -1)
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

    cout << "Original ";
    display();

    insertBottom(5);

    cout << "After insertion ";
    display();

    return 0;
}