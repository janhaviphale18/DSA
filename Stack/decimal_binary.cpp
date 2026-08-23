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

int main()
{
    int number;
    int original;

    cout << "Enter decimal number: ";
    cin >> number;

    original = number;

    if(number == 0)
    {
        push(0);
    }
    else
    {
        while(number > 0)
        {
            int remainder = number % 2;

            push(remainder);

            number = number / 2;
        }
    }

    cout << "Decimal: " << original << endl;
    cout << "Binary: ";

    while(top != -1)
    {
        cout << pop();
    }

    cout << endl;

    return 0;
}