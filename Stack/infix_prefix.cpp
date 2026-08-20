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

void reverseString(string &str)
{
    int start = 0;
    int end = str.length() - 1;

    while(start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

int main()
{
    string infix;
    string prefix = "";

    cout << "Enter infix expression: ";
    cin >> infix;

    reverseString(infix);

    for(int i = 0; infix[i] != '\0'; i++)
    {
        if(infix[i] == '(')
        {
            infix[i] = ')';
        }
        else if(infix[i] == ')')
        {
            infix[i] = '(';
        }
    }

    for(int i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        if(isOperand(ch))
        {
            prefix += ch;
        }

        else if(ch == '(')
        {
            push(ch);
        }

        else if(ch == ')')
        {
            while(top != -1 && peek() != '(')
            {
                prefix += pop();
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
                  precedence(peek()) > precedence(ch))
            {
                prefix += pop();
            }

            push(ch);
        }
    }

    while(top != -1)
    {
        prefix += pop();
    }

    reverseString(prefix);

    cout << "Prefix expression: " << prefix << endl;

    return 0;
}