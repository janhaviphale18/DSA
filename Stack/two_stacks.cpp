#include<iostream>
using namespace std;

#define MAX 10

int stack[MAX];

int top1 = -1;
int top2 = MAX;

void push1(int value)
{
    if(top1 + 1 == top2)
    {
        cout << "Stack Overflow" << endl;
        return;
    }

    top1++;
    stack[top1] = value;

    cout << value << " pushed into Stack 1" << endl;
}

void push2(int value)
{
    if(top1 + 1 == top2)
    {
        cout << "Stack Overflow" << endl;
        return;
    }

    top2--;
    stack[top2] = value;

    cout << value << " pushed into Stack 2" << endl;
}

void pop1()
{
    if(top1 == -1)
    {
        cout << "Stack 1 Underflow" << endl;
        return;
    }

    cout << stack[top1] << " popped from Stack 1" << endl;
    top1--;
}

void pop2()
{
    if(top2 == MAX)
    {
        cout << "Stack 2 Underflow" << endl;
        return;
    }

    cout << stack[top2] << " popped from Stack 2" << endl;
    top2++;
}

void display1()
{
    if(top1 == -1)
    {
        cout << "Stack 1 is Empty" << endl;
        return;
    }

    cout << "Stack 1: ";

    for(int i = 0; i <= top1; i++)
    {
        cout << stack[i] << " ";
    }

    cout << endl;
}

void display2()
{
    if(top2 == MAX)
    {
        cout << "Stack 2 is Empty" << endl;
        return;
    }

    cout << "Stack 2: ";

    for(int i = MAX - 1; i >= top2; i--)
    {
        cout << stack[i] << " ";
    }

    cout << endl;
}

int main()
{
    push1(10);
    push1(20);

    push2(50);
    push2(40);

    display1();
    display2();

    pop1();
    pop2();

    display1();
    display2();

    return 0;
}