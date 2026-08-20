#include<iostream>
using namespace std;

#define MAX 100

char stack[MAX];
int top = -1;

void push(char value)
{
    top++;
    stack[top] = value;
}

char pop()
{
    char value = stack[top];
    top--;

    return value;
}

char peek()
{
    return stack[top];
}

int precedence(char op)
{
    if(op == '^')
        return 3;

    if(op == '*' || op == '/')
        return 2;

    if(op == '+' || op == '-')
        return 1;

    return 0;
}

bool isOperand(char ch)
{
    if((ch >= 'A' && ch <= 'Z') ||
       (ch >= 'a' && ch <= 'z') ||
       (ch >= '0' && ch <= '9'))
    {
        return true;
    }

    return false;
}

int main()
{
    string infix;
    string postfix = "";

    cout << "Enter infix expression: ";
    cin >> infix;

    for(int i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        if(isOperand(ch))
        {
            postfix += ch;
        }

        else if(ch == '(')
        {
            push(ch);
        }

        else if(ch == ')')
        {
            while(top != -1 && peek() != '(')
            {
                postfix += pop();
            }

            if(top != -1)
            {
                pop();
            }
        }

        else
        {
            while(top != -1 &&
                  peek() != '(' &&
                  precedence(peek()) >= precedence(ch))
            {
                postfix += pop();
            }

            push(ch);
        }
    }

    while(top != -1)
    {
        postfix += pop();
    }

    cout << "Postfix expression: " << postfix << endl;

    return 0;
}