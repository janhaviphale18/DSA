#include<iostream>
using namespace std;

#define MAX 100

int stack1[MAX];
int stack2[MAX];

int top1 = -1;
int top2 = -1;

void push1(int value)
{
    top1++;
    stack1[top1] = value;
}

void push2(int value)
{
    top2++;
    stack2[top2] = value;
}

int pop1()
{
    int value = stack1[top1];
    top1--;
    return value;
}

int pop2()
{
    int value = stack2[top2];
    top2--;
    return value;
}

void display()
{
    for(int i = top1; i >= 0; i--)
    {
        cout << stack1[i] << " ";
    }

    cout << endl;
}

void sortStack()
{
    while(top1 != -1)
    {
        int value = pop1();

        while(top2 != -1 && stack2[top2] > value)
        {
            push1(pop2());
        }

        push2(value);
    }

    while(top2 != -1)
    {
        push1(pop2());
    }
}

int main()
{
    push1(30);
    push1(10);
    push1(40);
    push1(20);

    cout << "Original Stack: ";
    display();

    sortStack();

    cout << "Sorted Stack: ";
    display();

    return 0;
}