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

int peek()
{
    return stack[top];
}

int main()
{
    int n;
    int price[MAX];
    int span[MAX];

    cout << "Enter number of days: ";
    cin >> n;

    cout << "Enter stock prices: ";

    for(int i = 0; i < n; i++)
    {
        cin >> price[i];
    }

    for(int i = 0; i < n; i++)
    {
        while(top != -1 && price[peek()] <= price[i])
        {
            pop();
        }

        if(top == -1)
        {
            span[i] = i + 1;
        }
        else
        {
            span[i] = i - peek();
        }

        push(i);
    }

    cout << "Stock Span: ";

    for(int i = 0; i < n; i++)
    {
        cout << span[i] << " ";
    }

    cout << endl;

    return 0;
}