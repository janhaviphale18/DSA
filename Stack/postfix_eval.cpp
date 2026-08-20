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
    string expression;

    cout << "Enter postfix expression: ";
    cin >> expression;

    for(int i = 0; expression[i] != '\0'; i++)
    {
        char ch = expression[i];

        if(ch >= '0' && ch <= '9')
        {
            push(ch - '0');
        }
        else
        {
            int second = pop();
            int first = pop();
            int result;

            if(ch == '+')
            {
                result = first + second;
            }
            else if(ch == '-')
            {
                result = first - second;
            }
            else if(ch == '*')
            {
                result = first * second;
            }
            else if(ch == '/')
            {
                result = first / second;
            }

            push(result);
        }
    }

    cout << "Postfix Expression: " << expression << endl;
    cout << "Result: " << pop() << endl;

    return 0;
}