#include<iostream>
using namespace std;

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value)
{
    top++;
    stack[top] = value;
}

int pop()
{
    int value = stack[top];
    top--;

    return value;
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

void removeMiddle()
{
    if(top == -1)
    {
        cout << "Stack is Empty" << endl;
        return;
    }

    int n = top + 1;
    int middle = n / 2;

    int temp[MAX];
    int tempTop = -1;

    for(int i = 0; i < middle; i++)
    {
        tempTop++;
        temp[tempTop] = pop();
    }

    int removed = pop();

    while(tempTop != -1)
    {
        push(temp[tempTop]);
        tempTop--;
    }

    cout << "Removed middle element: " << removed << endl;
}

int main()
{
    push(50);
    push(40);
    push(30);
    push(20);
    push(10);

    cout << "Original ";
    display();

    removeMiddle();

    cout << "After removing middle ";
    display();

    return 0;
}