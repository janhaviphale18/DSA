#include<iostream>
using namespace std;

#define MAX 100

char stack[MAX];
int top = -1;

void push(char value)
{
    if(top == MAX - 1)
    {
        cout << "Stack Overflow" << endl;
        return;
    }

    top++;
    stack[top] = value;
}

char pop()
{
    if(top == -1)
    {
        return '\0';
    }

    char value = stack[top];
    top--;

    return value;
}

bool isMatching(char open, char close)
{
    if(open == '(' && close == ')')
        return true;

    if(open == '{' && close == '}')
        return true;

    if(open == '[' && close == ']')
        return true;

    return false;
}

int main()
{
    string expression;

    cout << "Enter expression: ";
    cin >> expression;

    for(int i = 0; expression[i] != '\0'; i++)
    {
        char ch = expression[i];

        if(ch == '(' || ch == '{' || ch == '[')
        {
            push(ch);
        }
        else if(ch == ')' || ch == '}' || ch == ']')
        {
            if(top == -1)
            {
                cout << "Not Balanced" << endl;
                return 0;
            }

            char open = pop();

            if(!isMatching(open, ch))
            {
                cout << "Not Balanced" << endl;
                return 0;
            }
        }
    }

    if(top == -1)
    {
        cout << "Balanced Parentheses" << endl;
    }
    else
    {
        cout << "Not Balanced" << endl;
    }

    return 0;
}